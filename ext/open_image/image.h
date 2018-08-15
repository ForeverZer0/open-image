
#ifndef RB_OPEN_IMAGE_IMAGE_H
#define RB_OPEN_IMAGE_IMAGE_H 1

#include "common.h"

void Init_open_image_image(VALUE module);
static inline void open_image_free(void *data);
VALUE open_image_alloc(VALUE klass);
VALUE open_image_initialize(int argc, VALUE *argv, VALUE self);
VALUE open_image_dispose(VALUE self);
VALUE open_image_disposed_p(VALUE self);

VALUE open_image_width(VALUE self);
VALUE open_image_height(VALUE self);
VALUE open_image_pixels(VALUE self);
VALUE open_image_ptr(VALUE self);

VALUE open_image_save_png(VALUE self, VALUE path);
VALUE open_image_save_jpg(int argc, VALUE *argv, VALUE self);
VALUE open_image_save_tga(VALUE self, VALUE path);
VALUE open_image_save_bmp(VALUE self, VALUE path);

VALUE open_image_get_pixel(int argc, VALUE *argv, VALUE self);
VALUE open_image_set_pixel(int argc, VALUE *argv, VALUE self);
VALUE open_image_fill_rect(int argc, VALUE *argv, VALUE self);
VALUE open_image_subimage(int argc, VALUE *argv, VALUE self);

VALUE open_image_split(VALUE self, VALUE rows, VALUE columns);

VALUE open_image_size(VALUE self);
VALUE open_image_rect(VALUE self);
VALUE open_image_to_s(VALUE self);
VALUE open_image_dup(VALUE self);

#endif /* RB_OPEN_IMAGE_IMAGE_H */