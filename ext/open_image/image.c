
#include "image.h"

#define IMAGE()   \
    Image *image; \
    Data_Get_Struct(self, Image, image);

#define JPEG_QUALITY 90
#define COLOR_SIZE 4 /* For possible future expandment */
#define COLOR_COMP 4 /* Number of color components */

VALUE rb_cOpenImage;
VALUE rb_cOpenImagePointer;

void Init_open_image_image(VALUE module) {
    rb_cOpenImage = rb_define_class_under(module, "Image", rb_cObject);

    rb_define_alloc_func(rb_cOpenImage, open_image_alloc);
    rb_define_method(rb_cOpenImage, "initialize", open_image_initialize, -1);
    rb_define_method(rb_cOpenImage, "dispose", open_image_dispose, 0);
    rb_define_method(rb_cOpenImage, "disposed?", open_image_disposed_p, 0);

    rb_define_method(rb_cOpenImage, "width", open_image_width, 0);
    rb_define_method(rb_cOpenImage, "height", open_image_height, 0);
    rb_define_method(rb_cOpenImage, "pixels", open_image_pixels, 0);
    rb_define_alias(rb_cOpenImage, "rows", "height");
    rb_define_alias(rb_cOpenImage, "columns", "width");
    rb_define_alias(rb_cOpenImage, "to_blob", "pixels");
    rb_define_method(rb_cOpenImage, "dup", open_image_dup, 0);

    rb_define_method(rb_cOpenImage, "ptr", open_image_ptr, 0);
    rb_define_method(rb_cOpenImage, "size", open_image_size, 0);
    rb_define_method(rb_cOpenImage, "rect", open_image_rect, 0);
    rb_define_method(rb_cOpenImage, "to_s", open_image_to_s, 0);
    rb_define_alias(rb_cOpenImage, "to_str", "to_s");

    rb_define_method(rb_cOpenImage, "save_png", open_image_save_png, 1);
    rb_define_method(rb_cOpenImage, "save_jpg", open_image_save_jpg, -1);
    rb_define_method(rb_cOpenImage, "save_bmp", open_image_save_bmp, 1);
    rb_define_method(rb_cOpenImage, "save_tga", open_image_save_tga, 1);

    rb_define_method(rb_cOpenImage, "get_pixel", open_image_get_pixel, -1);
    rb_define_method(rb_cOpenImage, "set_pixel", open_image_set_pixel, -1);
    rb_define_method(rb_cOpenImage, "fill_rect", open_image_fill_rect, -1);
    rb_define_method(rb_cOpenImage, "subimage", open_image_subimage, -1);

    rb_define_method(rb_cOpenImage, "split", open_image_split, 2);
}

static inline void open_image_free(void *data) {
    Image *image = (Image *)data;
    xfree(image->pixels);
    xfree(image);
    image->pixels = NULL;
}

VALUE open_image_dispose(VALUE self) {
    open_image_free(RDATA(self)->data);
}

VALUE open_image_disposed_p(VALUE self) {
    IMAGE();
    return image->pixels ? Qfalse : Qtrue;
}

VALUE open_image_alloc(VALUE klass) {
    Image *image = ALLOC(Image);
    memset(image, 0, sizeof(Image));
    return Data_Wrap_Struct(klass, NULL, open_image_free, image);
}

VALUE open_image_initialize(int argc, VALUE *argv, VALUE self) {
    IMAGE();

    VALUE arg1, arg2, options;
    argc = rb_scan_args(argc, argv, "11:", &arg1, &arg2, &options);

    int flip = !NIL_P(options) && RTEST(rb_hash_aref(options, ID2SYM(rb_intern("flip"))));

    if (argc == 1)  // From File
    {
        Check_Type(arg1, T_STRING);
        const char *filename = StringValueCStr(arg1);
        if (flip)
            stbi_set_flip_vertically_on_load(TRUE);

        int n;
        image->pixels = (unsigned char *)stbi_load(filename, &image->width, &image->height, &n, COLOR_COMP);

        if (flip)
            stbi_set_flip_vertically_on_load(FALSE);
    } else  // From Dimensions
    {
        uint w = NUM2UINT(arg1);
        uint h = NUM2UINT(arg2);
        size_t size = w * h * COLOR_SIZE;

        image->width = w;
        image->height = h;
        image->pixels = xmalloc(size);

        VALUE c = Qnil;
        if (!NIL_P(options))
            c = rb_hash_aref(options, ID2SYM(rb_intern("color")));

        if (NIL_P(c))
            memset(image->pixels, 0, size);
        else {
            Color *src;
            Data_Get_Struct(c, Color, src);

            unsigned char *dst = (unsigned char *)image->pixels;
            size_t sz = sizeof(Color);
            for (int i = 0; i < size; i += sz)
                memcpy(dst + i, src, sz);
        }
    }

    if (rb_block_given_p()) {
        rb_yield(self);
        open_image_free(image);
    }

    return Qnil;
}

VALUE open_image_width(VALUE self) {
    IMAGE();
    return UINT2NUM(image->width);
}

VALUE open_image_height(VALUE self) {
    IMAGE();
    return UINT2NUM(image->height);
}

VALUE open_image_pixels(VALUE self) {
    IMAGE();
    long size = (long)(image->width * image->height * COLOR_SIZE);
    return rb_str_new(image->pixels, size);
}

VALUE open_image_ptr(VALUE self) {
    if (!rb_cOpenImagePointer) {
        rb_require("fiddle");
        VALUE fiddle = rb_const_get(rb_cObject, rb_intern("Fiddle"));
        rb_cOpenImagePointer = rb_const_get(fiddle, rb_intern("Pointer"));
    }

    IMAGE();
    VALUE *args = xmalloc(sizeof(VALUE) * 2);
    args[0] = LL2NUM((size_t)&image->pixels);
    args[1] = UINT2NUM(image->width * image->height * 4);
    VALUE pointer = rb_obj_alloc(rb_cOpenImagePointer);
    rb_obj_call_init(pointer, 2, args);
    xfree(args);
    return pointer;
}

VALUE open_image_save_png(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int stride = image->width * COLOR_SIZE;
    int result = stbi_write_png(filename, image->width, image->height, COLOR_COMP, image->pixels, stride);
    return result ? Qtrue : Qfalse;
}

VALUE open_image_save_jpg(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    VALUE path, quality;
    rb_scan_args(argc, argv, "11", &path, &quality);

    int q = NIL_P(quality) ? JPEG_QUALITY : NUM2INT(quality);
    const char *filename = StringValueCStr(path);

    int result = stbi_write_jpg(filename, image->width, image->height, COLOR_COMP, image->pixels, q);
    return result ? Qtrue : Qfalse;
}

VALUE open_image_save_tga(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int result = stbi_write_tga(filename, image->width, image->height, COLOR_COMP, image->pixels);
    return result ? Qtrue : Qfalse;
}

VALUE open_image_save_bmp(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int result = stbi_write_bmp(filename, image->width, image->height, COLOR_COMP, image->pixels);
    return result ? Qtrue : Qfalse;
}

VALUE open_image_get_pixel(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    Color *color = ALLOC(Color);
    int x, y;
    if (argc == 1) {
        Point *point;
        Data_Get_Struct(argv[0], Point, point);
        x = point->x;
        y = point->y;
    } else if (argc == 2) {
        x = NUM2INT(argv[0]);
        y = NUM2INT(argv[1]);
    } else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);

    if (x < 0 || x >= image->width)
        rb_raise(rb_eRangeError, "x coordinate outside of image bounds (given %d, expected 0...%u)", x, image->width);
    if (y < 0 || y >= image->height)
        rb_raise(rb_eRangeError, "y coordinate outside of image bounds (given %d, expected 0...%u)", y, image->height);

    int offset = (x + (y * image->width)) * COLOR_SIZE;
    memcpy(color, *(&image->pixels) + offset, COLOR_SIZE);
    RETURN_WRAP_STRUCT(rb_cOpenImageColor, color);
}

VALUE open_image_set_pixel(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    int x, y;
    Color *color;
    if (argc == 2) {
        Point *point;
        Data_Get_Struct(argv[0], Point, point);
        x = point->x;
        y = point->y;
        Data_Get_Struct(argv[1], Color, color);
    } else if (argc == 3) {
        x = NUM2INT(argv[0]);
        y = NUM2INT(argv[1]);
        Data_Get_Struct(argv[2], Color, color);
    } else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2, 3)", argc);

    if (x < 0 || x >= image->width)
        rb_raise(rb_eRangeError, "x coordinate outside of image bounds (given %d, expected 0...%u)", x, image->width);
    if (y < 0 || y >= image->height)
        rb_raise(rb_eRangeError, "y coordinate outside of image bounds (given %d, expected 0...%u)", y, image->height);

    int offset = (x + (y * image->width)) * COLOR_SIZE;
    memcpy(*(&image->pixels) + offset, color, COLOR_SIZE);

    return self;
}

VALUE open_image_fill_rect(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    int t, l, r, b;
    Color *color;
    if (argc == 2) {
        Rect *rect;
        Data_Get_Struct(argv[0], Rect, rect);
        l = MAX(rect->x, 0);
        t = MAX(rect->y, 0);
        r = MIN(l + NUM2INT(rect->width), image->width - 1);
        b = MIN(t + NUM2INT(rect->height), image->height - 1);
        Data_Get_Struct(argv[1], Color, color);
    } else if (argc == 5) {
        l = MAX(NUM2INT(argv[0]), 0);
        t = MAX(NUM2INT(argv[1]), 0);
        r = MIN(NUM2INT(argv[2]) + l, image->width - 1);
        b = MIN(NUM2INT(argv[3]) + t, image->height - 1);
        Data_Get_Struct(argv[4], Color, color);
    } else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2, 5)", argc);

    if (l >= r || t >= b)
        rb_raise(rb_eOpenImageError, "invalid rectangle specified (%d, %d, %d, %d)", l, t, r - l, b - t);

    int w = (r - l) * COLOR_SIZE;
    for (int y = t; y < b; y++) {
        int offset = (l + (y * image->width)) * COLOR_SIZE;
        for (int i = 0; i < w; i += COLOR_SIZE) {
            memcpy(*(&image->pixels) + offset + i, color, COLOR_SIZE);
        }
    }
    return self;
}

VALUE open_image_subimage(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    int t, l, r, b;
    if (argc == 1) {
        Rect *rect;
        Data_Get_Struct(argv[0], Rect, rect);
        l = MAX(rect->x, 0);
        t = MAX(rect->y, 0);
        r = MIN(l + NUM2INT(rect->width), image->width - 1);
        b = MIN(t + NUM2INT(rect->height), image->height - 1);
    } else if (argc == 4) {
        l = MAX(NUM2INT(argv[0]), 0);
        t = MAX(NUM2INT(argv[1]), 0);
        r = MIN(NUM2INT(argv[2]) + l, image->width - 1);
        b = MIN(NUM2INT(argv[3]) + t, image->height - 1);
    } else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 4)", argc);

    if (l >= r || t >= b)
        rb_raise(rb_eOpenImageError, "invalid rectangle specified (%d, %d, %d, %d)", l, t, r - l, b - t);

    unsigned char *dst = xmalloc((r - l) * (b - t) * COLOR_SIZE);
    unsigned char *src = *(&image->pixels);

    size_t w = (r - l) * COLOR_SIZE;
    int i = 0;
    for (int y = t; y < b; y++, i++) {
        int d = i * w;
        int s = (l + (y * image->width)) * COLOR_SIZE;
        memcpy(dst + d, src + s, w);
    }
    Image *sub = ALLOC(Image);
    sub->width = r - l;
    sub->height = b - t;
    sub->pixels = dst;
    return Data_Wrap_Struct(CLASS_OF(self), NULL, open_image_free, sub);
}

VALUE open_image_split(VALUE self, VALUE rows, VALUE columns) {
    int r = NUM2INT(rows);
    int c = NUM2INT(columns);

    if (r < 1)
        rb_raise(rb_eOpenImageError, "row count must be greater than 0 (given %d)", r);
    if (c < 1)
        rb_raise(rb_eOpenImageError, "column count must be greater than 0 (given %d)", c);

    if (r == 1 && c == 1)
        return rb_Array(self);

    IMAGE();
    if (image->width % c != 0)
        rb_raise(rb_eOpenImageError, "specified number of columns (%d) must be evenly divisible by image width (%u)", c, image->width);

    if (image->height % r != 0)
        rb_raise(rb_eOpenImageError, "specified number of rows (%d) must be evenly divisible by image height (%u)", r, image->height);

    uint w = image->width / c;
    uint h = image->height / r;

    int d, s, tx, ty, count = r * c;
    VALUE ary = rb_ary_new_capa(count);

    size_t row_width = w * COLOR_SIZE;
    VALUE klass = CLASS_OF(self);
    unsigned char *src = *(&image->pixels);
    for (int i = 0; i < count; i++) {
        tx = i % c;
        ty = i / c;
        unsigned char *dst = xmalloc(w * h * COLOR_SIZE);
        for (int y = 0; y < h; y++) {
            d = y * row_width;
            s = ((y * image->width) + (tx * w) + ((ty * h) * image->width)) * COLOR_SIZE;
            memcpy(dst + d, src + s, row_width);
        }
        Image *sub = ALLOC(Image);
        sub->width = w;
        sub->height = h;
        sub->pixels = dst;
        rb_ary_store(ary, i, Data_Wrap_Struct(klass, NULL, open_image_free, sub));
    }
    return ary;
}

VALUE open_image_size(VALUE self) {
    IMAGE();
    Size *size = ALLOC(Size);
    size->width = image->width;
    size->height = image->height;
    RETURN_WRAP_STRUCT(rb_cOpenImageSize, size);
}

VALUE open_image_rect(VALUE self) {
    IMAGE();
    Rect *rect = ALLOC(Rect);
    rect->x = 0;
    rect->y = 0;
    rect->width = image->width;
    rect->height = image->height;
    RETURN_WRAP_STRUCT(rb_cOpenImageRect, rect);
}

VALUE open_image_to_s(VALUE self) {
    IMAGE();
    return rb_sprintf("<Image: width:%u, height:%u>", image->width, image->height);
}

VALUE open_image_dup(VALUE self) {
    IMAGE();
    Image *clone = ALLOC(Image);
    memcpy(clone, image, sizeof(uint) * 2);

    size_t size = clone->width * clone->height * COLOR_SIZE;
    clone->pixels = xmalloc(size);
    memcpy(*(&clone->pixels), *(&image->pixels), size);

    return Data_Wrap_Struct(CLASS_OF(self), NULL, open_image_free, clone);
}