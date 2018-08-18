#ifndef OPEN_IMAGE_POINT_H
#define OPEN_IMAGE_POINT_H 1

#include "common.h"

#define POINT()   \
    Point *point; \
    Data_Get_Struct(self, Point, point)

void Init_img_point(VALUE module);
VALUE img_point_alloc(VALUE klass);
VALUE img_point_initialize(int argc, VALUE *argv, VALUE self);

VALUE img_point_set(VALUE self, VALUE x, VALUE y);
VALUE img_point_get_x(VALUE self);
VALUE img_point_get_y(VALUE self);
VALUE img_point_set_x(VALUE self, VALUE value);
VALUE img_point_set_y(VALUE self, VALUE value);

VALUE img_point_offset(int argc, VALUE *argv, VALUE self);
VALUE img_point_offset_bang(int argc, VALUE *argv, VALUE self);

VALUE img_point_to_a(VALUE self);
VALUE img_point_to_h(VALUE self);
VALUE img_point_to_s(VALUE self);
VALUE img_point_dup(VALUE self);
VALUE img_point_eql(VALUE self, VALUE other);

VALUE img_point_dump(int argc, VALUE *argv, VALUE self);
VALUE img_point_load(VALUE klass, VALUE binary);

#endif /* OPEN_IMAGE_POINT_H */