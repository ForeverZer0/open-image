
#include "image.h"

#define IMAGE()   \
    Image *image; \
    Data_Get_Struct(self, Image, image);

#define JPEG_QUALITY 90
#define COLOR_SIZE 4 /* For possible future expandment */
#define COLOR_COMP 4 /* Number of color components */

#define RETURN_WRAP_IMAGE(klass, img) return Data_Wrap_Struct(klass, NULL, img_image_free, img)

#define GET_PIXEL(img, x, y, c) ((unsigned char)(img->pixels[(((x) + ((y)*img->width) * COLOR_SIZE) + c)]))

#define IMAGE_DUP()                                           \
    Image *image, *dup;                                       \
    Data_Get_Struct(self, Image, image);                      \
    dup = ALLOC(Image);                                       \
    dup->width = image->width;                                \
    dup->height = image->height;                              \
    size_t _size = image->width * image->height * COLOR_SIZE; \
    dup->pixels = xmalloc(_size);                             \
    memcpy(*(&dup->pixels), *(&image->pixels), _size)

VALUE cImage;

void Init_img_image(VALUE module) {
    cImage = rb_define_class_under(module, "Image", rb_cObject);

    rb_define_alloc_func(cImage, img_image_alloc);
    rb_define_method(cImage, "initialize", img_image_initialize, -1);
    rb_define_method(cImage, "dispose", img_image_dispose, 0);
    rb_define_method(cImage, "disposed?", img_image_disposed_p, 0);

    rb_define_method(cImage, "width", img_image_width, 0);
    rb_define_method(cImage, "height", img_image_height, 0);
    rb_define_method(cImage, "pixels", img_image_pixels, 0);
    rb_define_alias(cImage, "rows", "height");
    rb_define_alias(cImage, "columns", "width");
    rb_define_alias(cImage, "to_blob", "pixels");
    rb_define_method(cImage, "dup", img_image_dup, 0);
    rb_define_method(cImage, "ptr", img_image_ptr, 0);

    rb_define_method(cImage, "size", img_image_size, 0);
    rb_define_method(cImage, "rect", img_image_rect, 0);
    rb_define_method(cImage, "to_s", img_image_to_s, 0);
    rb_define_alias(cImage, "to_str", "to_s");

    rb_define_method(cImage, "save_png", img_image_save_png, 1);
    rb_define_method(cImage, "save_jpg", img_image_save_jpg, -1);
    rb_define_method(cImage, "save_bmp", img_image_save_bmp, 1);
    rb_define_method(cImage, "save_tga", img_image_save_tga, 1);

    rb_define_method(cImage, "get_pixel", img_image_get_pixel, -1);
    rb_define_method(cImage, "set_pixel", img_image_set_pixel, -1);
    rb_define_method(cImage, "fill_rect", img_image_fill_rect, -1);
    rb_define_method(cImage, "subimage", img_image_subimage, -1);
    rb_define_method(cImage, "split", img_image_split, 2);

#if OPEN_IMAGE_GRAYSCALE
    rb_define_method(cImage, "grayscale", img_image_grayscale, -1);
    rb_define_method(cImage, "grayscale!", img_image_grayscale_bang, -1);
#endif

#if OPEN_IMAGE_SEPIA
    rb_define_method(cImage, "sepia", img_image_sepia, 0);
    rb_define_method(cImage, "sepia!", img_image_sepia_bang, 0);
#endif

#if OPEN_IMAGE_INVERT
    rb_define_method(cImage, "invert", img_image_invert, -1);
    rb_define_method(cImage, "invert!", img_image_invert_bang, -1);
#endif

#if OPEN_IMAGE_PIXELATE
    rb_define_method(cImage, "pixelate", img_image_pixelate, -1);
    rb_define_method(cImage, "pixelate!", img_image_pixelate_bang, -1);
#endif

#if OPEN_IMAGE_SOLARIZE
    rb_define_method(cImage, "solarize", img_image_solarize, 3);
    rb_define_method(cImage, "solarize!", img_image_solarize_bang, 3);
#endif

#if OPEN_IMAGE_CONTRAST
    rb_define_method(cImage, "contrast", img_image_contrast, 1);
    rb_define_method(cImage, "contrast!", img_image_contrast_bang, 1);
#endif

#if OPEN_IMAGE_COLOR_BALANCE
    rb_define_method(cImage, "balance", img_image_balance, 3);
    rb_define_method(cImage, "balance!", img_image_balance_bang, 3);
#endif

#if OPEN_IMAGE_BLUR
    rb_define_method(cImage, "blur", img_image_box_blur, 0);
    // rb_define_method(cImage, "blur!", img_image_blur_bang, 1);
#endif
}

static inline void img_image_free(void *data) {
    Image *image = (Image *)data;
    xfree(image->pixels);
    xfree(image);
    image->pixels = NULL;
}

VALUE img_image_dispose(VALUE self) {
    img_image_free(RDATA(self)->data);
}

VALUE img_image_disposed_p(VALUE self) {
    IMAGE();
    return image->pixels ? Qfalse : Qtrue;
}

VALUE img_image_alloc(VALUE klass) {
    Image *image = ALLOC(Image);
    memset(image, 0, sizeof(Image));
    return Data_Wrap_Struct(klass, NULL, img_image_free, image);
}

VALUE img_image_initialize(int argc, VALUE *argv, VALUE self) {
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
        img_image_free(image);
    }

    return Qnil;
}

VALUE img_image_width(VALUE self) {
    IMAGE();
    return UINT2NUM(image->width);
}

VALUE img_image_height(VALUE self) {
    IMAGE();
    return UINT2NUM(image->height);
}

VALUE img_image_pixels(VALUE self) {
    IMAGE();
    long size = (long)(image->width * image->height * COLOR_SIZE);
    return rb_str_new(image->pixels, size);
}

VALUE img_image_save_png(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int stride = image->width * COLOR_SIZE;
    int result = stbi_write_png(filename, image->width, image->height, COLOR_COMP, image->pixels, stride);
    return result ? Qtrue : Qfalse;
}

VALUE img_image_save_jpg(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    VALUE path, quality;
    rb_scan_args(argc, argv, "11", &path, &quality);

    int q = NIL_P(quality) ? JPEG_QUALITY : NUM2INT(quality);
    const char *filename = StringValueCStr(path);

    int result = stbi_write_jpg(filename, image->width, image->height, COLOR_COMP, image->pixels, q);
    return result ? Qtrue : Qfalse;
}

VALUE img_image_save_tga(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int result = stbi_write_tga(filename, image->width, image->height, COLOR_COMP, image->pixels);
    return result ? Qtrue : Qfalse;
}

VALUE img_image_save_bmp(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int result = stbi_write_bmp(filename, image->width, image->height, COLOR_COMP, image->pixels);
    return result ? Qtrue : Qfalse;
}

VALUE img_image_get_pixel(int argc, VALUE *argv, VALUE self) {
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
    RETURN_WRAP_STRUCT(cColor, color);
}

VALUE img_image_set_pixel(int argc, VALUE *argv, VALUE self) {
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

VALUE img_image_fill_rect(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    int t, l, r, b;
    Color *color;
    if (argc == 2) {
        Rect *rect;
        Data_Get_Struct(argv[0], Rect, rect);
        l = imax(rect->x, 0);
        t = imax(rect->y, 0);
        r = imin(l + NUM2INT(rect->width), image->width - 1);
        b = imin(t + NUM2INT(rect->height), image->height - 1);
        Data_Get_Struct(argv[1], Color, color);
    } else if (argc == 5) {
        l = imax(NUM2INT(argv[0]), 0);
        t = imax(NUM2INT(argv[1]), 0);
        r = imin(NUM2INT(argv[2]) + l, image->width - 1);
        b = imin(NUM2INT(argv[3]) + t, image->height - 1);
        Data_Get_Struct(argv[4], Color, color);
    } else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2, 5)", argc);

    if (l >= r || t >= b)
        rb_raise(eOpenImageError, "invalid rectangle specified (%d, %d, %d, %d)", l, t, r - l, b - t);

    int w = (r - l) * COLOR_SIZE;
    for (int y = t; y < b; y++) {
        int offset = (l + (y * image->width)) * COLOR_SIZE;
        for (int i = 0; i < w; i += COLOR_SIZE) {
            memcpy(*(&image->pixels) + offset + i, color, COLOR_SIZE);
        }
    }
    return self;
}

VALUE img_image_subimage(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    int t, l, r, b;
    if (argc == 1) {
        Rect *rect;
        Data_Get_Struct(argv[0], Rect, rect);
        l = imax(rect->x, 0);
        t = imax(rect->y, 0);
        r = imin(l + NUM2INT(rect->width), image->width - 1);
        b = imin(t + NUM2INT(rect->height), image->height - 1);
    } else if (argc == 4) {
        l = imax(NUM2INT(argv[0]), 0);
        t = imax(NUM2INT(argv[1]), 0);
        r = imin(NUM2INT(argv[2]) + l, image->width - 1);
        b = imin(NUM2INT(argv[3]) + t, image->height - 1);
    } else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 4)", argc);

    if (l >= r || t >= b)
        rb_raise(eOpenImageError, "invalid rectangle specified (%d, %d, %d, %d)", l, t, r - l, b - t);

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
    return Data_Wrap_Struct(CLASS_OF(self), NULL, img_image_free, sub);
}

VALUE img_image_split(VALUE self, VALUE rows, VALUE columns) {
    int r = NUM2INT(rows);
    int c = NUM2INT(columns);

    if (r < 1)
        rb_raise(eOpenImageError, "row count must be greater than 0 (given %d)", r);
    if (c < 1)
        rb_raise(eOpenImageError, "column count must be greater than 0 (given %d)", c);

    if (r == 1 && c == 1)
        return rb_Array(self);

    IMAGE();
    if (image->width % c != 0)
        rb_raise(eOpenImageError, "specified number of columns (%d) must be evenly divisible by image width (%u)", c, image->width);

    if (image->height % r != 0)
        rb_raise(eOpenImageError, "specified number of rows (%d) must be evenly divisible by image height (%u)", r, image->height);

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
        rb_ary_store(ary, i, Data_Wrap_Struct(klass, NULL, img_image_free, sub));
    }
    return ary;
}

VALUE img_image_size(VALUE self) {
    IMAGE();
    Size *size = ALLOC(Size);
    size->width = image->width;
    size->height = image->height;
    RETURN_WRAP_STRUCT(cSize, size);
}

VALUE img_image_rect(VALUE self) {
    IMAGE();
    Rect *rect = ALLOC(Rect);
    rect->x = 0;
    rect->y = 0;
    rect->width = image->width;
    rect->height = image->height;
    RETURN_WRAP_STRUCT(cRect, rect);
}

VALUE img_image_to_s(VALUE self) {
    IMAGE();
    return rb_sprintf("<Image: width:%u, height:%u>", image->width, image->height);
}

VALUE img_image_dup(VALUE self) {
    IMAGE();
    Image *clone = ALLOC(Image);
    clone->width = image->width;
    clone->height = image->height;

    size_t size = clone->width * clone->height * COLOR_SIZE;
    clone->pixels = xmalloc(size);
    memcpy(*(&clone->pixels), *(&image->pixels), size);

    return Data_Wrap_Struct(CLASS_OF(self), NULL, img_image_free, clone);
}

VALUE img_image_ptr(VALUE self) {
    IMAGE();
#if USE_FIDDLE
    VALUE *args = xmalloc(sizeof(VALUE) * 2);
    args[0] = LL2NUM((size_t)&image->pixels);
    args[1] = UINT2NUM(image->width * image->height * 4);
    VALUE pointer = rb_obj_alloc(cFiddlePointer);
    rb_obj_call_init(pointer, 2, args);
    xfree(args);
    return pointer;
#else
    return LL2NUM((size_t)&image->pixels);
#endif
}

#if OPEN_IMAGE_GRAYSCALE

VALUE img_image_grayscale(int argc, VALUE *argv, VALUE self) {
    VALUE amount;
    rb_scan_args(argc, argv, "01", &amount);
    IMAGE_DUP();
    img_image_grayscale_s(dup, amount);
    RETURN_WRAP_IMAGE(CLASS_OF(self), dup);
}

VALUE img_image_grayscale_bang(int argc, VALUE *argv, VALUE self) {
    VALUE amount;
    rb_scan_args(argc, argv, "01", &amount);
    IMAGE();
    img_image_grayscale_s(image, amount);
    return self;
}

static void img_image_grayscale_s(Image *image, VALUE amount) {
    float gray = 1.0f;
    if (RTEST(amount))
        gray = fclamp((RB_FLOAT_TYPE_P(amount) ? NUM2FLT(amount) : NUM2INT(amount) / 255.0f), 0.0f, 1.0f);
    int count = image->width * image->height;
    Color *pixels = (Color *)image->pixels;
    float r, g, b;
    for (int i = 0; i < count; i++) {
        r = pixels[i].r / 255.0f;
        g = pixels[i].g / 255.0f;
        b = pixels[i].b / 255.0f;
        float mean = (r + g + b) / 3.0f;
        pixels[i].r = (unsigned char)((r - ((r - mean) * gray)) * 255.0f);
        pixels[i].g = (unsigned char)((g - ((g - mean) * gray)) * 255.0f);
        pixels[i].b = (unsigned char)((b - ((b - mean) * gray)) * 255.0f);
    }
}

#endif

#if OPEN_IMAGE_SEPIA

VALUE img_image_sepia(VALUE self) {
    IMAGE_DUP();
    img_image_sepia_s(dup);
    RETURN_WRAP_IMAGE(CLASS_OF(self), dup);
}

VALUE img_image_sepia_bang(VALUE self) {
    IMAGE();
    img_image_sepia_s(image);
    return self;
}

static void img_image_sepia_s(Image *image) {
    int count = image->width * image->height * COLOR_SIZE;
    unsigned char *p = *(&image->pixels);
    unsigned char r, g, b;
    for (int i = 0; i < count; i += COLOR_SIZE) {
        r = fmin(p[i] * 0.189f + p[i + 1] * 0.769f + p[i + 2] * 0.393f, 255.0f);
        g = fmin(p[i] * 0.168f + p[i + 1] * 0.686f + p[i + 2] * 0.349f, 255.0f);
        b = fmin(p[i] * 0.131f + p[i + 1] * 0.534f + p[i + 2] * 0.272f, 255.0f);
        p[i] = (unsigned char)r;
        p[i + 1] = (unsigned char)g;
        p[i + 2] = (unsigned char)b;
    }
}

#endif

#if OPEN_IMAGE_INVERT

VALUE img_image_invert(int argc, VALUE *argv, VALUE self) {
    IMAGE_DUP();
    VALUE alpha;
    rb_scan_args(argc, argv, "01", &alpha);
    img_image_invert_s(image, RTEST(alpha));
    RETURN_WRAP_IMAGE(CLASS_OF(self), dup);
}

VALUE img_image_invert_bang(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    VALUE alpha;
    rb_scan_args(argc, argv, "01", &alpha);
    img_image_invert_s(image, RTEST(alpha));
    return self;
}

static void img_image_invert_s(Image *image, int alpha) {
    int count = image->width * image->height * COLOR_SIZE;
    unsigned char *p = *(&image->pixels);
    for (int i = 0; i < count; i += COLOR_SIZE) {
        p[i] = 255 - p[i];
        p[i + 1] = 255 - p[i + 1];
        p[i + 2] = 255 - p[i + 2];
        if (alpha)
            p[i + 3] = 255 - p[i + 3];
    }
}

#endif

#if OPEN_IMAGE_PIXELATE

VALUE img_image_pixelate(int argc, VALUE *argv, VALUE self) {
    VALUE pixel_size, avg_alpha;
    rb_scan_args(argc, argv, "11", &pixel_size, &avg_alpha);
    int pix = NUM2INT(pixel_size);
    int avg = NIL_P(avg_alpha) ? 1 : RTEST(avg_alpha);
    IMAGE_DUP();
    img_image_pixelate_s(dup, pix, avg);
    RETURN_WRAP_IMAGE(CLASS_OF(self), dup);
}

VALUE img_image_pixelate_bang(int argc, VALUE *argv, VALUE self) {
    VALUE pixel_size, avg_alpha;
    rb_scan_args(argc, argv, "11", &pixel_size, &avg_alpha);
    int pix = NUM2INT(pixel_size);
    int avg = NIL_P(avg_alpha) ? 1 : RTEST(avg_alpha);
    IMAGE();
    img_image_pixelate_s(image, pix, avg);
    return self;
}

static void img_image_pixelate_s(Image *image, int pix, int avg) {
    unsigned char *p = *(&image->pixels);
    int r, g, b, a, p_count, width = image->width, height = image->height;

    for (int x = 0; x < width; x += pix) {
        for (int y = 0; y < height; y += pix) {
            r = g = b = a = p_count = 0;
            // Add the value of each color component of surrounding pixels
            for (int x2 = 0; x2 < pix; x2++) {
                for (int y2 = 0; y2 < pix; y2++) {
                    if ((x + x2 < width) && ((y + y2 < height))) {
                        int i = ((x + x2) * 4) + ((y + y2) * (width * 4));
                        r += p[i];
                        g += p[i + 1];
                        b += p[i + 2];
                        a += p[i + 3];
                        p_count++;
                    } else  // Edge of the image
                        break;
                }
            }
            // Calculate average color of surrounding pixels
            r /= p_count;
            g /= p_count;
            b /= p_count;
            a /= p_count;
            for (int x2 = 0; x2 < pix; x2++) {
                for (int y2 = 0; y2 < pix; y2++) {
                    if ((x + x2 < width) && ((y + y2 < height))) {
                        int i = ((x + x2) * 4) + ((y + y2) * (width * 4));
                        p[i] = r;
                        p[i + 1] = g;
                        p[i + 2] = b;
                        if (avg)
                            p[i + 3] = a;
                    } else
                        break;
                }
            }
        }
    }
}

#endif

#if OPEN_IMAGE_SOLARIZE

VALUE img_image_solarize(VALUE self, VALUE red, VALUE green, VALUE blue) {
    IMAGE_DUP();
    img_image_solarize_s(dup, red, green, blue);
    RETURN_WRAP_IMAGE(CLASS_OF(self), dup);
}

VALUE img_image_solarize_bang(VALUE self, VALUE red, VALUE green, VALUE blue) {
    IMAGE();
    img_image_solarize_s(image, red, green, blue);
    return self;
}

static void img_image_solarize_s(Image *image, VALUE red, VALUE green, VALUE blue) {
    unsigned char r = (unsigned char)iclamp(RB_FLOAT_TYPE_P(red) ? roundf(NUM2FLT(red) * 255.0f) : NUM2INT(red), 0, 255);
    unsigned char g = (unsigned char)iclamp(RB_FLOAT_TYPE_P(green) ? roundf(NUM2FLT(green) * 255.0f) : NUM2INT(green), 0, 255);
    unsigned char b = (unsigned char)iclamp(RB_FLOAT_TYPE_P(blue) ? roundf(NUM2FLT(blue) * 255.0f) : NUM2INT(blue), 0, 255);
    Color *p = (Color *)image->pixels;
    int count = image->width * image->height;
    for (int i = 0; i < count; i++) {
        if (p[i].r < r)
            p[i].r = 255 - p[i].r;
        if (p[i].g < g)
            p[i].g = 255 - p[i].g;
        if (p[i].b < b)
            p[i].b = 255 - p[i].b;
    }
}

#endif

#if OPEN_IMAGE_CONTRAST

VALUE img_image_contrast(VALUE self, VALUE contrast) {
    IMAGE_DUP();
    img_image_contrast_s(dup, contrast);
    RETURN_WRAP_IMAGE(CLASS_OF(self), dup);
}

VALUE img_image_contrast_bang(VALUE self, VALUE contrast) {
    IMAGE();
    img_image_contrast_s(image, contrast);
    return self;
}

static void img_image_contrast_s(Image *image, VALUE contrast) {
    float c = fclamp(NUM2FLT(contrast) + 1.0f, 0.0f, 2.0f);
    c *= c;
    Color *p = (Color *)image->pixels;
    int count = image->width * image->height;

    for (int i = 0; i < count; i++) {
        p[i].r = (unsigned char)fclamp((((p[i].r / 255.0f - 0.5f) * c) + 0.5f) * 255.0f, 0.0f, 255.0);
        p[i].g = (unsigned char)fclamp((((p[i].g / 255.0f - 0.5f) * c) + 0.5f) * 255.0f, 0.0f, 255.0);
        p[i].b = (unsigned char)fclamp((((p[i].b / 255.0f - 0.5f) * c) + 0.5f) * 255.0f, 0.0f, 255.0);
    }
}

#endif

#if OPEN_IMAGE_COLOR_BALANCE

VALUE img_image_balance(VALUE self, VALUE red, VALUE green, VALUE blue) {
    IMAGE_DUP();
    img_image_balance_s(dup, red, green, blue);
    RETURN_WRAP_IMAGE(CLASS_OF(self), dup);
}

VALUE img_image_balance_bang(VALUE self, VALUE red, VALUE green, VALUE blue) {
    IMAGE();
    img_image_balance_s(image, red, green, blue);
    return self;
}

static void img_image_balance_s(Image *image, VALUE red, VALUE green, VALUE blue) {
    float r = fclamp(RB_FLOAT_TYPE_P(red) ? NUM2FLT(red) * 255.0f : (NUM2INT(red)), 0.0f, 255.0f);
    float g = fclamp(RB_FLOAT_TYPE_P(green) ? NUM2FLT(green) * 255.0f : (NUM2INT(green)), 0.0f, 255.0f);
    float b = fclamp(RB_FLOAT_TYPE_P(blue) ? NUM2FLT(blue) * 255.0f : (NUM2INT(blue)), 0.0f, 255.0f);

    Color *p = (Color *)image->pixels;
    int count = image->width * image->height;
    for (int i = 0; i < count; i++) {
        p[i].r = (unsigned char)fclamp(255.0f / r * p[i].r, 0.0f, 255.0f);
        p[i].g = (unsigned char)fclamp(255.0f / g * p[i].g, 0.0f, 255.0f);
        p[i].b = (unsigned char)fclamp(255.0f / b * p[i].b, 0.0f, 255.0f);
    }
}

#endif

#if OPEN_IMAGE_BLUR

VALUE img_image_blur(VALUE self, VALUE size) {
    IMAGE_DUP();
    img_image_blur_s(dup, NUM2INT(size));
    RETURN_WRAP_STRUCT(CLASS_OF(self), dup);
}

VALUE img_image_blur_bang(VALUE self, VALUE size) {
    IMAGE();
    img_image_blur_s(image, NUM2INT(size));
    return self;
}

static void img_image_blur_s(Image *image, int blur_size) {
    if (blur_size < 1)
        return;
    int avg_r, avg_g, avg_b, pix_count, i;
    ;
    uint width = image->width, height = image->height;
    unsigned char *p = *(&image->pixels);
    size_t size = width * height * COLOR_SIZE;

    for (int xx = 0; xx < width; xx++) {
        for (int yy = 0; yy < height; yy++) {
            // Enumerate the pixels around the current pixel
            avg_r = avg_g = avg_b = pix_count = 0;
            for (int x = imax(0, xx - blur_size); x <= imin(xx + blur_size, width - 1); x++)
            // for (int x = xx; (x < xx + blur_size && x < width); x++)
            {
                for (int y = imax(0, yy - blur_size); y <= imin(yy + blur_size, height - 1); y++)
                // for (int y = yy; (y < yy + blur_size && y < height); y++)
                {
                    i = (x + (y * width)) * COLOR_SIZE;
                    avg_r += p[i];
                    avg_g += p[i + 1];
                    avg_b += p[i + 2];
                    pix_count++;
                }
            }

            // Calculate average of block size
            avg_r = (unsigned char)(avg_r / pix_count);
            avg_g = (unsigned char)(avg_g / pix_count);
            avg_b = (unsigned char)(avg_b / pix_count);
            // Set average value to pixels
            for (int x = xx; (x < xx + blur_size && x < width); x++) {
                for (int y = yy; (y < yy + blur_size && y < height); y++) {
                    i = (x + (y * width)) * COLOR_SIZE;
                    p[i] = avg_r;
                    p[i + 1] = avg_g;
                    p[i + 2] = avg_b;
                }
            }
        }
    }
}

#endif

static inline void img_image_convolution_filter(Image *image, float *kernel, int kw, int kh) {
    int offsetX = (kw - 1) / 2;
    int offsetY = (kh - 1) / 2;
    float r, g, b, k;
    uint width = image->width, height = image->height;
    size_t size = width * height * 4;
    Color *src = (Color *)image->pixels, *il, *ol, *pixel;
    Color *buffer = xmalloc(size);
    for (int y = 0; y < height; y++) {
        ol = &buffer[y * width];
        for (int x = 0; x < width; x++) {
            r = g = b = 0.0f;
            for (int j = 0; j < kh; j++) {
                if (y + j < offsetY || y + j - offsetY >= height)
                    continue;
                il = &src[(y + j - offsetY) * width];
                for (int i = 0; i < kw; i++) {
                    if (x + i < offsetX || x + i - offsetX >= width)
                        continue;
                    k = kernel[i + j * kw];
                    pixel = &il[x + i - offsetX];
                    r += k * pixel->r;
                    g += k * pixel->g;
                    b += k * pixel->b;
                }
            }
            ol[x].r = (unsigned char)fclamp(r, 0.0f, 255.0f);
            ol[x].g = (unsigned char)fclamp(g, 0.0f, 255.0f);
            ol[x].b = (unsigned char)fclamp(b, 0.0f, 255.0f);
            ol[x].a = src[x].a;
        }
    }
    xfree(src);
    image->pixels = (unsigned char *)buffer;
}

VALUE img_image_box_blur(VALUE self) {
    // float *kernel = xmalloc(sizeof(float) * 9);
    // for (int i = 0; i < 9; i++)
    //     kernel[i] = -1.0f;
    // kernel[4] = 8.0f;

    float kernel[9] = {-1, -1, -1,
                       -1, 8, -1,
                       -1, -1, -1};

    IMAGE();

    Image *t = ALLOC(Image);
    t->width = image->width;
    t->height = image->height;

    img_image_convolution_filter(image, &kernel[0], 3, 3);

    // xfree(kernel);
    return self;
}
