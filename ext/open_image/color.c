
#include "color.h"

#define COLOR()   \
    Color *color; \
    Data_Get_Struct(self, Color, color)

#define RGB_FLOAT()              \
    COLOR();                     \
    float r = color->r / 255.0f; \
    float g = color->g / 255.0f; \
    float b = color->b / 255.0f

#define RGBA_FLOAT() \
    RGB_FLOAT();     \
    float a = color->a / 255.0f

VALUE cColor;

void Init_img_color(VALUE module) {
    cColor = rb_define_class_under(module, "Color", rb_cObject);
    rb_define_alloc_func(cColor, img_color_alloc);
    rb_define_method(cColor, "initialize", img_color_initialize, -1);

    rb_define_singleton_method(cColor, "from_hsb", img_color_from_hsb, -1);
    rb_define_singleton_method(cColor, "from_hsv", img_color_from_hsb, -1);
    rb_define_singleton_method(cColor, "from_hsl", img_color_from_hsl, -1);

    rb_define_method(cColor, "r", img_color_get_r, 0);
    rb_define_method(cColor, "g", img_color_get_g, 0);
    rb_define_method(cColor, "b", img_color_get_b, 0);
    rb_define_method(cColor, "a", img_color_get_a, 0);

    rb_define_method(cColor, "red", img_color_getf_r, 0);
    rb_define_method(cColor, "green", img_color_getf_g, 0);
    rb_define_method(cColor, "blue", img_color_getf_b, 0);
    rb_define_method(cColor, "alpha", img_color_getf_a, 0);

    rb_define_method(cColor, "r=", img_color_set_r, 1);
    rb_define_method(cColor, "g=", img_color_set_g, 1);
    rb_define_method(cColor, "b=", img_color_set_b, 1);
    rb_define_method(cColor, "a=", img_color_set_a, 1);

    rb_define_alias(cColor, "red=", "r=");
    rb_define_alias(cColor, "green=", "g=");
    rb_define_alias(cColor, "blue=", "b=");
    rb_define_alias(cColor, "alpha=", "a=");

    rb_define_method(cColor, "to_a", img_color_to_a, 0);
    rb_define_method(cColor, "to_h", img_color_to_h, 0);
    rb_define_method(cColor, "to_s", img_color_to_s, 0);
    rb_define_method(cColor, "to_i", img_color_to_i, 0);
    rb_define_method(cColor, "gl", img_color_gl, 0);
    rb_define_method(cColor, "hsl", img_color_hsl, 0);
    rb_define_method(cColor, "hsb", img_color_hsb, 0);
    rb_define_method(cColor, "html", img_color_html, 0);

    rb_define_alias(cColor, "to_ary", "to_a");
    rb_define_alias(cColor, "to_str", "to_s");
    rb_define_alias(cColor, "to_int", "to_i");
    rb_define_method(cColor, "==", img_color_eql, 1);

    rb_define_method(cColor, "hue", img_color_hue, 0);
    rb_define_method(cColor, "saturation", img_color_saturation, 0);
    rb_define_method(cColor, "lightness", img_color_lightness, 0);
    rb_define_method(cColor, "brightness", img_color_brightness, 0);
    rb_define_alias(cColor, "value", "brightness");

    rb_define_method(cColor, "lerp", img_color_lerp, 2);
    rb_define_method(cColor, "lerp!", img_color_lerp_bang, 2);

    rb_define_method(cColor, "_dump", img_color_dump, -1);
    rb_define_method(cColor, "pack", img_color_dump, -1);
    rb_define_singleton_method(cColor, "_load", img_color_load, 1);
    rb_define_singleton_method(cColor, "unpack", img_color_load, 1);
}

VALUE img_color_alloc(VALUE klass) {
    Color *color = ALLOC(Color);
    memset(color, 0, sizeof(Color));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, color);
}

VALUE img_color_initialize(int argc, VALUE *argv, VALUE self) {
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
            } else  // Unsigned Integer
            {
                argb = NUM2UINT(argv[0]);
            }
            color[3] = (unsigned char)((argb & 0xff000000) >> 24);
            color[0] = (unsigned char)((argb & 0x00ff0000) >> 16);
            color[1] = (unsigned char)((argb & 0x0000ff00) >> 8);
            color[2] = (unsigned char)(argb & 0x000000ff);

            // TODO: Test with different endianess

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

VALUE img_color_get_r(VALUE self) {
    COLOR();
    return INT2NUM(color->r);
}

VALUE img_color_get_g(VALUE self) {
    COLOR();
    return INT2NUM(color->g);
}

VALUE img_color_get_b(VALUE self) {
    COLOR();
    return INT2NUM(color->b);
}

VALUE img_color_get_a(VALUE self) {
    COLOR();
    return INT2NUM(color->a);
}

VALUE img_color_getf_r(VALUE self) {
    COLOR();
    return DBL2NUM(color->r / 255.0);
}

VALUE img_color_getf_g(VALUE self) {
    COLOR();
    return DBL2NUM(color->g / 255.0);
}

VALUE img_color_getf_b(VALUE self) {
    COLOR();
    return DBL2NUM(color->b / 255.0);
}

VALUE img_color_getf_a(VALUE self) {
    COLOR();
    return DBL2NUM(color->a / 255.0);
}

VALUE img_color_set_r(VALUE self, VALUE value) {
    COLOR();
    if (RB_FLOAT_TYPE_P(value))
        color->r = (unsigned char)roundf(fclamp(NUM2FLT(value) * 255.0f, 0.0f, 255.0f));
    else
        color->r = (unsigned char)iclamp(NUM2INT(value), 0, 255);
    return value;
}

VALUE img_color_set_g(VALUE self, VALUE value) {
    COLOR();
    if (RB_FLOAT_TYPE_P(value))
        color->g = (unsigned char)roundf(fclamp(NUM2FLT(value) * 255.0f, 0.0f, 255.0f));
    else
        color->g = (unsigned char)iclamp(NUM2INT(value), 0, 255);
    return value;
}

VALUE img_color_set_b(VALUE self, VALUE value) {
    COLOR();
    if (RB_FLOAT_TYPE_P(value))
        color->b = (unsigned char)roundf(fclamp(NUM2FLT(value) * 255.0f, 0.0f, 255.0f));
    else
        color->b = (unsigned char)iclamp(NUM2INT(value), 0, 255);
    return value;
}

VALUE img_color_set_a(VALUE self, VALUE value) {
    COLOR();
    if (RB_FLOAT_TYPE_P(value))
        color->a = (unsigned char)roundf(fclamp(NUM2FLT(value) * 255.0f, 0.0f, 255.0f));
    else
        color->a = (unsigned char)iclamp(NUM2INT(value), 0, 255);
    return value;
}

VALUE img_color_to_a(VALUE self) {
    COLOR();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, INT2NUM(color->r));
    rb_ary_store(ary, 1, INT2NUM(color->g));
    rb_ary_store(ary, 2, INT2NUM(color->b));
    rb_ary_store(ary, 3, INT2NUM(color->a));
    return ary;
}

VALUE img_color_to_h(VALUE self) {
    COLOR();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, STR2SYM("red"), INT2NUM(color->r));
    rb_hash_aset(hash, STR2SYM("green"), INT2NUM(color->g));
    rb_hash_aset(hash, STR2SYM("blue"), INT2NUM(color->b));
    rb_hash_aset(hash, STR2SYM("alpha"), INT2NUM(color->a));
    return hash;
}

VALUE img_color_to_s(VALUE self) {
    COLOR();
    return rb_sprintf("<Color: R:%d, G:%d, B:%d, A:%d>", color->r, color->g, color->b, color->a);
}

VALUE img_color_to_i(VALUE self) {
    COLOR();
    return UINT2NUM((uint)(((color->a << 24) | (color->r << 16) | (color->g << 8) | color->b) & 0xFFFFFFFFu));
}

VALUE img_color_lerp(VALUE self, VALUE other, VALUE amount) {
    Color *c1, *c2, *result;
    Data_Get_Struct(self, Color, c1);
    Data_Get_Struct(other, Color, c2);
    result = ALLOC(Color);
    float w = fclamp(NUM2FLT(amount), 0.0f, 1.0f);
    result->r = (unsigned char)roundf(c1->r + (c2->r - c1->r) * w);
    result->g = (unsigned char)roundf(c1->g + (c2->g - c1->g) * w);
    result->b = (unsigned char)roundf(c1->b + (c2->b - c1->b) * w);
    result->a = (unsigned char)roundf(c1->a + (c2->a - c1->a) * w);
    RETURN_WRAP_STRUCT(CLASS_OF(self), result);
}

VALUE img_color_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Color *c1, *c2;
    Data_Get_Struct(self, Color, c1);
    Data_Get_Struct(other, Color, c2);
    float w = fclamp(NUM2FLT(amount), 0.0f, 1.0f);
    c1->r = (unsigned char)roundf(c1->r + (c2->r - c1->r) * w);
    c1->g = (unsigned char)roundf(c1->g + (c2->g - c1->g) * w);
    c1->b = (unsigned char)roundf(c1->b + (c2->b - c1->b) * w);
    c1->a = (unsigned char)roundf(c1->a + (c2->a - c1->a) * w);
    return self;
}

VALUE img_color_gl(VALUE self) {
    COLOR();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, DBL2NUM(color->r / 255.0));
    rb_ary_store(ary, 1, DBL2NUM(color->g / 255.0));
    rb_ary_store(ary, 2, DBL2NUM(color->b / 255.0));
    rb_ary_store(ary, 3, DBL2NUM(color->a / 255.0));
    return ary;
}

VALUE img_color_hue(VALUE self) {
    RGB_FLOAT();
    if (color->r == color->g && color->g == color->b)
        return DBL2NUM(0.0);

    float max = fmax(r, fmax(g, b));
    float min = fmin(r, fmin(g, b));
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

VALUE img_color_saturation(VALUE self) {
    RGB_FLOAT();
    float max = fmax(r, fmax(g, b));
    float min = fmin(r, fmin(g, b));
    float lightness, s = 0.0f;

    if (fabsf(max - min) > FLT_EPSILON) {
        lightness = (max + min) * 0.5f;
        s = (max - min) / (lightness <= 0.5f ? (max + min) : (2 - max - min));
    }
    return DBL2NUM(s);
}

VALUE img_color_lightness(VALUE self) {
    RGB_FLOAT();
    float max = fmax(r, fmax(g, b));
    float min = fmin(r, fmin(g, b));
    return DBL2NUM((max + min) * 0.5f);
}

VALUE img_color_brightness(VALUE self) {
    RGB_FLOAT();
    float max = fmax(r, fmax(g, b));
    return DBL2NUM(max);
}

VALUE img_color_hsl(VALUE self) {
    RGB_FLOAT();
    float max = fmax(r, fmax(g, b));
    float min = fmin(r, fmin(g, b));
    float delta = max - min, lightness = (max + min) * 0.5f, hue = 0.0f, saturation = 0.0f;

    if (delta > FLT_EPSILON) {
        saturation = (max - min) / (lightness <= 0.5f ? (max + min) : (2 - max - min));

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
    }
    VALUE hsl = rb_ary_new_capa(3);
    rb_ary_store(hsl, 0, DBL2NUM(hue));
    rb_ary_store(hsl, 1, DBL2NUM(saturation));
    rb_ary_store(hsl, 2, DBL2NUM(lightness));
    return hsl;
}

VALUE img_color_hsb(VALUE self) {
    RGB_FLOAT();
    float max = fmax(r, fmax(g, b));
    float min = fmin(r, fmin(g, b));
    float delta = max - min, s = 0.0f, h = 0.0f, v = max;

    if (delta > FLT_EPSILON) {
        s = (delta / max);
        if (r >= max)
            h = (g - b) / delta;
        else if (g >= max)
            h = 2.0 + (b - r) / delta;
        else
            h = 4.0 + (r - g) / delta;
        h *= 60.0;
        if (h < 0.0f)
            h += 360.0;
    }

    VALUE hsv = rb_ary_new_capa(3);
    rb_ary_store(hsv, 0, DBL2NUM(h));
    rb_ary_store(hsv, 1, DBL2NUM(s));
    rb_ary_store(hsv, 2, DBL2NUM(v));
    return hsv;
}

VALUE img_color_from_hsb(int argc, VALUE *argv, VALUE klass) {
    VALUE hue, saturation, brightness, alpha;
    rb_scan_args(argc, argv, "31", &hue, &saturation, &brightness, &alpha);

    float h = fclamp(NUM2FLT(hue), 0.0f, 360.0f);
    float s = fclamp(NUM2FLT(saturation), 0.0f, 1.0f);
    float b = fclamp(NUM2FLT(brightness), 0.0f, 1.0f);

    Color *color = ALLOC(Color);
    img_color_hsb2rgb(color, h, s, b);
    color->a = (unsigned char)(NIL_P(alpha) ? 255 : iclamp(NUM2INT(alpha), 0, 255));
    RETURN_WRAP_STRUCT(klass, color);
}

VALUE img_color_from_hsl(int argc, VALUE *argv, VALUE klass) {
    VALUE hue, saturation, lightness, alpha;
    rb_scan_args(argc, argv, "31", &hue, &saturation, &lightness, &alpha);

    float h = fclamp(NUM2FLT(hue), 0.0f, 360.0f);
    float s = fclamp(NUM2FLT(saturation), 0.0f, 1.0f);
    float l = fclamp(NUM2FLT(lightness), 0.0f, 1.0f);
    float sat, b;

    // Convert the saturation and lightness to be consistent with HSB/HSV, then compute
    img_color_hsl2hsb(s, l, &sat, &b);

    Color *color = ALLOC(Color);
    img_color_hsb2rgb(color, h, sat, b);
    color->a = (unsigned char)(NIL_P(alpha) ? 255 : iclamp(NUM2INT(alpha), 0, 255));
    RETURN_WRAP_STRUCT(klass, color);
}

static inline void img_color_hsl2hsb(float in_s, float in_l, float *out_s, float *out_b) {
    float t = in_s * (in_l < 0.5f ? in_l : 1.0f - in_l);
    *out_b = in_l + t;
    *out_s = in_l > 0.0f ? 2.0f * t / *out_b : *out_s;
}

static inline void img_color_hsb2rgb(Color *color, float hue, float saturation, float brightness) {
    float r, g, b;

    if (saturation < FLT_EPSILON) {
        r = brightness;
        g = brightness;
        b = brightness;
    } else {
        float p, q, t, ff;
        if (hue >= 360.0f)
            hue = 0.0f;
        hue /= 60.0f;
        int i = (int)hue;
        ff = hue - i;
        p = brightness * (1.0f - saturation);
        q = brightness * (1.0f - (saturation * ff));
        t = brightness * (1.0f - (saturation * (1.0f - ff)));

        switch (i) {
            case 0:
                r = brightness;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = brightness;
                b = p;
                break;
            case 2:
                r = p;
                g = brightness;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = brightness;
                break;
            case 4:
                r = t;
                g = p;
                b = brightness;
                break;
            case 5:
            default:
                r = brightness;
                g = p;
                b = q;
                break;
        }
    }

    color->r = (unsigned char)roundf(r * 255.0f);
    color->g = (unsigned char)roundf(g * 255.0f);
    color->b = (unsigned char)roundf(b * 255.0f);
}

VALUE img_color_html(VALUE self) {
    COLOR();
    return rb_sprintf("#%2x%2x%2x", color->r, color->g, color->b);
}

VALUE img_color_dump(int argc, VALUE *argv, VALUE self) {
    RB_MARSHAL_DUMP(Color);
}

VALUE img_color_load(VALUE klass, VALUE binary) {
    RB_MARSHAL_LOAD(Color);
}

VALUE img_color_eql(VALUE self, VALUE other) {
    RB_DATA_EQL(Color);
}