require_relative 'open_image/version'
require_relative 'open_image/open_image'
require_relative 'open_image/colors'


require 'benchmark'

module OpenImage

  # path = 'D:/Enterbrain/RGSS/Standard/Graphics/Characters/001-Fighter01.png'
  # img = Image.new(path)

  # puts Colors.white.lerp(Colors.black, 0.5)

  # exit

  color = Colors.red

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