require_relative 'open_image/version'
require_relative 'open_image/open_image'
require_relative 'open_image/colors'


require 'benchmark'

module OpenImage

  # path = 'D:/Enterbrain/RGSS/Standard/Graphics/Characters/001-Fighter01.png'
  # img = Image.new(path)

  puts Colors.white.lerp(Colors.black, 0.5)

  exit

  color = Colors.light_goldenrod_yellow

  count = 1_000_000

  Benchmark.bmbm do |x|

    x.report do 
      count.times do
        [color.hue, color.saturation, color.brightness]
      end
    end

    x.report do 
      count.times do
        color.hsb
      end
    end

  end




end