#ifndef OPEN_IMAGE_POINT_H
#define OPEN_IMAGE_POINT_H 1

#include "common.h"

#define POINT() \
    Point *point; \
    Data_Get_Struct(self, Point, point)

void Init_open_image_point(VALUE module);
VALUE open_image_point_alloc(VALUE klass);
VALUE open_image_point_initialize(int argc, VALUE *argv, VALUE self);

VALUE open_image_point_get_x(VALUE self);
VALUE open_image_point_get_y(VALUE self);
VALUE open_image_point_set_x(VALUE self, VALUE value);
VALUE open_image_point_set_y(VALUE self, VALUE value);

#endif /* OPEN_IMAGE_POINT_H */