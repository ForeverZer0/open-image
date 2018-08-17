require_relative 'open_image/version'
require_relative 'open_image/open_image'
require_relative 'open_image/colors'


require 'benchmark'

module OpenImage


  path = 'D:/Enterbrain/RGSS/Standard/Graphics/Characters/001-Fighter01.png'
  img = Image.new(path)

  # out = "C:/Users/Eric/Desktop/OUTPUT/posterize.png"
  # img.solarize(16, 16, 8).save_png(out)

  # exit

  [-1.0, -0.5, 0.0, 0.5, 1.0].each do |i|

    out = "C:/Users/Eric/Desktop/OUTPUT/contrast#{(i * 100).to_i}.png"

    img.contrast(i).save_png(out)

  end


  exit



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