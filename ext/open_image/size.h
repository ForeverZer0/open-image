#ifndef OPEN_IMAGE_SIZE_H
#define OPEN_IMAGE_SIZE_H 1

#include "common.h"

void Init_img_size(VALUE module);
VALUE img_size_alloc(VALUE klass);
VALUE img_size_initialize(int argc, VALUE *argv, VALUE self);

VALUE img_size_set(VALUE self, VALUE width, VALUE height);
VALUE img_size_get_width(VALUE self);
VALUE img_size_get_height(VALUE self);
VALUE img_size_set_width(VALUE self, VALUE value);
VALUE img_size_set_height(VALUE self, VALUE value);

VALUE img_size_to_a(VALUE self);
VALUE img_size_to_h(VALUE self);
VALUE img_size_to_s(VALUE self);
VALUE img_size_dup(VALUE self);
VALUE img_size_eql(VALUE self, VALUE other);

VALUE img_size_dump(int argc, VALUE *argv, VALUE self);
VALUE img_size_load(VALUE klass, VALUE binary);

#endif /* OPEN_IMAGE_SIZE_H */