File.open('documentation.rb', 'wb') do |io|

  regex = /define_color :([a-z|_]+), 0x([\h]+)/

  file = File.readlines('lib/open_image/colors.rb').each do |line|

    match = regex.match(line)
    next unless match

    io.write("##\n")
    io.write("# @!method #{match[1]}\n")
    io.write("# @return [Color] the newly-created color\n")
    color = match[2][2, 6].downcase
    io.write("# <span style=\"background-color:##{color}; display: inline-block; width: 20px; height: 20px;\"></span>")
    io.write("\n\n")
  end
end