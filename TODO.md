# TODO

## All

* `==`
* `coerce`
* `_load(binary)`
* `_dump(level = 0)`

___

## Color

* `gl` (floats between 0.0f and 1.0f)
* `hue=`
* `saturation=`
* `brightness=`

___

## Point

* `offset(x, y)`
* `offset!(point)`
* `offset!(x, y)`
* `move(x, y)`

___

## Size

* `resize(width, height)`

___

## Rect

* `inflate`
* `inflate!`
* `offset(point)`
* `offset(x, y)`
* `offset!(point)`
* `offset!(x, y)`
* `move(x, y)`
* `resize(width, height)`
* `intersect(rect)`
* `intersects?(rect)`
* `union(rect)`
* `include?(x, y)`
* `include?(point)`
* `include?(rect)`
* `alias include?, contains?`

___

## Image

* `blit(point, image)`
* `blit(x, y, image)`
* `blit(rect, image)`
* `draw_rect(x, y, width, height, color, thickness)`
* `draw_rect(rect, color, thickness)`
* `delete(color)`
* `delete!(color)`
* `adjust_tone(r, g, b)`
* `grayscale(amount)`
* `balance(r, g, b)`
* `to_texture` (?)(maybe in gem extending this one?)

## Gosu / OpenGL

* Create gem extending this one for loading directly into OpenGL texture or `Gosu::Image` / `Ashton::Texture`
* Interop `OpenImage::Color` with `Gosu::Color` / `Ashton::Color`