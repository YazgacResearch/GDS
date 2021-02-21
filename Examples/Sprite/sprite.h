#include <Adafruit_GFX.h>    // Core graphics library
#include <GDShield_Capabilities.h>
#include <GDShields.h>

class Sprite {

	public:
    
    uint16_t width, height;
    Point P;

		Sprite(GDS *tft, const uint16_t sprite[], uint16_t _width, uint16_t _height, uint16_t velocity, uint16_t backgroundcolor);
    void  Draw(GDS *tft, uint16_t x, uint16_t y);
		void  VScroll(GDS *tft, uint16_t xend, uint16_t yend);
		void  HScroll(GDS *tft, uint16_t xend, uint16_t yend);
    void  MoveTo(GDS *tft, int16_t xend, int16_t yend);

	private:
		uint16_t *sbuf;
    uint16_t bkcolor;
		uint16_t len;
		uint16_t speed;
};
