
#include "size.h"

VALUE rb_cOpenImageSize;

#define SIZE()  \
    Size *size; \
    Data_Get_Struct(self, Size, size)

void Init_open_image_size(VALUE module) {
    rb_cOpenImageSize = rb_define_class_under(module, "Size", rb_cObject);

    rb_define_method(rb_cOpenImageSize, "width", open_image_size_get_width, 0);
    rb_define_method(rb_cOpenImageSize, "height", open_image_size_get_height, 0);
    rb_define_method(rb_cOpenImageSize, "width=", open_image_size_set_width, 1);
    rb_define_method(rb_cOpenImageSize, "height=", open_image_size_set_height, 1);
}

VALUE open_image_size_alloc(VALUE klass) {
    Size *size = ALLOC(Size);
    memset(size, 0, sizeof(Size));
    RETURN_WRAP_STRUCT(klass, size);
}

VALUE open_image_size_initialize(int argc, VALUE *argv, VALUE self) {
    SIZE();
    switch (argc) {
        case 0:
            break;
        case 1: {
            Point *point;
            Data_Get_Struct(argv[0], Point, point);
            size->width = point->x;
            size->height = point->y;
        }
        case 2: {
            size->width = NUM2INT(argv[0]);
            size->height = NUM2INT(argv[1]);
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 1, 2)", argc);
    }
    return Qnil;
}

VALUE open_image_size_get_width(VALUE self) {
    SIZE();
    return INT2NUM(size->width);
}

VALUE open_image_size_get_height(VALUE self) {
    SIZE();
    return INT2NUM(size->height);
}

VALUE open_image_size_set_width(VALUE self, VALUE value) {
    SIZE();
    size->width = NUM2INT(value);
    return value;
}

VALUE open_image_size_set_height(VALUE self, VALUE value) {
    SIZE();
    size->height = NUM2INT(value);
    return value;
}