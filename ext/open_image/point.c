
#include "point.h"

VALUE rb_cOpenImagePoint;

void Init_open_image_point(VALUE module) {
    rb_cOpenImagePoint = rb_define_class_under(module, "Point", rb_cObject);

    rb_define_method(rb_cOpenImagePoint, "x", open_image_point_get_x, 0);
    rb_define_method(rb_cOpenImagePoint, "y", open_image_point_get_y, 0);
    rb_define_method(rb_cOpenImagePoint, "x=", open_image_point_set_x, 1);
    rb_define_method(rb_cOpenImagePoint, "y=", open_image_point_set_y, 1);

    rb_define_method(rb_cOpenImagePoint, "to_a", open_image_point_to_a, 0);
    rb_define_method(rb_cOpenImagePoint, "to_h", open_image_point_to_h, 0);
    rb_define_method(rb_cOpenImagePoint, "to_s", open_image_point_to_s, 0);
    rb_define_alias(rb_cOpenImagePoint, "to_str", "to_s");
    rb_define_method(rb_cOpenImagePoint, "dup", open_image_point_dup, 0);
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

VALUE open_image_point_to_a(VALUE self) {
    POINT();
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(point->x));
    rb_ary_store(ary, 1, INT2NUM(point->y));
    return ary;
}

VALUE open_image_point_to_h(VALUE self) {
    POINT();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, STR2SYM("x"), INT2NUM(point->x));
    rb_hash_aset(hash, STR2SYM("y"), INT2NUM(point->y));
    return hash;
}

VALUE open_image_point_to_s(VALUE self) {
    POINT();
    return rb_sprintf("<Point: x:%d, y:%d>", point->x, point->y);
}

VALUE open_image_point_dup(VALUE self) {
    struct RData *rdata = RDATA(self);
    Point *clone = ALLOC(Point);
    memcpy(clone, rdata->data, sizeof(Point));
    RETURN_WRAP_STRUCT(rdata->basic.klass, clone);
}