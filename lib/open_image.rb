require_relative 'open_image/version'
require_relative 'open_image/open_image'
require_relative 'open_image/colors'


require 'benchmark'


module OpenImage





  # path = 'D:/Enterbrain/RGSS/Standard/Graphics/Characters/001-Fighter01.png'
  path = 'C:/Users/Eric/Desktop/test.jpg'
  path = 'C:/Users/Eric/Downloads/DSCN1638.JPG'
  img = Image.new(path)

  [0, 1, 2, 3].each_with_index do |i, ii|

    out = "C:/Users/Eric/Desktop/OUTPUT/line_detect#{ii}.png"

    img.line_detect(i).save_png(out)

  end

  exit


  out = "C:/Users/Eric/Desktop/OUTPUT/blur.png"
  img.blur.save_png out

  # out = "C:/Users/Eric/Desktop/OUTPUT/emboss.png"
  # img.emboss.save_png out

  # out = "C:/Users/Eric/Desktop/OUTPUT/sharpen.png"
  # img.sharpen.save_png out

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