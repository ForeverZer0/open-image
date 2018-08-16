#include "open_image.h"

VALUE mOpenImage;
VALUE cImage;
VALUE eOpenImageError;

void Init_open_image(void) {
    mOpenImage = rb_define_module("OpenImage");
    eOpenImageError = rb_define_class_under(mOpenImage, "Error", rb_eStandardError);

    Init_img_point(mOpenImage);
    Init_img_size(mOpenImage);
    Init_img_rect(mOpenImage);
    Init_img_color(mOpenImage);
    Init_img_image(mOpenImage);
}
