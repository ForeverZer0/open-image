
#include "size.h"

VALUE cSize;

#define SIZE()  \
    Size *size; \
    Data_Get_Struct(self, Size, size)

void Init_img_size(VALUE module) {
    cSize = rb_define_class_under(module, "Size", rb_cObject);
    rb_define_alloc_func(cSize, img_size_alloc);
    rb_define_method(cSize, "initialize", img_size_initialize, -1);

    rb_define_method(cSize, "set", img_size_set, 2);
    rb_define_method(cSize, "width", img_size_get_width, 0);
    rb_define_method(cSize, "height", img_size_get_height, 0);
    rb_define_method(cSize, "width=", img_size_set_width, 1);
    rb_define_method(cSize, "height=", img_size_set_height, 1);

    rb_define_method(cSize, "to_a", img_size_to_a, 0);
    rb_define_method(cSize, "to_h", img_size_to_h, 0);
    rb_define_method(cSize, "to_s", img_size_to_s, 0);
    rb_define_alias(cSize, "to_str", "to_s");
    rb_define_alias(cSize, "to_ary", "to_a");
    rb_define_method(cSize, "dup", img_size_dup, 0);
    rb_define_method(cSize, "==", img_size_eql, 1);

    rb_define_method(cSize, "_dump", img_size_dump, -1);
    rb_define_method(cSize, "pack", img_size_dump, -1);
    rb_define_singleton_method(cSize, "_load", img_size_load, 1);
    rb_define_singleton_method(cSize, "unpack", img_size_load, 1);
}

VALUE img_size_alloc(VALUE klass) {
    Size *size = ALLOC(Size);
    memset(size, 0, sizeof(Size));
    RETURN_WRAP_STRUCT(klass, size);
}

VALUE img_size_initialize(int argc, VALUE *argv, VALUE self) {
    SIZE();
    switch (argc) {
        case 0:
            break;
        case 1: {
            Point *point;
            Data_Get_Struct(argv[0], Point, point);
            size->width = point->x;
            size->height = point->y;
            break;
        }
        case 2: {
            size->width = NUM2INT(argv[0]);
            size->height = NUM2INT(argv[1]);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 1, 2)", argc);
            break;
    }
    return Qnil;
}

VALUE img_size_set(VALUE self, VALUE width, VALUE height) {
    SIZE();
    size->width = NUM2INT(width);
    size->height = NUM2INT(height);
    return self;
}

VALUE img_size_get_width(VALUE self) {
    SIZE();
    return INT2NUM(size->width);
}

VALUE img_size_get_height(VALUE self) {
    SIZE();
    return INT2NUM(size->height);
}

VALUE img_size_set_width(VALUE self, VALUE value) {
    SIZE();
    size->width = NUM2INT(value);
    return value;
}

VALUE img_size_set_height(VALUE self, VALUE value) {
    SIZE();
    size->height = NUM2INT(value);
    return value;
}

VALUE img_size_to_a(VALUE self) {
    SIZE();
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(size->width));
    rb_ary_store(ary, 1, INT2NUM(size->height));
    return ary;
}

VALUE img_size_to_h(VALUE self) {
    SIZE();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, STR2SYM("width"), INT2NUM(size->width));
    rb_hash_aset(hash, STR2SYM("height"), INT2NUM(size->height));
    return hash;
}

VALUE img_size_to_s(VALUE self) {
    SIZE();
    return rb_sprintf("<Size: width:%d, height:%d>", size->width, size->height);
}

VALUE img_size_dup(VALUE self) {
    struct RData *rdata = RDATA(self);
    Size *clone = ALLOC(Size);
    memcpy(clone, rdata->data, sizeof(Size));
    RETURN_WRAP_STRUCT(rdata->basic.klass, clone);
}

VALUE img_size_dump(int argc, VALUE *argv, VALUE self) {
    RB_MARSHAL_DUMP(Size);
}

VALUE img_size_load(VALUE klass, VALUE binary) {
    RB_MARSHAL_LOAD(Size);
}

VALUE img_size_eql(VALUE self, VALUE other) {
    RB_DATA_EQL(Size);
}