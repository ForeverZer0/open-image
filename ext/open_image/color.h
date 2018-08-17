
#ifndef RB_OPEN_IMAGE_COLOR_H
#define RB_OPEN_IMAGE_COLOR_H 1

#include <string.h>
#include "common.h"

static inline void img_color_hsb2rgb(Color *color, float hue, float saturation, float brightness);
static inline void img_color_hsl2rgb(Color *color, float hue, float saturation, float brightness);
static inline void img_color_hsl2hsb(float in_s, float in_l, float *out_s, float *out_b);

void Init_img_color(VALUE module);
VALUE img_color_alloc(VALUE klass);
VALUE img_color_initialize(int argc, VALUE *argv, VALUE self);
VALUE img_color_from_hsb(int argc, VALUE *argv, VALUE klass);
VALUE img_color_from_hsl(int argc, VALUE *argv, VALUE klass);

VALUE img_color_get_r(VALUE self);
VALUE img_color_get_g(VALUE self);
VALUE img_color_get_b(VALUE self);
VALUE img_color_get_a(VALUE self);

VALUE img_color_getf_r(VALUE self);
VALUE img_color_getf_g(VALUE self);
VALUE img_color_getf_b(VALUE self);
VALUE img_color_getf_a(VALUE self);

VALUE img_color_set_r(VALUE self, VALUE value);
VALUE img_color_set_g(VALUE self, VALUE value);
VALUE img_color_set_b(VALUE self, VALUE value);
VALUE img_color_set_a(VALUE self, VALUE value);

VALUE img_color_to_a(VALUE self);
VALUE img_color_to_h(VALUE self);
VALUE img_color_to_s(VALUE self);
VALUE img_color_to_i(VALUE self);
VALUE img_color_gl(VALUE self);
VALUE img_color_hsb(VALUE self);
VALUE img_color_hsl(VALUE self);
VALUE img_color_html(VALUE self);

VALUE img_color_hue(VALUE self);
VALUE img_color_saturation(VALUE self);
VALUE img_color_lightness(VALUE self);
VALUE img_color_brightness(VALUE self);

VALUE img_color_lerp(VALUE self, VALUE other, VALUE amount);
VALUE img_color_lerp_bang(VALUE self, VALUE other, VALUE amount);

VALUE img_color_dump(int argc, VALUE *argv, VALUE self);
VALUE img_color_load(VALUE klass, VALUE binary);

#endif /* RB_OPEN_IMAGE_COLOR_H */