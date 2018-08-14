
#ifndef RB_OPEN_IMAGE_COMMON_H
#define RB_OPEN_IMAGE_COMMON_H 1

#define STBI_MALLOC ruby_xmalloc
#define STBI_REALLOC ruby_xrealloc
#define STBI_FREE ruby_xfree

#define STBIW_MALLOC STBI_MALLOC
#define STBIW_REALLOC STBI_REALLOC
#define STBIW_FREE STBI_FREE

#define RETURN_WRAP_STRUCT(klass, obj) return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, obj)
#define STR2SYM(str) ID2SYM(rb_intern(str))
#define MIN(v1, v2) (v1 > v2 ? v2 : v1)
#define MAX(v1, v2) (v1 < v2 ? v2 : v1)


#include "ruby.h"
#include "stb_image.h"
#include "stb_image_write.h"

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

extern VALUE rb_mOpenImage;
extern VALUE rb_eOpenImageError;
extern VALUE rb_cOpenImage;
extern VALUE rb_cOpenImageColor;
extern VALUE rb_mOpenImageColors;
extern VALUE rb_cOpenImagePoint;
extern VALUE rb_cOpenImageSize;
extern VALUE rb_cOpenImageRect;

#endif /* RB_OPEN_IMAGE_COMMON_H */