
module OpenImage

  ##
  # Module containing convenience methods for defining, retrieving, and
  # enumerating preset named {Color} objects.
  module Colors

    # @!group Helper Methods

    ##
    # Dynamically defines a static method to return a named color.
    #
    # @param name [String, Symbol] The name of the color.
    # @param uint [Integer] An unsigned integer defining the color in AARRGGBB
    #   format.
    #
    # @return [void]
    def self.define_color(name, uint)
      define_singleton_method(name) { Color.new(uint) }
      @names ||= []
      @names << name.to_s.split('_').map(&:capitalize).join(' ')
    end

    ##
    # Returns an array containing the formatted names of each color defined in
    # the {Colors} module.
    #
    # Formatted where each `_` will be replaced with a space, and each word
    # segment is capitalized.
    #
    # `:alice_blue` becomes `"Alice Blue"`
    #
    # `:light_goldenrod_yellow` becomes `"Light Goldenrod Yellow"`
    # 
    # @return [Array<String>] the names array.
    def self.names
      @names
    end

    ##
    # Enumerates the pre-defined colors.
    #
    # @overload each
    #   When called with a block, yields each color to the block.
    #
    #   @yield [color] Yields a color to the block.
    #   @yieldparam color [Color] The currently enumerated color object.
    #
    #   @return [void]
    #
    # @overload each
    #   When called without a block, returns an enumerator for the colors.
    #
    #   @return [Enumerator]
    def self.each
      return enum_for __method__ unless block_given?
      @names.each do |name|
        sym = name.downcase.tr(' ', '_').to_sym
        yield method(sym).call rescue next
      end
    end

    # @!endgroup

    define_color :alice_blue, 0xFFF0F8FF
    define_color :antique_white, 0xFFFAEBD7
    define_color :aqua, 0xFF00FFFF
    define_color :aquamarine, 0xFF7FFFD4
    define_color :azure, 0xFFF0FFFF
    define_color :beige, 0xFFF5F5DC
    define_color :bisque, 0xFFFFE4C4
    define_color :black, 0xFF000000
    define_color :blanched_almond, 0xFFFFEBCD
    define_color :blue, 0xFF0000FF
    define_color :blue_violet, 0xFF8A2BE2
    define_color :brown, 0xFFA52A2A
    define_color :burly_wood, 0xFFDEB887
    define_color :cadet_blue, 0xFF5F9EA0
    define_color :chartreuse, 0xFF7FFF00
    define_color :chocolate, 0xFFD2691E
    define_color :coral, 0xFFFF7F50
    define_color :cornflower_blue, 0xFF6495ED
    define_color :cornsilk, 0xFFFFF8DC
    define_color :crimson, 0xFFDC143C
    define_color :cyan, 0xFF00FFFF
    define_color :dark_blue, 0xFF00008B
    define_color :dark_cyan, 0xFF008B8B
    define_color :dark_goldenrod, 0xFFB8860B
    define_color :dark_gray, 0xFFA9A9A9
    define_color :dark_green, 0xFF006400
    define_color :dark_khaki, 0xFFBDB76B
    define_color :dark_magenta, 0xFF8B008B
    define_color :dark_olive_green, 0xFF556B2F
    define_color :dark_orange, 0xFFFF8C00
    define_color :dark_orchid, 0xFF9932CC
    define_color :dark_red, 0xFF8B0000
    define_color :dark_salmon, 0xFFE9967A
    define_color :dark_sea_green, 0xFF8FBC8F
    define_color :dark_slate_blue, 0xFF483D8B
    define_color :dark_slate_gray, 0xFF2F4F4F
    define_color :dark_turquoise, 0xFF00CED1
    define_color :dark_violet, 0xFF9400D3
    define_color :deep_pink, 0xFFFF1493
    define_color :deep_sky_blue, 0xFF00BFFF
    define_color :dim_gray, 0xFF696969
    define_color :dodger_blue, 0xFF1E90FF
    define_color :firebrick, 0xFFB22222
    define_color :floral_white, 0xFFFFFAF0
    define_color :forest_green, 0xFF228B22
    define_color :fuchsia, 0xFFFF00FF
    define_color :gainsboro, 0xFFDCDCDC
    define_color :ghost_white, 0xFFF8F8FF
    define_color :gold, 0xFFFFD700
    define_color :goldenrod, 0xFFDAA520
    define_color :gray, 0xFF808080
    define_color :green, 0xFF008000
    define_color :green_yellow, 0xFFADFF2F
    define_color :honeydew, 0xFFF0FFF0
    define_color :hot_pink, 0xFFFF69B4
    define_color :indian_red, 0xFFCD5C5C
    define_color :indigo, 0xFF4B0082
    define_color :ivory, 0xFFFFFFF0
    define_color :khaki, 0xFFF0E68C
    define_color :lavender, 0xFFE6E6FA
    define_color :lavender_blush, 0xFFFFF0F5
    define_color :lawn_green, 0xFF7CFC00
    define_color :lemon_chiffon, 0xFFFFFACD
    define_color :light_blue, 0xFFADD8E6
    define_color :light_coral, 0xFFF08080
    define_color :light_cyan, 0xFFE0FFFF
    define_color :light_goldenrod_yellow, 0xFFFAFAD2
    define_color :light_green, 0xFF90EE90
    define_color :light_gray, 0xFFD3D3D3
    define_color :light_pink, 0xFFFFB6C1
    define_color :light_salmon, 0xFFFFA07A
    define_color :light_sea_green, 0xFF20B2AA
    define_color :light_sky_blue, 0xFF87CEFA
    define_color :light_slate_gray, 0xFF778899
    define_color :light_steel_blue, 0xFFB0C4DE
    define_color :light_yellow, 0xFFFFFFE0
    define_color :lime, 0xFF00FF00
    define_color :lime_green, 0xFF32CD32
    define_color :linen, 0xFFFAF0E6
    define_color :magenta, 0xFFFF00FF
    define_color :maroon, 0xFF800000
    define_color :medium_aquamarine, 0xFF66CDAA
    define_color :medium_blue, 0xFF0000CD
    define_color :medium_orchid, 0xFFBA55D3
    define_color :medium_purple, 0xFF9370DB
    define_color :medium_sea_green, 0xFF3CB371
    define_color :medium_slate_blue, 0xFF7B68EE
    define_color :medium_spring_green, 0xFF00FA9A
    define_color :medium_turquoise, 0xFF48D1CC
    define_color :medium_violet_red, 0xFFC71585
    define_color :midnight_blue, 0xFF191970
    define_color :mint_cream, 0xFFF5FFFA
    define_color :misty_rose, 0xFFFFE4E1
    define_color :moccasin, 0xFFFFE4B5
    define_color :navajo_white, 0xFFFFDEAD
    define_color :navy, 0xFF000080
    define_color :old_lace, 0xFFFDF5E6
    define_color :olive, 0xFF808000
    define_color :olive_drab, 0xFF6B8E23
    define_color :orange, 0xFFFFA500
    define_color :orange_red, 0xFFFF4500
    define_color :orchid, 0xFFDA70D6
    define_color :pale_goldenrod, 0xFFEEE8AA
    define_color :pale_green, 0xFF98FB98
    define_color :pale_turquoise, 0xFFAFEEEE
    define_color :pale_violet_red, 0xFFDB7093
    define_color :papaya_whip, 0xFFFFEFD5
    define_color :peach_puff, 0xFFFFDAB9
    define_color :peru, 0xFFCD853F
    define_color :pink, 0xFFFFC0CB
    define_color :plum, 0xFFDDA0DD
    define_color :powder_blue, 0xFFB0E0E6
    define_color :purple, 0xFF800080
    define_color :red, 0xFFFF0000
    define_color :rosy_brown, 0xFFBC8F8F
    define_color :royal_blue, 0xFF4169E1
    define_color :saddle_brown, 0xFF8B4513
    define_color :salmon, 0xFFFA8072
    define_color :sandy_brown, 0xFFF4A460
    define_color :sea_green, 0xFF2E8B57
    define_color :sea_shell, 0xFFFFF5EE
    define_color :sienna, 0xFFA0522D
    define_color :silver, 0xFFC0C0C0
    define_color :sky_blue, 0xFF87CEEB
    define_color :slate_blue, 0xFF6A5ACD
    define_color :slate_gray, 0xFF708090
    define_color :snow, 0xFFFFFAFA
    define_color :spring_green, 0xFF00FF7F
    define_color :steel_blue, 0xFF4682B4
    define_color :tan, 0xFFD2B48C
    define_color :teal, 0xFF008080
    define_color :thistle, 0xFFD8BFD8
    define_color :tomato, 0xFFFF6347
    define_color :transparent, 0x00FFFFFF
    define_color :turquoise, 0xFF40E0D0
    define_color :violet, 0xFFEE82EE
    define_color :wheat, 0xFFF5DEB3
    define_color :white, 0xFFFFFFFF
    define_color :white_smoke, 0xFFF5F5F5
    define_color :yellow, 0xFFFFFF00
    define_color :yellow_green, 0xFF9ACD32

    class << self

      ##
      # @!method alice_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#f0f8ff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method antique_white
      # @return [Color] the newly-created color
      # <span style="background-color:#faebd7; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method aqua
      # @return [Color] the newly-created color
      # <span style="background-color:#00ffff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method aquamarine
      # @return [Color] the newly-created color
      # <span style="background-color:#7fffd4; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method azure
      # @return [Color] the newly-created color
      # <span style="background-color:#f0ffff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method beige
      # @return [Color] the newly-created color
      # <span style="background-color:#f5f5dc; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method bisque
      # @return [Color] the newly-created color
      # <span style="background-color:#ffe4c4; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method black
      # @return [Color] the newly-created color
      # <span style="background-color:#000000; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method blanched_almond
      # @return [Color] the newly-created color
      # <span style="background-color:#ffebcd; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method blue
      # @return [Color] the newly-created color
      # <span style="background-color:#0000ff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method blue_violet
      # @return [Color] the newly-created color
      # <span style="background-color:#8a2be2; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method brown
      # @return [Color] the newly-created color
      # <span style="background-color:#a52a2a; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method burly_wood
      # @return [Color] the newly-created color
      # <span style="background-color:#deb887; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method cadet_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#5f9ea0; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method chartreuse
      # @return [Color] the newly-created color
      # <span style="background-color:#7fff00; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method chocolate
      # @return [Color] the newly-created color
      # <span style="background-color:#d2691e; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method coral
      # @return [Color] the newly-created color
      # <span style="background-color:#ff7f50; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method cornflower_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#6495ed; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method cornsilk
      # @return [Color] the newly-created color
      # <span style="background-color:#fff8dc; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method crimson
      # @return [Color] the newly-created color
      # <span style="background-color:#dc143c; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method cyan
      # @return [Color] the newly-created color
      # <span style="background-color:#00ffff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#00008b; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_cyan
      # @return [Color] the newly-created color
      # <span style="background-color:#008b8b; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_goldenrod
      # @return [Color] the newly-created color
      # <span style="background-color:#b8860b; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_gray
      # @return [Color] the newly-created color
      # <span style="background-color:#a9a9a9; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_green
      # @return [Color] the newly-created color
      # <span style="background-color:#006400; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_khaki
      # @return [Color] the newly-created color
      # <span style="background-color:#bdb76b; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_magenta
      # @return [Color] the newly-created color
      # <span style="background-color:#8b008b; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_olive_green
      # @return [Color] the newly-created color
      # <span style="background-color:#556b2f; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_orange
      # @return [Color] the newly-created color
      # <span style="background-color:#ff8c00; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_orchid
      # @return [Color] the newly-created color
      # <span style="background-color:#9932cc; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_red
      # @return [Color] the newly-created color
      # <span style="background-color:#8b0000; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_salmon
      # @return [Color] the newly-created color
      # <span style="background-color:#e9967a; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_sea_green
      # @return [Color] the newly-created color
      # <span style="background-color:#8fbc8f; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_slate_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#483d8b; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_slate_gray
      # @return [Color] the newly-created color
      # <span style="background-color:#2f4f4f; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_turquoise
      # @return [Color] the newly-created color
      # <span style="background-color:#00ced1; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dark_violet
      # @return [Color] the newly-created color
      # <span style="background-color:#9400d3; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method deep_pink
      # @return [Color] the newly-created color
      # <span style="background-color:#ff1493; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method deep_sky_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#00bfff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dim_gray
      # @return [Color] the newly-created color
      # <span style="background-color:#696969; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method dodger_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#1e90ff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method firebrick
      # @return [Color] the newly-created color
      # <span style="background-color:#b22222; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method floral_white
      # @return [Color] the newly-created color
      # <span style="background-color:#fffaf0; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method forest_green
      # @return [Color] the newly-created color
      # <span style="background-color:#228b22; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method fuchsia
      # @return [Color] the newly-created color
      # <span style="background-color:#ff00ff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method gainsboro
      # @return [Color] the newly-created color
      # <span style="background-color:#dcdcdc; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method ghost_white
      # @return [Color] the newly-created color
      # <span style="background-color:#f8f8ff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method gold
      # @return [Color] the newly-created color
      # <span style="background-color:#ffd700; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method goldenrod
      # @return [Color] the newly-created color
      # <span style="background-color:#daa520; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method gray
      # @return [Color] the newly-created color
      # <span style="background-color:#808080; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method green
      # @return [Color] the newly-created color
      # <span style="background-color:#008000; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method green_yellow
      # @return [Color] the newly-created color
      # <span style="background-color:#adff2f; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method honeydew
      # @return [Color] the newly-created color
      # <span style="background-color:#f0fff0; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method hot_pink
      # @return [Color] the newly-created color
      # <span style="background-color:#ff69b4; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method indian_red
      # @return [Color] the newly-created color
      # <span style="background-color:#cd5c5c; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method indigo
      # @return [Color] the newly-created color
      # <span style="background-color:#4b0082; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method ivory
      # @return [Color] the newly-created color
      # <span style="background-color:#fffff0; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method khaki
      # @return [Color] the newly-created color
      # <span style="background-color:#f0e68c; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method lavender
      # @return [Color] the newly-created color
      # <span style="background-color:#e6e6fa; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method lavender_blush
      # @return [Color] the newly-created color
      # <span style="background-color:#fff0f5; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method lawn_green
      # @return [Color] the newly-created color
      # <span style="background-color:#7cfc00; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method lemon_chiffon
      # @return [Color] the newly-created color
      # <span style="background-color:#fffacd; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#add8e6; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_coral
      # @return [Color] the newly-created color
      # <span style="background-color:#f08080; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_cyan
      # @return [Color] the newly-created color
      # <span style="background-color:#e0ffff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_goldenrod_yellow
      # @return [Color] the newly-created color
      # <span style="background-color:#fafad2; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_green
      # @return [Color] the newly-created color
      # <span style="background-color:#90ee90; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_gray
      # @return [Color] the newly-created color
      # <span style="background-color:#d3d3d3; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_pink
      # @return [Color] the newly-created color
      # <span style="background-color:#ffb6c1; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_salmon
      # @return [Color] the newly-created color
      # <span style="background-color:#ffa07a; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_sea_green
      # @return [Color] the newly-created color
      # <span style="background-color:#20b2aa; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_sky_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#87cefa; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_slate_gray
      # @return [Color] the newly-created color
      # <span style="background-color:#778899; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_steel_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#b0c4de; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method light_yellow
      # @return [Color] the newly-created color
      # <span style="background-color:#ffffe0; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method lime
      # @return [Color] the newly-created color
      # <span style="background-color:#00ff00; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method lime_green
      # @return [Color] the newly-created color
      # <span style="background-color:#32cd32; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method linen
      # @return [Color] the newly-created color
      # <span style="background-color:#faf0e6; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method magenta
      # @return [Color] the newly-created color
      # <span style="background-color:#ff00ff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method maroon
      # @return [Color] the newly-created color
      # <span style="background-color:#800000; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_aquamarine
      # @return [Color] the newly-created color
      # <span style="background-color:#66cdaa; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#0000cd; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_orchid
      # @return [Color] the newly-created color
      # <span style="background-color:#ba55d3; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_purple
      # @return [Color] the newly-created color
      # <span style="background-color:#9370db; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_sea_green
      # @return [Color] the newly-created color
      # <span style="background-color:#3cb371; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_slate_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#7b68ee; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_spring_green
      # @return [Color] the newly-created color
      # <span style="background-color:#00fa9a; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_turquoise
      # @return [Color] the newly-created color
      # <span style="background-color:#48d1cc; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method medium_violet_red
      # @return [Color] the newly-created color
      # <span style="background-color:#c71585; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method midnight_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#191970; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method mint_cream
      # @return [Color] the newly-created color
      # <span style="background-color:#f5fffa; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method misty_rose
      # @return [Color] the newly-created color
      # <span style="background-color:#ffe4e1; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method moccasin
      # @return [Color] the newly-created color
      # <span style="background-color:#ffe4b5; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method navajo_white
      # @return [Color] the newly-created color
      # <span style="background-color:#ffdead; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method navy
      # @return [Color] the newly-created color
      # <span style="background-color:#000080; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method old_lace
      # @return [Color] the newly-created color
      # <span style="background-color:#fdf5e6; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method olive
      # @return [Color] the newly-created color
      # <span style="background-color:#808000; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method olive_drab
      # @return [Color] the newly-created color
      # <span style="background-color:#6b8e23; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method orange
      # @return [Color] the newly-created color
      # <span style="background-color:#ffa500; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method orange_red
      # @return [Color] the newly-created color
      # <span style="background-color:#ff4500; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method orchid
      # @return [Color] the newly-created color
      # <span style="background-color:#da70d6; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method pale_goldenrod
      # @return [Color] the newly-created color
      # <span style="background-color:#eee8aa; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method pale_green
      # @return [Color] the newly-created color
      # <span style="background-color:#98fb98; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method pale_turquoise
      # @return [Color] the newly-created color
      # <span style="background-color:#afeeee; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method pale_violet_red
      # @return [Color] the newly-created color
      # <span style="background-color:#db7093; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method papaya_whip
      # @return [Color] the newly-created color
      # <span style="background-color:#ffefd5; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method peach_puff
      # @return [Color] the newly-created color
      # <span style="background-color:#ffdab9; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method peru
      # @return [Color] the newly-created color
      # <span style="background-color:#cd853f; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method pink
      # @return [Color] the newly-created color
      # <span style="background-color:#ffc0cb; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method plum
      # @return [Color] the newly-created color
      # <span style="background-color:#dda0dd; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method powder_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#b0e0e6; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method purple
      # @return [Color] the newly-created color
      # <span style="background-color:#800080; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method red
      # @return [Color] the newly-created color
      # <span style="background-color:#ff0000; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method rosy_brown
      # @return [Color] the newly-created color
      # <span style="background-color:#bc8f8f; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method royal_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#4169e1; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method saddle_brown
      # @return [Color] the newly-created color
      # <span style="background-color:#8b4513; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method salmon
      # @return [Color] the newly-created color
      # <span style="background-color:#fa8072; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method sandy_brown
      # @return [Color] the newly-created color
      # <span style="background-color:#f4a460; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method sea_green
      # @return [Color] the newly-created color
      # <span style="background-color:#2e8b57; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method sea_shell
      # @return [Color] the newly-created color
      # <span style="background-color:#fff5ee; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method sienna
      # @return [Color] the newly-created color
      # <span style="background-color:#a0522d; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method silver
      # @return [Color] the newly-created color
      # <span style="background-color:#c0c0c0; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method sky_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#87ceeb; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method slate_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#6a5acd; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method slate_gray
      # @return [Color] the newly-created color
      # <span style="background-color:#708090; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method snow
      # @return [Color] the newly-created color
      # <span style="background-color:#fffafa; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method spring_green
      # @return [Color] the newly-created color
      # <span style="background-color:#00ff7f; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method steel_blue
      # @return [Color] the newly-created color
      # <span style="background-color:#4682b4; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method tan
      # @return [Color] the newly-created color
      # <span style="background-color:#d2b48c; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method teal
      # @return [Color] the newly-created color
      # <span style="background-color:#008080; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method thistle
      # @return [Color] the newly-created color
      # <span style="background-color:#d8bfd8; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method tomato
      # @return [Color] the newly-created color
      # <span style="background-color:#ff6347; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method transparent
      # @return [Color] the newly-created color
      # <span style="background-color:#ffffff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method turquoise
      # @return [Color] the newly-created color
      # <span style="background-color:#40e0d0; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method violet
      # @return [Color] the newly-created color
      # <span style="background-color:#ee82ee; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method wheat
      # @return [Color] the newly-created color
      # <span style="background-color:#f5deb3; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method white
      # @return [Color] the newly-created color
      # <span style="background-color:#ffffff; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method white_smoke
      # @return [Color] the newly-created color
      # <span style="background-color:#f5f5f5; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method yellow
      # @return [Color] the newly-created color
      # <span style="background-color:#ffff00; display: inline-block; width: 20px; height: 20px;"></span>

      ##
      # @!method yellow_green
      # @return [Color] the newly-created color
      # <span style="background-color:#9acd32; display: inline-block; width: 20px; height: 20px;"></span>
    end
  end
end