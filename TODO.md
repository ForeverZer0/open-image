# TODO

## All

* `==`
* `coerce`
* `_load(binary)`
* `_dump(level = 0)`

___

## Color

* ~~`lightness=`~~ 
* ~~`hue=`~~
* ~~`saturation=`~~ (Saturation is different algorithm depending if HSV/HSB or HSL...)
* ~~`brightness=` (alias `value=`)~~

___

## Point

___

## Size

___

## Rect

___

## Image

* `draw_rect(x, y, width, height, color, thickness)`
* `draw_rect(rect, color, thickness)`
* `delete(color)`
* `delete!(color)`
* `adjust_tone(r, g, b)`
* `balance(r, g, b)`
* `tone(r, g, b)`
* `to_texture` (maybe in gem extending this one?)

## Gosu / OpenGL

* Create gem extending this one for loading directly into OpenGL texture or `Gosu::Image` / `Ashton::Texture`
* Interop `OpenImage::Color` with `Gosu::Color` / `Ashton::Color`
