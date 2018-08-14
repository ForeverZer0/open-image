
#ifndef RB_OPEN_IMAGE_IMAGE_H
#define RB_OPEN_IMAGE_IMAGE_H 1

#include "common.h"
#include <string.h>

void Init_open_image_image(VALUE module);
void open_image_free(void *data);
VALUE open_image_alloc(VALUE klass);
VALUE open_image_initialize(int argc, VALUE *argv, VALUE self);

VALUE open_image_width(VALUE self);
VALUE open_image_height(VALUE self);
VALUE open_image_pixels(VALUE self);
VALUE open_image_ptr(VALUE self);

VALUE open_image_save_png(VALUE self, VALUE path);
VALUE open_image_save_jpg(int argc, VALUE *argv, VALUE self);
VALUE open_image_save_tga(VALUE self, VALUE path);
VALUE open_image_save_bmp(VALUE self, VALUE path);

#endif /* RB_OPEN_IMAGE_IMAGE_H */