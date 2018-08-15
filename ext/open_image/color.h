
#ifndef RB_OPEN_IMAGE_COLOR_H
#define RB_OPEN_IMAGE_COLOR_H 1

#include <string.h>
#include "common.h"

void Init_open_image_color(VALUE module);
VALUE open_image_color_alloc(VALUE klass);
VALUE open_image_color_initialize(int argc, VALUE *argv, VALUE self);

VALUE open_image_color_get_r(VALUE self);
VALUE open_image_color_get_g(VALUE self);
VALUE open_image_color_get_b(VALUE self);
VALUE open_image_color_get_a(VALUE self);

VALUE open_image_color_set_r(VALUE self, VALUE value);
VALUE open_image_color_set_g(VALUE self, VALUE value);
VALUE open_image_color_set_b(VALUE self, VALUE value);
VALUE open_image_color_set_a(VALUE self, VALUE value);

VALUE open_image_color_to_a(VALUE self);
VALUE open_image_color_to_h(VALUE self);
VALUE open_image_color_to_s(VALUE self);
VALUE open_image_color_to_i(VALUE self);

VALUE open_image_color_hue(VALUE self);
VALUE open_image_color_saturation(VALUE self);
VALUE open_image_color_brightness(VALUE self);
VALUE open_image_color_hsb(VALUE self);

VALUE open_image_color_lerp(VALUE self, VALUE other, VALUE amount);
VALUE open_image_color_lerp_bang(VALUE self, VALUE other, VALUE amount);

#endif /* RB_OPEN_IMAGE_COLOR_H */