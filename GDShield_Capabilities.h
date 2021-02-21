#ifndef GDSHIELD_CAPABILITIES_H
#define GDSHIELD_CAPABILITIES_H

// Supported Shields
#define OPENSMART_ILI9327_SHIELD

// Supported Display Controllers
/*
#define SUPPORT_HX8347A
#define SUPPORT_HX8347B
#define SUPPORT_HX8347D
#define SUPPORT_HX8347G
#define SUPPORT_HX8347I
#define SUPPORT_HX8352A
#define SUPPORT_HX8352B
#define SUPPORT_HX8357D


#define SUPPORT_ILI9320
#define SUPPORT_ILI9325
#define SUPPORT_ILI9326

#define SUPPORT_ILI9327
#define ILI9327_SPECIAL								// Color Inversion
#define OFFSET_ILI9327 32             //costs about 103 bytes, 0.08s

#define SUPPORT_ILI9329
#define SUPPORT_ILI9341
#define SUPPORT_ILI9481
#define SUPPORT_ILI9486
#define SUPPORT_ILI9488

#define SUPPORT_LGDP4535

#define SUPPORT_R61303V
#define SUPPORT_R61505W
#define SUPPORT_R61509V
#define SUPPORT_R61551
#define SUPPORT_R61526
#define SUPPORT_RM68140

#define SUPPORT_S6D0139
#define SUPPORT_S6D0154
#define SUPPORT_SSD1289
#define SUPPORT_SS1963
#define SUPPORT_ST7783
#define SUPPORT_ST7789
*/

// Assign human-readable names to some common 16-bit color values:
/*
#define BLACK       (0x0000)
#define MAROON      (0x0010)
#define DARK_GREEN  (0x0400)
#define OLIVE_GREEN (0x0410)
#define NAVY_BLUE   (0x8000)
#define PURPLE      (0x8010)
#define TEAL        (0x8400)
#define GRAY        (0x8410)
#define SILVER      (0xBDF7)
#define RED         (0xF800)
#define GREEN  			(0x07E0)
#define YELLOW      (0xFFE0)
#define BLUE        (0x001F)
#define FUCHSIA     (0xF81F)
#define AQUA        (0xFFE0)
#define WHITE       (0xFFFF)
#define MONEY_GREEN (0xBED7)
#define SKY_BLUE    (0xEE54)
#define CREAM       (0xEFDF)
#define MEDIUM_GRAY (0xA513)
#define CYAN        (0x07FF)
#define MAGENTA     (0xF81F)
*/
#define ALICEBLUE                       (0x7FDF)
#define ANTIQUEWHITE                    (0x7F5A)
#define AQUA                            (0x07FF)
#define AQUAMARINE                      (0x3FFA)
#define AZURE                           (0x7FFF)
#define BEIGE                           (0x7FBB)
#define BISQUE                          (0x7F38)
#define BLACK                           (0x0000)
#define BLANCHEDALMOND                  (0x7F59)
#define BLUE                            (0x001F)
#define BLUEVIOLET                      (0x455C)
#define BROWN                           (0x5145)
#define BURLYWOOD                       (0x6DD0)
#define CADETBLUE                       (0x2CF4)
#define CHARTREUSE                      (0x3FE0)
#define CHOCOLATE                       (0x6B43)
#define CORAL                           (0x7FEA)
#define CORNFLOWERBLUE                  (0x34BD)
#define CORNSILK                        (0x7FDB)
#define CRIMSON                         (0x6CA7)
#define CYAN                            (0x07FF)
#define DARKBLUE                        (0x0011)
#define DARKCYAN                        (0x0451)
#define DARKGOLDENROD                   (0x5C21)
#define DARKGRAY                        (0x5555)
#define DARKGREEN                       (0x0320)
#define DARKGREY                        (0x5555)
#define DARKKHAKI                       (0x5DAD)
#define DARKMAGENTA                     (0x4411)
#define DARKOLIVEGREEN                  (0x2B45)
#define DARKORANGE                      (0x7C60)
#define DARKORCHID                      (0x4D99)
#define DARKRED                         (0x4400)
#define DARKSALMON                      (0x74AF)
#define DARKSEAGREEN                    (0x45F1)
#define DARKSLATEBLUE                   (0x25F1)
#define DARKSLATEGRAY                   (0x1669)
#define DARKSLATEGREY                   (0x1669)
#define DARKTURQUOISE                   (0x067A)
#define DARKVIOLET                      (0x481A)
#define DEEPPINK                        (0x7CB2)
#define DEEPSKYBLUE                     (0x05FF)
#define DIMGRAY                         (0x374D)
#define DIMGREY                         (0x374D)
#define DODGERBLUE                      (0x0C9F)
#define FIREBRICK                       (0x5904)
#define FLORALWHITE                     (0x7FDE)
#define FORESTGREEN                     (0x1444)
#define FUCHSIA                         (0x7C1F)
#define GAINSBORO                       (0x6EFB)
#define GHOSTWHITE                      (0x7FDF)
#define GOLD                            (0x7EA0)
#define GOLDENROD                       (0x6D24)
#define GRAY                            (0x4410)
#define GREEN                           (0x07E0)
#define GREENYELLOW                     (0x57E5)
#define GREY                            (0x4410)
#define HONEYDEW                        (0x7FFE)
#define HOTPINK                         (0x7F56)
#define INDIANRED                       (0x66EB)
#define INDIGO                          (0x2410)
#define IVORY                           (0x7FFE)
#define KHAKI                           (0x7F31)
#define LAVENDER                        (0x773F)
#define LAVENDERBLUSH                   (0x7F9E)
#define LAWNGREEN                       (0x3FE0)
#define LEMONCHIFFON                    (0x7FD9)
#define LIGHTBLUE                       (0x56DC)
#define LIGHTCORAL                      (0x7C10)
#define LIGHTCYAN                       (0x77FF)
#define LIGHTGOLDENRODYELLOW            (0x7FDA)
#define LIGHTGRAY                       (0x6E9A)
#define LIGHTGREEN                      (0x4F72)
#define LIGHTGREY                       (0x6E9A)
#define LIGHTPINK                       (0x7DB8)
#define LIGHTSALMON                     (0x7D0F)
#define LIGHTSEAGREEN                   (0x1595)
#define LIGHTSKYBLUE                    (0x467F)
#define LIGHTSLATEGRAY                  (0x3C53)
#define LIGHTSLATEGREY                  (0x3C53)
#define LIGHTSTEELBLUE                  (0x5E3B)
#define LIGHTYELLOW                     (0x7FFC)
#define LTGRAY                          (0x6618)
#define MEDGRAY                         (0x5514)
#define DKGRAY                          (0x4410)
#define MONEYGREEN                      (0x66F8)
#define LEGACYSKYBLUE                   (0x565E)
#define CREAM                           (0x7FDE)
#define LIME                            (0x07E0)
#define LIMEGREEN                       (0x1E66)
#define LINEN                           (0x7F9C)
#define MAGENTA                         (0xF81F)
#define MAROON                          (0x4000)
#define MEDIUMAQUAMARINE                (0x3675)
#define MEDIUMBLUE                      (0x0019)
#define MEDIUMORCHID                    (0x5EBA)
#define MEDIUMPURPLE                    (0x4B9B)
#define MEDIUMSEAGREEN                  (0x1D8E)
#define MEDIUMSLATEBLUE                 (0x3F5D)
#define MEDIUMSPRINGGREEN               (0x07D3)
#define MEDIUMTURQUOISE                 (0x2699)
#define MEDIUMVIOLETRED                 (0x60B0)
#define MIDNIGHTBLUE                    (0x0CCE)
#define MINTCREAM                       (0x7FFF)
#define MISTYROSE                       (0x7F3C)
#define MOCCASIN                        (0x7F36)
#define NAVAJOWHITE                     (0x7EF5)
#define NAVY                            (0x0010)
#define OLDLACE                         (0x7FBC)
#define OLIVE                           (0x4400)
#define OLIVEDRAB                       (0x3464)
#define ORANGE                          (0x7D20)
#define ORANGERED                       (0x7E20)
#define ORCHID                          (0x6F9A)
#define PALEGOLDENROD                   (0x7755)
#define PALEGREEN                       (0x4FD3)
#define PALETURQUOISE                   (0x577D)
#define PALEVIOLETRED                   (0x6F92)
#define PAPAYAWHIP                      (0x7F7A)
#define PEACHPUFF                       (0x7ED7)
#define PERU                            (0x6427)
#define NATURELPINK                     (0x7E19)
#define PLUM                            (0x6D1B)
#define POWDERBLUE                      (0x5F1C)
#define PURPLE                          (0x4010)
#define RED                             (0xF800)
#define ROSYBROWN                       (0x5C71)
#define ROYALBLUE                       (0x235C)
#define SADDLEBROWN                     (0x4622)
#define SALMON                          (0x7C0E)
#define SANDYBROWN                      (0x7D2C)
#define SEAGREEN                        (0x144A)
#define SEASHELL                        (0x7FBD)
#define SIENNA                          (0x5285)
#define SILVER                          (0x6618)
#define SKYBLUE                         (0x467D)
#define SLATEBLUE                       (0x36D9)
#define SLATEGRAY                       (0x3C12)
#define SLATEGREY                       (0x3C12)
#define SNOW                            (0x7FDF)
#define SPRINGGREEN                     (0x07EF)
#define STEELBLUE                       (0x2416)
#define TAN                             (0x6DB1)
#define TEAL                            (0x0410)
#define THISTLE                         (0x6DFB)
#define TOMATO                          (0x7F08)
#define TURQUOISE                       (0x271A)
#define VIOLET                          (0x741D)
#define WHEAT                           (0x7EF6)
#define WHITE                           (0xFFFF)
#define WHITESMOKE                      (0x7FBE)
#define YELLOW                          (0xFFE0)
#define YELLOWGREEN                     (0x4E66)
#define NULL                            (0x0000)


// Open Smart 3.2 inch TFT Shield (ili9327)
#ifdef OPENSMART_ILI9327_SHIELD
	#define GDS_CAPABILITIES_TFT
	#ifdef	GDS_CAPABILITIES_TFT
		#define SUPPORT_ILI9327
		//#define ILI9327_SPECIAL
		#define OFFSET_ILI9327 32             //costs about 103 bytes, 0.08s
	#endif

	#define GDS_CAPABILITIES_LM75
	#ifdef	GDS_CAPABILITIES_LM75
		#define LM75_ADDRESS 0x48
	#endif
	
	#define GDS_CAPABILITIES_TOUCHSCREEN
	#ifdef	GDS_CAPABILITIES_TOUCHSCREEN
		#define TOUCHSCREEN_YP (A1)
		#define TOUCHSCREEN_XM (A2)
		#define TOUCHSCREEN_YM (7)
		#define TOUCHSCREEN_XP (6)
		#define PRESSURE_THRESHHOLD 150

		#define TOUCHSCREEN_KX1 (0.2894502000)
		#define TOUCHSCREEN_KX2 (0.0114433800)
		#define TOUCHSCREEN_KX3 (-21.6983320000)
		#define TOUCHSCREEN_KY1 (-0.0022438001)
		#define TOUCHSCREEN_KY2 (0.4650275700)
		#define TOUCHSCREEN_KY3 (-25.8783300000)
	#endif
#endif

#endif // GDSHIELD_CAPABILITIES_H