#ifndef OPEN_IMAGE_SIZE_H
#define OPEN_IMAGE_SIZE_H 1

#include "common.h"

void Init_open_image_size(VALUE module);
VALUE open_image_size_alloc(VALUE klass);
VALUE open_image_size_initialize(int argc, VALUE *argv, VALUE self);

VALUE open_image_size_get_width(VALUE self);
VALUE open_image_size_get_height(VALUE self);
VALUE open_image_size_set_width(VALUE self, VALUE value);
VALUE open_image_size_set_height(VALUE self, VALUE value);

#endif /* OPEN_IMAGE_SIZE_H */