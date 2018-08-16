
#ifndef RB_OPEN_IMAGE_IMAGE_H
#define RB_OPEN_IMAGE_IMAGE_H 1

#include "common.h"

void Init_img_image(VALUE module);
static inline void img_image_free(void *data);
VALUE img_image_alloc(VALUE klass);
VALUE img_image_initialize(int argc, VALUE *argv, VALUE self);
VALUE img_image_dispose(VALUE self);
VALUE img_image_disposed_p(VALUE self);

VALUE img_image_width(VALUE self);
VALUE img_image_height(VALUE self);
VALUE img_image_pixels(VALUE self);
VALUE img_image_ptr(VALUE self);

VALUE img_image_save_png(VALUE self, VALUE path);
VALUE img_image_save_jpg(int argc, VALUE *argv, VALUE self);
VALUE img_image_save_tga(VALUE self, VALUE path);
VALUE img_image_save_bmp(VALUE self, VALUE path);

VALUE img_image_get_pixel(int argc, VALUE *argv, VALUE self);
VALUE img_image_set_pixel(int argc, VALUE *argv, VALUE self);
VALUE img_image_fill_rect(int argc, VALUE *argv, VALUE self);
VALUE img_image_subimage(int argc, VALUE *argv, VALUE self);

VALUE img_image_split(VALUE self, VALUE rows, VALUE columns);

VALUE img_image_size(VALUE self);
VALUE img_image_rect(VALUE self);
VALUE img_image_to_s(VALUE self);
VALUE img_image_dup(VALUE self);

VALUE img_image_grayscale(VALUE self, VALUE amount);
VALUE img_image_sepia(VALUE self);

#endif /* RB_OPEN_IMAGE_IMAGE_H */