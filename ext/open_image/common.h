
#ifndef RB_OPEN_IMAGE_COMMON_H
#define RB_OPEN_IMAGE_COMMON_H 1

#define STBI_MALLOC ruby_xmalloc
#define STBI_REALLOC ruby_xrealloc
#define STBI_FREE ruby_xfree

#define STBIW_MALLOC STBI_MALLOC
#define STBIW_REALLOC STBI_REALLOC
#define STBIW_FREE STBI_FREE

#include "ruby.h"
#include "ruby/version.h"
#include "stb_image.h"
#include "stb_image_write.h"

#define OPEN_IMAGE_DEBUG 0
#if OPEN_IMAGE_DEBUG
#define DEBUG printf
#else
#define DEBUG(...) \
    do {           \
    } while (0)
#endif

#define RETURN_WRAP_STRUCT(klass, obj) return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, obj)
#define STR2SYM(str) ID2SYM(rb_intern(str))

#define MAX(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define MIN(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define CLAMP(value, min, max) \
    ({ __typeof__ (value) _value = (value); \
       __typeof__ (min) _min = (min); \
       __typeof__ (max) _max = (max); \
       _value < _min ? _min : _value > _max ? _max : _value; })

#ifndef FLT_EPSILON
#define FLT_EPSILON 1.192092896e-07F
#endif

#define NUM2FLT(v) ((float)NUM2DBL(v))
#define USE_FIDDLE RUBY_API_VERSION_MAJOR < 2

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

#endif /* RB_OPEN_IMAGE_COMMON_H */