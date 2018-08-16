
#include "rect.h"

VALUE cRect;

#define RECT()  \
    Rect *rect; \
    Data_Get_Struct(self, Rect, rect)

void Init_img_rect(VALUE module) {
    cRect = rb_define_class_under(module, "Rect", rb_cObject);
    rb_define_alloc_func(cRect, img_rect_alloc);
    rb_define_method(cRect, "initialize", img_rect_initialize, -1);
    rb_define_singleton_method(cRect, "from_ltrb", img_rect_from_ltrb, 4);
    rb_define_singleton_method(cRect, "empty", img_rect_alloc, 0);

    rb_define_method(cRect, "empty?", img_rect_empty_p, 0);


    rb_define_method(cRect, "x", img_rect_get_x, 0);
    rb_define_method(cRect, "y", img_rect_get_y, 0);
    rb_define_method(cRect, "width", img_rect_get_width, 0);
    rb_define_method(cRect, "height", img_rect_get_height, 0);
    rb_define_method(cRect, "x=", img_rect_set_x, 1);
    rb_define_method(cRect, "y=", img_rect_set_y, 1);
    rb_define_method(cRect, "width=", img_rect_set_width, 1);
    rb_define_method(cRect, "height=", img_rect_set_height, 1);

    rb_define_alias(cRect, "left", "x");
    rb_define_alias(cRect, "top", "y");
    rb_define_method(cRect, "right", img_rect_right, 0);
    rb_define_method(cRect, "bottom", img_rect_bottom, 0);
    rb_define_method(cRect, "area", img_rect_area, 0);
    rb_define_method(cRect, "perimeter", img_rect_perimeter, 0);

    rb_define_method(cRect, "location", img_rect_get_location, 0);
    rb_define_method(cRect, "size", img_rect_get_size, 0);
    rb_define_method(cRect, "location=", img_rect_set_location, 1);
    rb_define_method(cRect, "size=", img_rect_set_size, 1);

    rb_define_method(cRect, "to_a", img_rect_to_a, 0);
    rb_define_method(cRect, "to_h", img_rect_to_h, 0);
    rb_define_method(cRect, "to_s", img_rect_to_s, 0);
    rb_define_alias(cRect, "to_str", "to_s");
    rb_define_method(cRect, "dup", img_rect_dup, 0);
}

VALUE img_rect_alloc(VALUE klass) {
    Rect *rect = ALLOC(Rect);
    memset(rect, 0, sizeof(Rect));
    RETURN_WRAP_STRUCT(klass, rect);
}

VALUE img_rect_initialize(int argc, VALUE *argv, VALUE self) {
    RECT();
    switch (argc) {
        case 0:
            break;
        case 2: {
            Point *point;
            Size *size;
            Data_Get_Struct(argv[0], Point, point);
            Data_Get_Struct(argv[1], Size, size);
            rect->x = point->x;
            rect->y = point->y;
            rect->width = size->width;
            rect->height = size->height;
        }
        case 3: {
            if (FIXNUM_P(argv[0])) {
                Size *s;
                Data_Get_Struct(argv[2], Size, s);
                rect->x = NUM2INT(argv[0]);
                rect->y = NUM2INT(argv[1]);
                rect->width = s->width;
                rect->height = s->height;
            } else {
                Point *p;
                Data_Get_Struct(argv[0], Point, p);
                rect->x = p->x;
                rect->y = p->y;
                rect->width = NUM2INT(argv[1]);
                rect->height = NUM2INT(argv[2]);
            }
        }
        case 4: {
            rect->x = NUM2INT(argv[0]);
            rect->y = NUM2INT(argv[1]);
            rect->width = NUM2INT(argv[2]);
            rect->height = NUM2INT(argv[3]);
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 2, 3, 4)", argc);
    }
    return Qnil;
}

VALUE img_rect_from_ltrb(VALUE klass, VALUE left, VALUE top, VALUE right, VALUE bottom) {
    Rect *rect = ALLOC(Rect);
    int x = NUM2INT(left), y = NUM2INT(top);
    rect->x = x;
    rect->y = y;
    rect->width = NUM2INT(right) - x;
    rect->height = NUM2INT(bottom) - y;
    RETURN_WRAP_STRUCT(klass, rect);
}

VALUE img_rect_empty_p(VALUE self) {
    RECT();
    return rect->x == 0 && rect->y == 0 && rect->width == 0 && rect->height == 0 ? Qtrue : Qfalse;
}

VALUE img_rect_get_x(VALUE self) {
    RECT();
    return INT2NUM(rect->x);
}

VALUE img_rect_get_y(VALUE self) {
    RECT();
    return INT2NUM(rect->y);
}

VALUE img_rect_get_width(VALUE self) {
    RECT();
    return INT2NUM(rect->width);
}

VALUE img_rect_get_height(VALUE self) {
    RECT();
    return INT2NUM(rect->height);
}

VALUE img_rect_set_x(VALUE self, VALUE value) {
    RECT();
    rect->x = NUM2INT(value);
    return value;
}

VALUE img_rect_set_y(VALUE self, VALUE value) {
    RECT();
    rect->y = NUM2INT(value);
    return value;
}

VALUE img_rect_set_width(VALUE self, VALUE value) {
    RECT();
    rect->width = NUM2INT(value);
    return value;
}

VALUE img_rect_set_height(VALUE self, VALUE value) {
    RECT();
    rect->height = NUM2INT(value);
    return value;
}

VALUE img_rect_get_location(VALUE self) {
    RECT();
    Point *point = ALLOC(Point);
    point->x = rect->x;
    point->y = rect->y;
    RETURN_WRAP_STRUCT(cPoint, point);
}

VALUE img_rect_get_size(VALUE self) {
    RECT();
    Size *size = ALLOC(Size);
    size->width = rect->width;
    size->height = rect->height;
    RETURN_WRAP_STRUCT(cSize, size);
}

VALUE img_rect_set_location(VALUE self, VALUE value) {
    RECT();
    Point *point;
    Data_Get_Struct(value, Point, point);
    rect->x = point->x;
    rect->y = point->y;
    return value;
}

VALUE img_rect_set_size(VALUE self, VALUE value) {
    RECT();
    Size *size;
    Data_Get_Struct(value, Size, size);
    rect->width = size->width;
    rect->height = size->height;
    return value;
}

VALUE img_rect_to_a(VALUE self) {
    RECT();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, INT2NUM(rect->x));
    rb_ary_store(ary, 1, INT2NUM(rect->y));
    rb_ary_store(ary, 2, INT2NUM(rect->width));
    rb_ary_store(ary, 3, INT2NUM(rect->height));
    return ary;
}

VALUE img_rect_to_h(VALUE self) {
    RECT();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, STR2SYM("x"), INT2NUM(rect->x));
    rb_hash_aset(hash, STR2SYM("y"), INT2NUM(rect->y));
    rb_hash_aset(hash, STR2SYM("width"), INT2NUM(rect->width));
    rb_hash_aset(hash, STR2SYM("height"), INT2NUM(rect->height));
    return hash;
}

VALUE img_rect_to_s(VALUE self) {
    RECT();
    return rb_sprintf("<Rect: x:%d, y:%d, width:%d, height:%d>", rect->x, rect->y, rect->width, rect->height);
}

VALUE img_rect_dup(VALUE self) {
    struct RData *rdata = RDATA(self);
    Rect *clone = ALLOC(Rect);
    memcpy(clone, rdata->data, sizeof(Rect));
    RETURN_WRAP_STRUCT(rdata->basic.klass, clone);
}

VALUE img_rect_right(VALUE self) {
    RECT();
    return INT2NUM(rect->x + rect->width);
}

VALUE img_rect_bottom(VALUE self) {
    RECT();
    return INT2NUM(rect->y + rect->height);
}

VALUE img_rect_area(VALUE self) {
    RECT();
    return INT2NUM(abs(rect->width * rect->height));
}

VALUE img_rect_perimeter(VALUE self) {
    RECT();
    return INT2NUM((abs(rect->width) + abs(rect->height)) * 2);
}