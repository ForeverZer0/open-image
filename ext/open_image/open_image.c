#include "open_image.h"

VALUE mOpenImage;
VALUE eOpenImageError;

#if USE_FIDDLE
VALUE cFiddlePointer;
#endif

void Init_open_image(void) {
    mOpenImage = rb_define_module("OpenImage");
    eOpenImageError = rb_define_class_under(mOpenImage, "Error", rb_eStandardError);

    Init_img_point(mOpenImage);
    Init_img_size(mOpenImage);
    Init_img_rect(mOpenImage);
    Init_img_color(mOpenImage);
    Init_img_image(mOpenImage);

#if USE_FIDDLE
    rb_require("fiddle");
    VALUE fiddle = rb_const_get(rb_cObject, rb_intern("Fiddle"));
    cFiddlePointer = rb_const_get(fiddle, rb_intern("Pointer"));
#endif
}
