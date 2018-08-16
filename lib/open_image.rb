require_relative 'open_image/version'
require_relative 'open_image/open_image'
require_relative 'open_image/colors'


require 'benchmark'

module OpenImage

  path = 'D:/Enterbrain/RGSS/Standard/Graphics/Characters/001-Fighter01.png'
  img = Image.new(path)

  out = 'C:/Users/Eric/Desktop/OUTPUT/gray.png'

  img.sepia
  
  img.save_png(out)

  exit

  color = Colors.red

  color.r = 278
  color.a = -1.7

  p [color.r, color.g, color.b, color.a] 
  p [color.red, color.green, color.blue, color.alpha] 


  # count = 1_000_000
  # Benchmark.bmbm do |x|

  #   x.report do 
  #     count.times do
  #       360 * 0.016666666666
  #     end
  #   end

  #   x.report do 
  #     count.times do
  #       360 / 60.0
  #     end
  #   end

  # end




end