
#include "rect.h"

VALUE rb_cOpenImageRect;

#define RECT()  \
    Rect *rect; \
    Data_Get_Struct(self, Rect, rect)

void Init_open_image_rect(VALUE module) {
    rb_cOpenImageRect = rb_define_class_under(module, "Rect", rb_cObject);

    rb_define_method(rb_cOpenImageRect, "x", open_image_rect_get_x, 0);
    rb_define_method(rb_cOpenImageRect, "y", open_image_rect_get_y, 0);
    rb_define_method(rb_cOpenImageRect, "width", open_image_rect_get_width, 0);
    rb_define_method(rb_cOpenImageRect, "height", open_image_rect_get_height, 0);
    rb_define_method(rb_cOpenImageRect, "x=", open_image_rect_set_x, 1);
    rb_define_method(rb_cOpenImageRect, "y=", open_image_rect_set_y, 1);
    rb_define_method(rb_cOpenImageRect, "width=", open_image_rect_set_width, 1);
    rb_define_method(rb_cOpenImageRect, "height=", open_image_rect_set_height, 1);

    rb_define_method(rb_cOpenImageRect, "location", open_image_rect_get_location, 0);
    rb_define_method(rb_cOpenImageRect, "size", open_image_rect_get_size, 0);
    rb_define_method(rb_cOpenImageRect, "location=", open_image_rect_set_location, 1);
    rb_define_method(rb_cOpenImageRect, "size=", open_image_rect_set_size, 1);
}

VALUE open_image_rect_alloc(VALUE klass) {
    Rect *rect = ALLOC(Rect);
    memset(rect, 0, sizeof(Rect));
    RETURN_WRAP_STRUCT(klass, rect);
}

VALUE open_image_rect_initialize(int argc, VALUE *argv, VALUE self) {
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

VALUE open_image_rect_get_x(VALUE self) {
    RECT();
    return INT2NUM(rect->x);
}

VALUE open_image_rect_get_y(VALUE self) {
    RECT();
    return INT2NUM(rect->y);
}

VALUE open_image_rect_get_width(VALUE self) {
    RECT();
    return INT2NUM(rect->width);
}

VALUE open_image_rect_get_height(VALUE self) {
    RECT();
    return INT2NUM(rect->height);
}

VALUE open_image_rect_set_x(VALUE self, VALUE value) {
    RECT();
    rect->x = NUM2INT(value);
    return value;
}

VALUE open_image_rect_set_y(VALUE self, VALUE value) {
    RECT();
    rect->y = NUM2INT(value);
    return value;
}

VALUE open_image_rect_set_width(VALUE self, VALUE value) {
    RECT();
    rect->width = NUM2INT(value);
    return value;
}

VALUE open_image_rect_set_height(VALUE self, VALUE value) {
    RECT();
    rect->height = NUM2INT(value);
    return value;
}

VALUE open_image_rect_get_location(VALUE self) {
    RECT();
    Point *point = ALLOC(Point);
    point->x = rect->x;
    point->y = rect->y;
    RETURN_WRAP_STRUCT(rb_cOpenImagePoint, point);
}

VALUE open_image_rect_get_size(VALUE self) {
    RECT();
    Size *size = ALLOC(Size);
    size->width = rect->width;
    size->height = rect->height;
    RETURN_WRAP_STRUCT(rb_cOpenImageSize, size);
}

VALUE open_image_rect_set_location(VALUE self, VALUE value) {
    RECT();
    Point *point;
    Data_Get_Struct(value, Point, point);
    rect->x = point->x;
    rect->y = point->y;
    return value;
}

VALUE open_image_rect_set_size(VALUE self, VALUE value) {
    RECT();
    Size *size;
    Data_Get_Struct(value, Size, size);
    rect->width = size->width;
    rect->height = size->height;
    return value;
}