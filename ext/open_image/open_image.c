#include "open_image.h"

VALUE rb_mOpenImage;
VALUE rb_cOpenImage;
VALUE rb_eOpenImageError;

void Init_open_image(void) {
    rb_mOpenImage = rb_define_module("OpenImage");
    rb_eOpenImageError = rb_define_class_under(rb_mOpenImage, "Error", rb_eStandardError);

    Init_open_image_point(rb_mOpenImage);
    Init_open_image_size(rb_mOpenImage);
    Init_open_image_rect(rb_mOpenImage);
    Init_open_image_color(rb_mOpenImage);
    Init_open_image_image(rb_mOpenImage);
}
