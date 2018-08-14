
#ifndef RB_OPEN_IMAGE_COMMON_H
#define RB_OPEN_IMAGE_COMMON_H 1

#define STBI_MALLOC ruby_xmalloc
#define STBI_REALLOC ruby_xrealloc
#define STBI_FREE ruby_xfree

#define STBIW_MALLOC STBI_MALLOC
#define STBIW_REALLOC STBI_REALLOC
#define STBIW_FREE STBI_FREE


#include "ruby.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef unsigned int uint;

typedef struct Image {
    unsigned int width;
    unsigned int height;
    unsigned char *pixels;
} Image;

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

#endif /* RB_OPEN_IMAGE_COMMON_H */