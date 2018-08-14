#ifndef OPEN_IMAGE_RECT_H
#define OPEN_IMAGE_RECT_H 1

#include "common.h"

void Init_open_image_rect(VALUE module);
VALUE open_image_rect_alloc(VALUE klass);
VALUE open_image_rect_initialize(int argc, VALUE *argv, VALUE self);

VALUE open_image_rect_get_x(VALUE self);
VALUE open_image_rect_get_y(VALUE self);
VALUE open_image_rect_get_width(VALUE self);
VALUE open_image_rect_get_height(VALUE self);
VALUE open_image_rect_set_x(VALUE self, VALUE value);
VALUE open_image_rect_set_y(VALUE self, VALUE value);
VALUE open_image_rect_set_width(VALUE self, VALUE value);
VALUE open_image_rect_set_height(VALUE self, VALUE value);

VALUE open_image_rect_get_location(VALUE self);
VALUE open_image_rect_get_size(VALUE self);
VALUE open_image_rect_set_location(VALUE self, VALUE value);
VALUE open_image_rect_set_size(VALUE self, VALUE value);

#endif /* OPEN_IMAGE_RECT_H */