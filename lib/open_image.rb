require_relative 'open_image/version'
require_relative 'open_image/open_image'
require_relative 'open_image/colors'


require 'benchmark'


module OpenImage


  # path = 'D:/Enterbrain/RGSS/Standard/Graphics/Characters/001-Fighter01.png'
  path = 'C:/Users/Eric/Desktop/test.jpg'
  img = Image.new(path)

  out = "C:/Users/Eric/Desktop/OUTPUT/box_blur.png"
  img.blur.save_png out

  exit
  
  # img.soften.save_png(out)

  # exit

  [1, 2, 4, 8, 10].each do |i|

    out = "C:/Users/Eric/Desktop/OUTPUT/blur#{i}.png"

    img.blur(i).save_png(out)

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