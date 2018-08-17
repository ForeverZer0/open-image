#ifndef OPEN_IMAGE_RECT_H
#define OPEN_IMAGE_RECT_H 1

#include "common.h"

void Init_img_rect(VALUE module);
VALUE img_rect_alloc(VALUE klass);
VALUE img_rect_initialize(int argc, VALUE *argv, VALUE self);
VALUE img_rect_from_ltrb(VALUE klass, VALUE left, VALUE top, VALUE right, VALUE bottom);

VALUE img_rect_set(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height);
VALUE img_rect_get_x(VALUE self);
VALUE img_rect_get_y(VALUE self);
VALUE img_rect_get_width(VALUE self);
VALUE img_rect_get_height(VALUE self);
VALUE img_rect_set_x(VALUE self, VALUE value);
VALUE img_rect_set_y(VALUE self, VALUE value);
VALUE img_rect_set_width(VALUE self, VALUE value);
VALUE img_rect_set_height(VALUE self, VALUE value);
VALUE img_rect_right(VALUE self);
VALUE img_rect_bottom(VALUE self);

VALUE img_rect_empty_p(VALUE self);
VALUE img_rect_area(VALUE self);
VALUE img_rect_perimeter(VALUE self);

VALUE img_rect_get_location(VALUE self);
VALUE img_rect_get_size(VALUE self);
VALUE img_rect_set_location(VALUE self, VALUE value);
VALUE img_rect_set_size(VALUE self, VALUE value);

VALUE img_rect_to_a(VALUE self);
VALUE img_rect_to_h(VALUE self);
VALUE img_rect_to_s(VALUE self);
VALUE img_rect_dup(VALUE self);

VALUE img_rect_offset(int argc, VALUE *argv, VALUE self);
VALUE img_rect_offset_bang(int argc, VALUE *argv, VALUE self);
VALUE img_rect_inflate(int argc, VALUE *argv, VALUE self);
VALUE img_rect_inflate_bang(int argc, VALUE *argv, VALUE self);
VALUE img_rect_intersect(VALUE self, VALUE other);
VALUE img_rect_intersect_bang(VALUE self, VALUE other);
VALUE img_rect_intersects_p(VALUE self, VALUE other);
VALUE img_rect_union(VALUE self, VALUE other);
VALUE img_rect_union_bang(VALUE self, VALUE other);

VALUE img_rect_include_p(int argc, VALUE *argv, VALUE self);
VALUE img_rect_dump(int argc, VALUE *argv, VALUE self);
VALUE img_rect_load(VALUE klass, VALUE binary);

#endif /* OPEN_IMAGE_RECT_H */