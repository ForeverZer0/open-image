# TODO

## All

* `==`
* `coerce`

___

## Color

* `lerp`

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
