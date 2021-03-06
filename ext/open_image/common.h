
#ifndef RB_OPEN_IMAGE_COMMON_H
#define RB_OPEN_IMAGE_COMMON_H 1

#define STBI_MALLOC ruby_xmalloc
#define STBI_REALLOC ruby_xrealloc
#define STBI_FREE ruby_xfree

#define STBIW_MALLOC STBI_MALLOC
#define STBIW_REALLOC STBI_REALLOC
#define STBIW_FREE STBI_FREE

#define __USE_MINGW_ANSI_STDIO 1

#include "ruby.h"

#if HAVE_RUBY_VERSION_H
#include "ruby/version.h"
#define USE_FIDDLE RUBY_API_VERSION_MAJOR >= 2
#else
#define USE_FIDDLE 0
#endif

#include "features.h"
#include "stb_image.h"
#include "stb_image_write.h"

#define RETURN_WRAP_STRUCT(klass, obj) return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, obj)
#define STR2SYM(str) ID2SYM(rb_intern(str))

#ifndef FLT_EPSILON
#define FLT_EPSILON 1.192092896e-07F
#endif

#define NUM2FLT(v) ((float)NUM2DBL(v))

#define RB_MARSHAL_DUMP(struct_t)       \
    struct_t *s;                        \
    Data_Get_Struct(self, struct_t, s); \
    long size = (long)sizeof(struct_t); \
    return rb_str_new(RDATA(self)->data, size)

#define RB_MARSHAL_LOAD(struct_t)        \
    size_t size = sizeof(struct_t);      \
    void *data = StringValuePtr(binary); \
    struct_t *v = ALLOC(struct_t);       \
    memcpy(v, data, size);               \
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, v)

#define RB_DATA_EQL(struct_t)             \
    if (self == other)                    \
        return Qtrue;                     \
    if (TYPE(other) != T_DATA)            \
        return Qfalse;                    \
    struct_t *v1, *v2;                    \
    Data_Get_Struct(self, struct_t, v1);  \
    Data_Get_Struct(other, struct_t, v2); \
    return memcmp(v1, v2, sizeof(struct_t)) ? Qfalse : Qtrue

typedef unsigned int uint;

typedef struct Image {
    unsigned int width;
    unsigned int height;
    unsigned char *pixels;
} Image;

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Size {
    int width;
    int height;
} Size;

typedef struct Rect {
    int x;
    int y;
    int width;
    int height;
} Rect;

typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

extern VALUE mOpenImage;
extern VALUE eOpenImageError;
extern VALUE cImage;
extern VALUE cColor;
extern VALUE cPoint;
extern VALUE cSize;
extern VALUE cRect;
#if USE_FIDDLE
extern VALUE cFiddlePointer;
#endif

inline int imax(int v1, int v2) {
    return v1 > v2 ? v1 : v2;
}

inline int imin(int v1, int v2) {
    return v1 < v2 ? v1 : v2;
}

inline int iclamp(int value, int min, int max) {
    return value < min ? min : value > max ? max : value;
}

inline float fclamp(float value, float min, float max) {
    return value < min ? min : value > max ? max : value;
}

#endif /* RB_OPEN_IMAGE_COMMON_H */