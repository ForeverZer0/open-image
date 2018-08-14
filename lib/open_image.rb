require_relative 'open_image/version'
require_relative 'open_image/open_image'

module OpenImage

  path = 'C:/Users/Eric/Desktop/glfw-icon.png'
  # path = 'D:/Movies/Shock And Awe (2017) [BluRay] [720p] [YTS.AM]/www.YTS.AM.jpg'

  OUT_PNG = 'C:/Users/Eric/Desktop/OUT_JPG.jpg'

  img = Image.new(path)
  
  p img.save_jpg(OUT_PNG, 95)

end
