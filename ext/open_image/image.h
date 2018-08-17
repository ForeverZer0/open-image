
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

#if OPEN_IMAGE_GRAYSCALE
VALUE img_image_grayscale(int argc, VALUE *argv, VALUE self);
VALUE img_image_grayscale_bang(int argc, VALUE *argv, VALUE self);
static inline void img_image_grayscale_s(Image *image, VALUE amount);
#endif

#if OPEN_IMAGE_SEPIA
VALUE img_image_sepia(VALUE self);
VALUE img_image_sepia_bang(VALUE self);
static inline void img_image_sepia_s(Image *image);
#endif

#if OPEN_IMAGE_INVERT
VALUE img_image_invert(int argc, VALUE *argv, VALUE self);
VALUE img_image_invert_bang(int argc, VALUE *argv, VALUE self);
static inline void img_image_invert_s(Image *image, int alpha);
#endif

#if OPEN_IMAGE_PIXELATE
VALUE img_image_pixelate(int argc, VALUE *argv, VALUE self);
VALUE img_image_pixelate_bang(int argc, VALUE *argv, VALUE self);
static inline void img_image_pixelate_s(Image *image, int pix, int avg_alpha);
#endif

#if OPEN_IMAGE_SOLARIZE
VALUE img_image_solarize(VALUE self, VALUE red, VALUE green, VALUE blue);
VALUE img_image_solarize_bang(VALUE self, VALUE red, VALUE green, VALUE blue);
static inline void img_image_solarize_s(Image *image, VALUE red, VALUE green, VALUE blue);
#endif

#if OPEN_IMAGE_CONTRAST
VALUE img_image_contrast(VALUE self, VALUE contrast);
VALUE img_image_contrast_bang(VALUE self, VALUE contrast);
static inline void img_image_contrast_s(Image *image, VALUE contrast);
#endif

#if OPEN_IMAGE_COLOR_BALANCE
VALUE img_image_balance(VALUE self, VALUE red, VALUE green, VALUE blue);
VALUE img_image_balance_bang(VALUE self, VALUE red, VALUE green, VALUE blue);
static inline void img_image_balance_s(Image *image, VALUE red, VALUE green, VALUE blue);
#endif

#if OPEN_IMAGE_CONVOLUTION_FILTER

VALUE img_image_convolution_filter(VALUE self, VALUE matrix);
VALUE img_image_convolution_filter_bang(VALUE self, VALUE matrix);
static inline void img_image_convolution_filter_s(Image *image, float *kernel, int kw, int kh);

#if OPEN_IMAGE_BOX_BLUR 
VALUE img_image_box_blur(VALUE self);
VALUE img_image_box_blur_bang(VALUE self);
static inline void img_image_box_blur_s(Image *image);
#endif

#if OPEN_IMAGE_GAUSSIAN_BLUR 
VALUE img_image_gaussian(VALUE self);
VALUE img_image_gaussian_bang(VALUE self);
static inline void img_image_gaussian_s(Image *image);
#endif

#if OPEN_IMAGE_SHARPEN
VALUE img_image_sharpen(VALUE self);
VALUE img_image_sharpen_bang(VALUE self);
static inline void img_image_sharpen_s(Image *image);
#endif

#if OPEN_IMAGE_EDGE_DETECT
VALUE img_image_edge_detect(VALUE self);
VALUE img_image_edge_detect_bang(VALUE self);
static inline void img_image_edge_detect_s(Image *image);
#endif

#if OPEN_IMAGE_EMBOSS
VALUE img_image_emboss(VALUE self);
VALUE img_image_emboss_bang(VALUE self);
static inline void img_image_emboss_s(Image *image);
#endif

#endif /* OPEN_IMAGE_CONVOLUTION_FILTER */
#endif /* RB_OPEN_IMAGE_IMAGE_H */