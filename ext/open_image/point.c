
#include "point.h"

VALUE cPoint;

void Init_img_point(VALUE module) {
    cPoint = rb_define_class_under(module, "Point", rb_cObject);
    rb_define_alloc_func(cPoint, img_point_alloc);
    rb_define_method(cPoint, "initialize", img_point_initialize, -1);

    rb_define_method(cPoint, "set", img_point_set, 2);
    rb_define_method(cPoint, "x", img_point_get_x, 0);
    rb_define_method(cPoint, "y", img_point_get_y, 0);
    rb_define_method(cPoint, "x=", img_point_set_x, 1);
    rb_define_method(cPoint, "y=", img_point_set_y, 1);

    rb_define_method(cPoint, "to_a", img_point_to_a, 0);
    rb_define_method(cPoint, "to_h", img_point_to_h, 0);
    rb_define_method(cPoint, "to_s", img_point_to_s, 0);
    rb_define_method(cPoint, "dup", img_point_dup, 0);
    rb_define_method(cPoint, "==", img_point_eql, 1);

    rb_define_method(cPoint, "offset", img_point_offset, -1);
    rb_define_method(cPoint, "offset!", img_point_offset_bang, -1);

    rb_define_alias(cPoint, "to_ary", "to_a");
    rb_define_alias(cPoint, "to_str", "to_s");

    rb_define_method(cPoint, "_dump", img_point_dump, -1);
    rb_define_method(cPoint, "pack", img_point_dump, -1);
    rb_define_singleton_method(cPoint, "_load", img_point_load, 1);
    rb_define_singleton_method(cPoint, "unpack", img_point_load, 1);
}

VALUE img_point_alloc(VALUE klass) {
    Point *point = ALLOC(Point);
    memset(point, 0, sizeof(Point));
    RETURN_WRAP_STRUCT(klass, point);
}

VALUE img_point_initialize(int argc, VALUE *argv, VALUE self) {
    POINT();
    switch (argc) {
        case 0:
            break;
        case 1: {
            Size *size;
            Data_Get_Struct(argv[0], Size, size);
            point->x = size->width;
            point->y = size->height;
            break;
        }
        case 2: {
            point->x = NUM2INT(argv[0]);
            point->y = NUM2INT(argv[1]);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 1, 2)", argc);
            break;
    }
    return Qnil;
}

VALUE img_point_get_x(VALUE self) {
    POINT();
    return INT2NUM(point->x);
}

VALUE img_point_get_y(VALUE self) {
    POINT();
    return INT2NUM(point->y);
}

VALUE img_point_set_x(VALUE self, VALUE value) {
    POINT();
    point->x = NUM2INT(value);
    return value;
}

VALUE img_point_set_y(VALUE self, VALUE value) {
    POINT();
    point->y = NUM2INT(value);
    return value;
}

VALUE img_point_to_a(VALUE self) {
    POINT();
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(point->x));
    rb_ary_store(ary, 1, INT2NUM(point->y));
    return ary;
}

VALUE img_point_to_h(VALUE self) {
    POINT();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, STR2SYM("x"), INT2NUM(point->x));
    rb_hash_aset(hash, STR2SYM("y"), INT2NUM(point->y));
    return hash;
}

VALUE img_point_to_s(VALUE self) {
    POINT();
    return rb_sprintf("<Point: x:%d, y:%d>", point->x, point->y);
}

VALUE img_point_dup(VALUE self) {
    struct RData *rdata = RDATA(self);
    Point *clone = ALLOC(Point);
    memcpy(clone, rdata->data, sizeof(Point));
    RETURN_WRAP_STRUCT(rdata->basic.klass, clone);
}

VALUE img_point_set(VALUE self, VALUE x, VALUE y) {
    POINT();
    point->x = NUM2INT(x);
    point->y = NUM2INT(y);
    return self;
}

VALUE img_point_offset(int argc, VALUE *argv, VALUE self) {
    Point *p1, *result;
    Data_Get_Struct(self, Point, p1);
    result = ALLOC(Point);
    if (argc == 1)
    {
        Point *p2;
        Data_Get_Struct(argv[0], Point, p2);
        result->x = p1->x + p2->x;
        result->y = p1->y + p2->y;
    }
    else if (argc == 2)
    {
        result->x = p1->x + NUM2INT(argv[0]);
        result->y = p1->y + NUM2INT(argv[1]);
    }
    else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);
    RETURN_WRAP_STRUCT(CLASS_OF(self), result);
}

VALUE img_point_offset_bang(int argc, VALUE *argv, VALUE self) {
    POINT();
    if (argc == 1)
    {
        Point *p2;
        Data_Get_Struct(argv[0], Point, p2);
        point->x = point->x + p2->x;
        point->y = point->y + p2->y;
    }
    else if (argc == 2)
    {
        point->x = point->x + NUM2INT(argv[0]);
        point->y = point->y + NUM2INT(argv[1]);
    }
    else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);
    return self;
}

VALUE img_point_dump(int argc, VALUE *argv, VALUE self) {
    RB_MARSHAL_DUMP(Point);
}

VALUE img_point_load(VALUE klass, VALUE binary) {
    RB_MARSHAL_LOAD(Point);
}

VALUE img_point_eql(VALUE self, VALUE other) {
    RB_DATA_EQL(Point);
}