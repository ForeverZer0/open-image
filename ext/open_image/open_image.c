#include "open_image.h"

VALUE rb_mOpenImage;

void
Init_open_image(void)
{
  rb_mOpenImage = rb_define_module("OpenImage");
}
