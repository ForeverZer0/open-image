
module OpenImage

  module Colors

    def self.define_color(name, uint)
      define_singleton_method(name) { Color.new(uint) }
      @names ||= []
      @names << name.to_s.split('_').map(&:capitalize).join(' ')
    end

    def self.names
      @names
    end

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
  end
end