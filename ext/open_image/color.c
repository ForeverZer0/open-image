
#include "color.h"

#define COLOR()   \
    Color *color; \
    Data_Get_Struct(self, Color, color)

#define CLAMP(value, min, max) (value < min ? min : value > max ? max : value)

#define RGB_FLOAT()              \
    COLOR();                     \
    float r = color->r / 255.0f; \
    float g = color->g / 255.0f; \
    float b = color->b / 255.0f

#define RGBA_FLOAT() \
    RGB_FLOAT();     \
    float a = color->a / 255.0f

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
    rb_define_method(rb_cOpenImageColor, "gl", open_image_color_gl, 0);

    rb_define_alias(rb_cOpenImageColor, "to_str", "to_s");
    rb_define_alias(rb_cOpenImageColor, "to_int", "to_i");

    rb_define_method(rb_cOpenImageColor, "hue", open_image_color_hue, 0);
    rb_define_method(rb_cOpenImageColor, "saturation", open_image_color_saturation, 0);
    rb_define_method(rb_cOpenImageColor, "brightness", open_image_color_brightness, 0);
    rb_define_method(rb_cOpenImageColor, "hsb", open_image_color_hsb, 0);

    rb_define_method(rb_cOpenImageColor, "lerp", open_image_color_lerp, 2);
    rb_define_method(rb_cOpenImageColor, "lerp!", open_image_color_lerp_bang, 2);
}

VALUE open_image_color_alloc(VALUE klass) {
    Color *color = ALLOC(Color);
    memset(color, 0, sizeof(Color));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, color);
}

VALUE open_image_color_initialize(int argc, VALUE *argv, VALUE self) {
    unsigned char *color = RDATA(self)->data;
    switch (argc) {
        case 0:  // None
            break;
        case 1: {
            uint argb;
            if (RB_TYPE_P(argv[0], T_STRING))  // HTML
            {
                const char *hexstring = StringValueCStr(argv[0]);
                if (hexstring[0] == '#')
                    hexstring++;
                argb = (uint)strtoul(hexstring, NULL, 16);

                printf("%u", argb);
            } else  // Unsigned Integer
            {
                argb = NUM2UINT(argv[0]);
            }
            color[3] = (unsigned char)((argb & 0xff000000) >> 24);
            color[0] = (unsigned char)((argb & 0x00ff0000) >> 16);
            color[1] = (unsigned char)((argb & 0x0000ff00) >> 8);
            color[2] = (unsigned char)(argb & 0x000000ff);

            // TODO: Test big-endian

            break;
        }
        case 3:  // RGB
            color[3] = 255;
        case 4:  // RGBA
        {
            for (int i = 0; i < argc; i++) {
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
    color->r = (unsigned char)CLAMP(NUM2INT(value), 0, 255);
    return value;
}

VALUE open_image_color_set_g(VALUE self, VALUE value) {
    COLOR();
    color->g = (unsigned char)CLAMP(NUM2INT(value), 0, 255);
    return value;
}
VALUE open_image_color_set_b(VALUE self, VALUE value) {
    COLOR();
    color->b = (unsigned char)CLAMP(NUM2INT(value), 0, 255);
    return value;
}

VALUE open_image_color_set_a(VALUE self, VALUE value) {
    COLOR();
    color->a = (unsigned char)CLAMP(NUM2INT(value), 0, 255);
    return value;
}

VALUE open_image_color_to_a(VALUE self) {
    COLOR();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, INT2NUM(color->r));
    rb_ary_store(ary, 1, INT2NUM(color->g));
    rb_ary_store(ary, 2, INT2NUM(color->b));
    rb_ary_store(ary, 3, INT2NUM(color->a));
    return ary;
}

VALUE open_image_color_to_h(VALUE self) {
    COLOR();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, STR2SYM("red"), INT2NUM(color->r));
    rb_hash_aset(hash, STR2SYM("green"), INT2NUM(color->g));
    rb_hash_aset(hash, STR2SYM("blue"), INT2NUM(color->b));
    rb_hash_aset(hash, STR2SYM("alpha"), INT2NUM(color->a));
    return hash;
}

VALUE open_image_color_to_s(VALUE self) {
    COLOR();
    return rb_sprintf("<Color: R:%d, G:%d, B:%d, A:%d>", color->r, color->g, color->b, color->a);
}

VALUE open_image_color_to_i(VALUE self) {
    COLOR();
    return UINT2NUM((uint)(((color->a << 24) | (color->r << 16) | (color->g << 8) | color->b) & 0xFFFFFFFFu));
}

VALUE open_image_color_hue(VALUE self) {
    RGB_FLOAT();
    if (color->r == color->g && color->g == color->b)
        return DBL2NUM(0.0);

    float max = MAX(r, MAX(g, b));
    float min = MIN(r, MIN(g, b));
    float delta = max - min, hue = 0.0f;

    if (fabsf(r - max) < FLT_EPSILON) {
        hue = (g - b) / delta;
    } else if (fabsf(g - max) < FLT_EPSILON) {
        hue = 2.0f + (b - r) / delta;
    } else if (fabsf(b - max) < FLT_EPSILON) {
        hue = 4.0f + (r - g) / delta;
    }

    hue *= 60.0f;
    if (hue < 0.0f)
        hue += 360.0f;

    return DBL2NUM(hue);
}

VALUE open_image_color_saturation(VALUE self) {
    RGB_FLOAT();
    float max = MAX(r, MAX(g, b));
    float min = MIN(r, MIN(g, b));
    float brightness, s = 0.0f;

    if (fabsf(max - min) > FLT_EPSILON) {
        brightness = (max + min) * 0.5f;
        s = (max - min) / (brightness <= 0.5f ? (max + min) : (2 - max - min));
    }
    return DBL2NUM(s);
}

VALUE open_image_color_brightness(VALUE self) {
    RGB_FLOAT();
    float max = MAX(r, MAX(g, b));
    float min = MIN(r, MIN(g, b));
    return DBL2NUM((max + min) * 0.5f);
}

VALUE open_image_color_hsb(VALUE self) {
    RGB_FLOAT();
    float max = MAX(r, MAX(g, b));
    float min = MIN(r, MIN(g, b));
    float delta = max - min, brightness = (max + min) * 0.5f, hue = 0.0f, saturation = 0.0f;

    if (fabsf(max - min) > FLT_EPSILON) {
        saturation = (max - min) / (brightness <= 0.5f ? (max + min) : (2 - max - min));
    }

    if (fabsf(r - max) < FLT_EPSILON) {
        hue = (g - b) / delta;
    } else if (fabsf(g - max) < FLT_EPSILON) {
        hue = 2.0f + (b - r) / delta;
    } else if (fabsf(b - max) < FLT_EPSILON) {
        hue = 4.0f + (r - g) / delta;
    }

    hue *= 60.0f;
    if (hue < 0.0f)
        hue += 360.0f;

    VALUE hsb = rb_ary_new_capa(3);
    rb_ary_store(hsb, 0, DBL2NUM(hue));
    rb_ary_store(hsb, 1, DBL2NUM(saturation));
    rb_ary_store(hsb, 2, DBL2NUM(brightness));
    return hsb;
}

VALUE open_image_color_lerp(VALUE self, VALUE other, VALUE amount) {
    Color *c1, *c2, *result;
    Data_Get_Struct(self, Color, c1);
    Data_Get_Struct(other, Color, c2);
    result = ALLOC(Color);
    float w = CLAMP(NUM2FLT(amount), 0.0f, 1.0f);
    result->r = (unsigned char)roundf(c1->r + (c2->r - c1->r) * w);
    result->g = (unsigned char)roundf(c1->g + (c2->g - c1->g) * w);
    result->b = (unsigned char)roundf(c1->b + (c2->b - c1->b) * w);
    result->a = (unsigned char)roundf(c1->a + (c2->a - c1->a) * w);
    RETURN_WRAP_STRUCT(CLASS_OF(self), result);
}

VALUE open_image_color_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Color *c1, *c2;
    Data_Get_Struct(self, Color, c1);
    Data_Get_Struct(other, Color, c2);
    

    return self;
}

VALUE open_image_color_gl(VALUE self) {
    COLOR();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, DBL2NUM(color->r / 255.0));
    rb_ary_store(ary, 1, DBL2NUM(color->g / 255.0));
    rb_ary_store(ary, 2, DBL2NUM(color->b / 255.0));
    rb_ary_store(ary, 3, DBL2NUM(color->a / 255.0));
    return ary;
}