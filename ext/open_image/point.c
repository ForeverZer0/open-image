
#include "point.h"

VALUE rb_cOpenImagePoint;

void Init_open_image_point(VALUE module) {
    rb_cOpenImagePoint = rb_define_class_under(module, "Point", rb_cObject);

    rb_define_method(rb_cOpenImagePoint, "x", open_image_point_get_x, 0);
    rb_define_method(rb_cOpenImagePoint, "y", open_image_point_get_y, 0);
    rb_define_method(rb_cOpenImagePoint, "x=", open_image_point_set_x, 1);
    rb_define_method(rb_cOpenImagePoint, "y=", open_image_point_set_y, 1);
}

VALUE open_image_point_alloc(VALUE klass) {
    Point *point = ALLOC(Point);
    memset(point, 0, sizeof(Point));
    RETURN_WRAP_STRUCT(klass, point);
}

VALUE open_image_point_initialize(int argc, VALUE *argv, VALUE self) {
    POINT();
    switch (argc) {
        case 0:
            break;
        case 1: {
            Size *size;
            Data_Get_Struct(argv[0], Size, size);
            point->x = size->width;
            point->y = size->height;
        }
        case 2: {
            point->x = NUM2INT(argv[0]);
            point->y = NUM2INT(argv[1]);
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 1, 2)", argc);
    }
    return Qnil;
}

VALUE open_image_point_get_x(VALUE self) {
    POINT();
    return INT2NUM(point->x);
}

VALUE open_image_point_get_y(VALUE self) {
    POINT();
    return INT2NUM(point->y);
}

VALUE open_image_point_set_x(VALUE self, VALUE value) {
    POINT();
    point->x = NUM2INT(value);
    return value;
}

VALUE open_image_point_set_y(VALUE self, VALUE value) {
    POINT();
    point->y = NUM2INT(value);
    return value;
}