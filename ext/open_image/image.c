
#include "image.h"

#define IMAGE()   \
    Image *image; \
    Data_Get_Struct(self, Image, image);

#define JPEG_QUALITY 90
#define COLOR_SIZE 4 /* For possible future expandment */

#define RETURN_WRAP_IMAGE(klass, img) return Data_Wrap_Struct(klass, NULL, img_image_free, img)
#define RETURN_DUP_IMAGE() return Data_Wrap_Struct(CLASS_OF(self), NULL, img_image_free, dup)

#define IMAGE_DUP()                                           \
    Image *image, *dup;                                       \
    Data_Get_Struct(self, Image, image);                      \
    dup = ALLOC(Image);                                       \
    dup->width = image->width;                                \
    dup->height = image->height;                              \
    size_t _size = image->width * image->height * COLOR_SIZE; \
    dup->pixels = xmalloc(_size);                             \
    memcpy(dup->pixels, image->pixels, _size)

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

#if OPEN_IMAGE_CONVOLUTION_FILTER

    rb_define_method(cImage, "filter", img_image_convolution_filter, 1);
    rb_define_method(cImage, "filter!", img_image_convolution_filter_bang, 1);

#if OPEN_IMAGE_BOX_BLUR
    rb_define_method(cImage, "box_blur", img_image_box_blur, 0);
    rb_define_method(cImage, "box_blur!", img_image_box_blur_bang, 0);
#endif

#if OPEN_IMAGE_GAUSSIAN_BLUR
    rb_define_method(cImage, "gaussian_blur", img_image_gaussian, 0);
    rb_define_method(cImage, "gaussian_blur!", img_image_gaussian_bang, 0);
#endif

#if OPEN_IMAGE_SHARPEN
    rb_define_method(cImage, "sharpen", img_image_sharpen, 0);
    rb_define_method(cImage, "sharpen!", img_image_sharpen_bang, 0);
#endif

#if OPEN_IMAGE_EDGE_DETECT
    rb_define_method(cImage, "edge_detect", img_image_edge_detect, 0);
    rb_define_method(cImage, "edge_detect!", img_image_edge_detect_bang, 0);
#endif

#if OPEN_IMAGE_EMBOSS
    rb_define_method(cImage, "emboss", img_image_emboss, 0);
    rb_define_method(cImage, "emboss!", img_image_emboss_bang, 0);
#endif

#if OPEN_IMAGE_BRIGHTEN
    rb_define_method(cImage, "brighten", img_image_brighten, 1);
    rb_define_method(cImage, "brighten!", img_image_brighten_bang, 1);
#endif

#if OPEN_IMAGE_BLUR
    rb_define_method(cImage, "blur", img_image_blur, 0);
    rb_define_method(cImage, "blur!", img_image_blur_bang, 0);
#endif

#if OPEN_IMAGE_LINE_DETECT
    rb_define_method(cImage, "line_detect", img_image_line_detect, 1);
    rb_define_method(cImage, "line_detect!", img_image_line_detect_bang, 1);
#endif

#endif /* OPEN_IMAGE_CONVOLUTION_FILTER */
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
        image->pixels = (unsigned char *)stbi_load(filename, &image->width, &image->height, &n, COLOR_SIZE);

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
    int result = stbi_write_png(filename, image->width, image->height, COLOR_SIZE, image->pixels, stride);
    return result ? Qtrue : Qfalse;
}

VALUE img_image_save_jpg(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    VALUE path, quality;
    rb_scan_args(argc, argv, "11", &path, &quality);

    int q = NIL_P(quality) ? JPEG_QUALITY : NUM2INT(quality);
    const char *filename = StringValueCStr(path);

    int result = stbi_write_jpg(filename, image->width, image->height, COLOR_SIZE, image->pixels, q);
    return result ? Qtrue : Qfalse;
}

VALUE img_image_save_tga(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int result = stbi_write_tga(filename, image->width, image->height, COLOR_SIZE, image->pixels);
    return result ? Qtrue : Qfalse;
}

VALUE img_image_save_bmp(VALUE self, VALUE path) {
    IMAGE();
    const char *filename = StringValueCStr(path);
    int result = stbi_write_bmp(filename, image->width, image->height, COLOR_SIZE, image->pixels);
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
    IMAGE_DUP();
    RETURN_DUP_IMAGE();
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
    RETURN_DUP_IMAGE();
}

VALUE img_image_grayscale_bang(int argc, VALUE *argv, VALUE self) {
    VALUE amount;
    rb_scan_args(argc, argv, "01", &amount);
    IMAGE();
    img_image_grayscale_s(image, amount);
    return self;
}

static inline void img_image_grayscale_s(Image *image, VALUE amount) {
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
    RETURN_DUP_IMAGE();
}

VALUE img_image_sepia_bang(VALUE self) {
    IMAGE();
    img_image_sepia_s(image);
    return self;
}

static inline void img_image_sepia_s(Image *image) {
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
    RETURN_DUP_IMAGE();
}

VALUE img_image_invert_bang(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    VALUE alpha;
    rb_scan_args(argc, argv, "01", &alpha);
    img_image_invert_s(image, RTEST(alpha));
    return self;
}

static inline void img_image_invert_s(Image *image, int alpha) {
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
    RETURN_DUP_IMAGE();
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

static inline void img_image_pixelate_s(Image *image, int pix, int avg) {
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
    RETURN_DUP_IMAGE();
}

VALUE img_image_solarize_bang(VALUE self, VALUE red, VALUE green, VALUE blue) {
    IMAGE();
    img_image_solarize_s(image, red, green, blue);
    return self;
}

static inline void img_image_solarize_s(Image *image, VALUE red, VALUE green, VALUE blue) {
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
    RETURN_DUP_IMAGE();
}

VALUE img_image_contrast_bang(VALUE self, VALUE contrast) {
    IMAGE();
    img_image_contrast_s(image, contrast);
    return self;
}

static inline void img_image_contrast_s(Image *image, VALUE contrast) {
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
    RETURN_DUP_IMAGE();
}

VALUE img_image_balance_bang(VALUE self, VALUE red, VALUE green, VALUE blue) {
    IMAGE();
    img_image_balance_s(image, red, green, blue);
    return self;
}

static inline void img_image_balance_s(Image *image, VALUE red, VALUE green, VALUE blue) {
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

#if OPEN_IMAGE_CONVOLUTION_FILTER

VALUE img_image_convolution_filter(VALUE self, VALUE matrix) {
    Check_Type(matrix, T_ARRAY);
    long kw, kh;
    kh = rb_array_len(matrix);
    if (kh % 2 != 0)
        rb_raise(eOpenImageError, "kernel for convolution filter must have odd-sized dimensions (given %d)", kh);
    float *kernel = xmalloc(sizeof(float) * (kh * kh));
    for (long i = 0; i < kh; i++) {
        VALUE row = rb_ary_entry(matrix, i);
        Check_Type(row, T_ARRAY);
        kw = rb_array_len(row);
        if (kw % 2 != 0)
            rb_raise(eOpenImageError, "kernel for convolution filter must have odd-sized dimensions (given %d)", kw);
        for (long j = 0; j < kw; j++)
            kernel[i + (j * kw)] = NUM2FLT(rb_ary_entry(row, j));
    }
    IMAGE_DUP();
    img_image_convolution_filter_s(dup, kernel, kw, kh);
    xfree(kernel);
    RETURN_DUP_IMAGE();
}

VALUE img_image_convolution_filter_bang(VALUE self, VALUE matrix) {
    Check_Type(matrix, T_ARRAY);
    long kw, kh;
    kh = rb_array_len(matrix);
    if (kh % 2 != 0)
        rb_raise(eOpenImageError, "kernel for convolution filter must have odd-sized dimensions (given %d)", kh);
    float *kernel = xmalloc(sizeof(float) * (kh * kh));
    for (long i = 0; i < kh; i++) {
        VALUE row = rb_ary_entry(matrix, i);
        Check_Type(row, T_ARRAY);
        kw = rb_array_len(row);
        if (kw % 2 != 0)
            rb_raise(eOpenImageError, "kernel for convolution filter must have odd-sized dimensions (given %d)", kw);
        for (long j = 0; j < kw; j++)
            kernel[i + (j * kw)] = NUM2FLT(rb_ary_entry(row, j));
    }
    IMAGE();
    img_image_convolution_filter_s(image, kernel, kw, kh);
    xfree(kernel);
    return self;
}

static inline void img_image_convolution_filter_s(Image *image, float *kernel, int kw, int kh) {
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

#if OPEN_IMAGE_BOX_BLUR

VALUE img_image_box_blur(VALUE self) {
    IMAGE_DUP();
    img_image_box_blur_s(dup);
    RETURN_DUP_IMAGE();
}

VALUE img_image_box_blur_bang(VALUE self) {
    IMAGE();
    img_image_box_blur_s(image);
    return self;
}

static inline void img_image_box_blur_s(Image *image) {
    float kernel[9];
    for (int i = 0; i < 9; i++)
        kernel[i] = 1.0f / 9.0f;
    img_image_convolution_filter_s(image, kernel, 3, 3);
}

#endif

#if OPEN_IMAGE_GAUSSIAN_BLUR

VALUE img_image_gaussian(VALUE self) {
    IMAGE_DUP();
    img_image_gaussian_s(dup);
    RETURN_DUP_IMAGE();
}

VALUE img_image_gaussian_bang(VALUE self) {
    IMAGE();
    img_image_box_blur_s(image);
    return self;
}

static inline void img_image_gaussian_s(Image *image) {
    float kernel[25] = {1.0f / 273.0f, 4.0f / 273.0f, 7.0f / 273.0f, 4.0f / 273.0f, 1.0f / 273.0f,
                        4.0f / 273.0f, 16.0f / 273.0f, 26.0f / 273.0f, 16.0f / 273.0f, 4.0f / 273.0f,
                        7.0f / 273.0f, 26.0f / 273.0f, 41.0f / 273.0f, 26.0f / 273.0f, 7.0f / 273.0f,
                        4.0f / 273.0f, 16.0f / 273.0f, 26.0f / 273.0f, 16.0f / 273.0f, 4.0f / 273.0f,
                        1.0f / 273.0f, 4.0f / 273.0f, 7.0f / 273.0f, 4.0f / 273.0f, 1.0f / 273.0f};
    img_image_convolution_filter_s(image, kernel, 7, 7);
}

#endif

#if OPEN_IMAGE_SHARPEN

VALUE img_image_sharpen(VALUE self) {
    IMAGE_DUP();
    img_image_sharpen_s(dup);
    RETURN_DUP_IMAGE();
}

VALUE img_image_sharpen_bang(VALUE self) {
    IMAGE();
    img_image_sharpen_s(image);
    return self;
}

static inline void img_image_sharpen_s(Image *image) {
    float kernel[9] = {-1.0f, -1.0f, -1.0f,
                       -1.0f, 9.0f, -1.0f,
                       -1.0f, -1.0f, -1.0f};
    img_image_convolution_filter_s(image, kernel, 3, 3);
}

#endif

#if OPEN_IMAGE_EDGE_DETECT

VALUE img_image_edge_detect(VALUE self) {
    IMAGE_DUP();
    img_image_edge_detect_s(dup);
    RETURN_DUP_IMAGE();
}

VALUE img_image_edge_detect_bang(VALUE self) {
    IMAGE();
    img_image_edge_detect_s(image);
    return self;
}

static inline void img_image_edge_detect_s(Image *image) {
    float kernel[9] = {-1.0f, -1.0f, -1.0f,
                       -1.0f, 8.0f, -1.0f,
                       -1.0f, -1.0f, -1.0f};
    img_image_convolution_filter_s(image, kernel, 3, 3);
}

#endif

#if OPEN_IMAGE_EMBOSS

VALUE img_image_emboss(VALUE self) {
    IMAGE_DUP();
    img_image_emboss_s(dup);
    RETURN_DUP_IMAGE();
}

VALUE img_image_emboss_bang(VALUE self) {
    IMAGE();
    img_image_emboss_s(image);
    return self;
}

static inline void img_image_emboss_s(Image *image) {
    float kernel[9] = {2.0f, 0.0f, 0.0f,
                       0.0f, -1.0f, 0.0f,
                       0.0f, 0.0f, -1.0f};
    img_image_convolution_filter_s(image, kernel, 3, 3);
}

#endif

#if OPEN_IMAGE_BRIGHTEN

VALUE img_image_brighten(VALUE self, VALUE level) {
    IMAGE_DUP();
    img_image_brighten_s(dup, level);
    RETURN_DUP_IMAGE();
}

VALUE img_image_brighten_bang(VALUE self, VALUE level) {
    IMAGE();
    img_image_brighten_s(image, level);
    return self;
}

static inline void img_image_brighten_s(Image *image, VALUE level) {
    float lvl = fclamp(NUM2FLT(level), 0.0f, 5.0f);
    float kernel[9] = {0.0f, 0.0f, 0.0f,
                       0.0f, lvl, 0.0f,
                       0.0f, 0.0f, 0.0f};
    img_image_convolution_filter_s(image, kernel, 3, 3);
}

#endif

#if OPEN_IMAGE_BLUR

VALUE img_image_blur(VALUE self) {
    IMAGE_DUP();
    img_image_blur_s(dup);
    RETURN_DUP_IMAGE();
}

VALUE img_image_blur_bang(VALUE self) {
    IMAGE();
    img_image_blur_s(image);
    return self;
}

static inline void img_image_blur_s(Image *image) {
    float kernel[49];
    for (int i = 0; i < 49; i++)
        kernel[i] = 1.0f / 49.0f;
    img_image_convolution_filter_s(image, kernel, 7, 7);
}

#endif

#if OPEN_IMAGE_LINE_DETECT

VALUE img_image_line_detect(VALUE self, VALUE direction) {
    IMAGE_DUP();
    img_image_line_detect_s(dup, direction);
    RETURN_DUP_IMAGE();
}

VALUE img_image_line_detect_bang(VALUE self, VALUE direction) {
    IMAGE();
    img_image_line_detect_s(image, direction);
    return self;
}

static inline void img_image_line_detect_s(Image *image, VALUE direction) {
    float *k = xmalloc(sizeof(float) * 9);
    int dir;
    if (RB_FIXNUM_P(direction)) {
        // If float, round to nearest 45°
        int a, b, d;
        float n = roundf(fabsf(NUM2FLT(direction)));
        d = ((int)n) % 360;
        a = (d / 45) * 45;
        b = a + 45;
        d = (d - a > b - d) ? b : a;
        switch (d) {
            case 45:
            case 225:
                dir = 1;
                break;
            case 90:
            case 270:
                dir = 2;
                break;
            case 135:
            case 315:
                dir = 3;
            default:
                dir = 0;
        }
    } else
        dir = NUM2INT(direction);
    switch (dir) {
        case 0:  // 0°, 180°, 360° (Vertical)
        {
            k[0] = k[2] = k[3] = k[5] = k[6] = k[8] = -1.0f;
            k[1] = k[4] = k[7] = 2.0f;
            break;
        }
        case 1:  // 45°, 225°
        {
            k[0] = k[1] = k[3] = k[5] = k[7] = k[8] = -1.0f;
            k[2] = k[4] = k[6] = 2.0f;
            break;
        }
        case 2:  //  90°, 270° (Horizontal)
        {
            k[0] = k[1] = k[2] = k[6] = k[7] = k[8] = -1.0f;
            k[3] = k[4] = k[5] = 2.0f;
            break;
        }
        case 3:  // 135°, 315°
        {
            k[1] = k[2] = k[3] = k[5] = k[6] = k[7] = -1.0f;
            k[0] = k[4] = k[8] = 2.0f;
            break;
        }
        default:
            rb_raise(eOpenImageError, "invalid angle specifier given (%d)", dir);
            break;
    }
    img_image_convolution_filter_s(image, k, 3, 3);
    xfree(k);
}

#endif

#endif /* OPEN_IMAGE_CONVOLUTION_FILTER */