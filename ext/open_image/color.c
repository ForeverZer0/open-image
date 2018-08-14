
#include "color.h"

#define COLOR()   \
    Color *color; \
    Data_Get_Struct(self, Color, color)

#define CLAMP(value, min, max) (value < min ? min : value > max ? max : value)

VALUE rb_cOpenImageColor;

void Init_open_image_color(VALUE module) {
    rb_cOpenImageColor = rb_define_class_under(module, "Color", rb_cObject);
    rb_define_alloc_func(rb_cOpenImageColor, open_image_color_alloc);
    rb_define_method(rb_cOpenImageColor, "initialize", open_image_color_initialize, -1);

    rb_define_method(rb_cOpenImageColor, "r", open_image_color_get_r, 0);
    rb_define_method(rb_cOpenImageColor, "g", open_image_color_get_g, 0);
    rb_define_method(rb_cOpenImageColor, "b", open_image_color_get_b, 0);
    rb_define_method(rb_cOpenImageColor, "a", open_image_color_get_a, 0);

    rb_define_method(rb_cOpenImageColor, "r=", open_image_color_set_r, 1);
    rb_define_method(rb_cOpenImageColor, "g=", open_image_color_set_g, 1);
    rb_define_method(rb_cOpenImageColor, "b=", open_image_color_set_b, 1);
    rb_define_method(rb_cOpenImageColor, "a=", open_image_color_set_a, 1);

    rb_define_alias(rb_cOpenImageColor, "red", "r");
    rb_define_alias(rb_cOpenImageColor, "green", "g");
    rb_define_alias(rb_cOpenImageColor, "blue", "b");
    rb_define_alias(rb_cOpenImageColor, "alpha", "a");

    rb_define_alias(rb_cOpenImageColor, "red=", "r=");
    rb_define_alias(rb_cOpenImageColor, "green=", "g=");
    rb_define_alias(rb_cOpenImageColor, "blue=", "b=");
    rb_define_alias(rb_cOpenImageColor, "alpha=", "a=");

    rb_define_method(rb_cOpenImageColor, "to_a", open_image_color_to_a, 0);
    rb_define_method(rb_cOpenImageColor, "to_h", open_image_color_to_h, 0);
    rb_define_method(rb_cOpenImageColor, "to_s", open_image_color_to_s, 0);
    rb_define_method(rb_cOpenImageColor, "to_i", open_image_color_to_i, 0);
}

VALUE open_image_color_alloc(VALUE klass) {
    Color *color = ALLOC(Color);
    memset(color, 0, sizeof(Color));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, color);
}

VALUE open_image_color_initialize(int argc, VALUE *argv, VALUE self) {
    unsigned char *color = RDATA(self)->data;
    switch (argc)
    {
        case 0:
            break;
        case 1:
        {

            break;
        }
        case 3:
            color[3] = 255;
        case 4:
        {
            for (int i = 0; i < argc; i++)
            {
                char c = NUM2CHR(argv[i]);
                memcpy(&color[i], &c, 1);
            }
            break;
        }
    }
    return Qnil;
}

VALUE open_image_color_get_r(VALUE self) {
    COLOR();
    return INT2NUM(color->r);
}

VALUE open_image_color_get_g(VALUE self) {
    COLOR();
    return INT2NUM(color->g);
}

VALUE open_image_color_get_b(VALUE self) {
    COLOR();
    return INT2NUM(color->b);
}

VALUE open_image_color_get_a(VALUE self) {
    COLOR();
    return INT2NUM(color->a);
}

VALUE open_image_color_set_r(VALUE self, VALUE value) {
    COLOR();
    color->r = (unsigned char) CLAMP(NUM2INT(value), 0, 255);
    return value;
}

VALUE open_image_color_set_g(VALUE self, VALUE value) {
    COLOR();
    color->g = (unsigned char) CLAMP(NUM2INT(value), 0, 255);
    return value;
}
VALUE open_image_color_set_b(VALUE self, VALUE value) {
    COLOR();
    color->b = (unsigned char) CLAMP(NUM2INT(value), 0, 255);
    return value;
}

VALUE open_image_color_set_a(VALUE self, VALUE value) {
    COLOR();
    color->a = (unsigned char) CLAMP(NUM2INT(value), 0, 255);
    return value;
}

VALUE open_image_color_to_a(VALUE self) {
    COLOR();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, color->r);
    rb_ary_store(ary, 1, color->g);
    rb_ary_store(ary, 2, color->b);
    rb_ary_store(ary, 3, color->a);
    return ary;
}

VALUE open_image_color_to_h(VALUE self) {
    COLOR();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, STR2SYM("red"), color->r);
    rb_hash_aset(hash, STR2SYM("green"), color->g);
    rb_hash_aset(hash, STR2SYM("blue"), color->b);
    rb_hash_aset(hash, STR2SYM("alpha"), color->a);
    return hash;
}

VALUE open_image_color_to_s(VALUE self) {
    COLOR();
    return rb_sprintf("<Color: R:%d, G:%d, B:%d, A:%d>", color->r, color->g, color->b, color->a);
}

VALUE open_image_color_to_i(VALUE self) {
    
}