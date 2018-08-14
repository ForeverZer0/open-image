
#include "image.h"

#define IMAGE()   \
    Image *image; \
    Data_Get_Struct(self, Image, image);

VALUE rb_cOpenImage;
VALUE rb_cOpenImagePointer;

void Init_open_image_image(VALUE module) {
    rb_cOpenImage = rb_define_class_under(module, "Image", rb_cObject);

    rb_define_alloc_func(rb_cOpenImage, open_image_alloc);
    rb_define_method(rb_cOpenImage, "initialize", open_image_initialize, -1);

    rb_define_method(rb_cOpenImage, "width", open_image_width, 0);
    rb_define_method(rb_cOpenImage, "height", open_image_height, 0);
    rb_define_method(rb_cOpenImage, "pixels", open_image_pixels, 0);

    rb_define_method(rb_cOpenImage, "ptr", open_image_ptr, 0);

    rb_define_method(rb_cOpenImage, "save_png", open_image_save_png, 1);
    rb_define_method(rb_cOpenImage, "save_jpg", open_image_save_jpg, -1);
    rb_define_method(rb_cOpenImage, "save_bmp", open_image_save_bmp, 1);
    rb_define_method(rb_cOpenImage, "save_tga", open_image_save_tga, 1);

    rb_define_alias(rb_cOpenImage, "rows", "height");
    rb_define_alias(rb_cOpenImage, "columns", "width");
    rb_define_alias(rb_cOpenImage, "to_blob", "pixels");
}

void open_image_free(void *data) {
    Image *image = (Image *)data;
    xfree(image->pixels);
    xfree(image);
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

    if (argc == 1) // From File
    {
        Check_Type(arg1, T_STRING);
        const char *filename = StringValueCStr(arg1);
        if (flip)
            stbi_set_flip_vertically_on_load(TRUE);

        int n;
        image->pixels = (unsigned char*) stbi_load(filename, &image->width, &image->height, &n, 4);

        if (flip)
            stbi_set_flip_vertically_on_load(FALSE);
    }
    else // From Dimensions
    {
        uint w = NUM2UINT(arg1);
        uint h = NUM2UINT(arg2);
        size_t size = w * h * 4;

        image->width = w;
        image->height = h;
        image->pixels = xmalloc(size);

        VALUE c = Qnil;
        if (!NIL_P(options))
            c = rb_hash_aref(options, ID2SYM(rb_intern("color")));

        if (NIL_P(c))
            memset(image->pixels, 0, size);
        else
        {
            Color *color;
            Data_Get_Struct(c, Color, color);
            
            // TODO: Implement

            // size_t sz = sizeof(Color);
            // Color *src = (Color*) image->pixels;
            // for (int i = 0; i < size; i += sz)
            //     memcpy(src + i, color, sz);
        }
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
    long size = (long)(image->width * image->height * 4);
    return rb_str_new(image->pixels, size);
}

VALUE open_image_ptr(VALUE self) {
    if (!rb_cOpenImagePointer)
    {
        rb_require("fiddle");
        VALUE fiddle = rb_const_get(rb_cObject, rb_intern("Fiddle"));
        rb_cOpenImagePointer = rb_const_get(fiddle, rb_intern("Pointer"));
    }

    IMAGE();
    VALUE *args = xmalloc(sizeof(VALUE) * 2);
    args[0] = LL2NUM((size_t) &image->pixels);
    args[1] = UINT2NUM(image->width * image->height * 4);
    VALUE pointer = rb_obj_alloc(rb_cOpenImagePointer);
    rb_obj_call_init(pointer, 2, args);
    xfree(args);
    return pointer; 
}

VALUE open_image_save_png(VALUE self, VALUE path) {
    IMAGE();
}

VALUE open_image_save_jpg(int argc, VALUE *argv, VALUE self) {
    IMAGE();
    VALUE path, quality;
    rb_scan_args(argc, argv, "11", &path, &quality);

    int q = NIL_P(quality) ? 90 : NUM2INT(quality);
    const char *filename = StringValueCStr(path);

    int result = stbi_write_jpg(filename, image->width, image->height, 4, image->pixels, q);
    return result ? Qtrue : Qfalse;
}

VALUE open_image_save_tga(VALUE self, VALUE path) {
    IMAGE();

}

VALUE open_image_save_bmp(VALUE self, VALUE path) {
    IMAGE();

}