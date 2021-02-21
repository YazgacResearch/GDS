#ifndef GDSHIELDS_H
#define GDSHIELDS_H

#define GDSHIELDS_VERSION (1.00)

// for Color Inversion
//#define ILI9327_SPECIAL 
// for Serial tft Shiels
//#define USE_SERIAL

#include <stdint.h>
#include <arduino.h>
#include <Wire.h>

#include "Adafruit_GFX.h"
#include "GDShield_Capabilities.h"

class Point {
	public:
  	Point(void);
    Point(int16_t x, int16_t y);

    bool operator==(Point);
    bool operator!=(Point);

    int16_t x, y;
};

#ifdef GDS_CAPABILITIES_TOUCHSCREEN

class TSPoint {
	public:
  	TSPoint(void);
    TSPoint(int16_t x, int16_t y, int16_t z);

    bool operator==(TSPoint);
    bool operator!=(TSPoint);

    int16_t x, y, z;
};

class TouchScreen {
	public:
  	TouchScreen(bool _Calibrated = true,
  							uint16_t _PT = PRESSURE_THRESHHOLD,	//	Pressure Treshhold 
  							double _kx1 = TOUCHSCREEN_KX1, double _kx2 = TOUCHSCREEN_KX2, double _kx3 = TOUCHSCREEN_KX3, 
  							double _ky1 = TOUCHSCREEN_KY1, double _ky2 = TOUCHSCREEN_KY2, double _ky3 = TOUCHSCREEN_KY3);

    // int readTouchY();
    // int readTouchX();
		// uint16_t pressure(void);
    TSPoint getPoint();
    bool isTouching(void);
    void setCalibrated(bool _Calibrated);
    void setPressureThreshhold(uint16_t _PT);
    void setCalibrationConstants( double _kx1, double _kx2, double _kx3, double _ky1, double _ky2, double _ky3);

	private:
		bool Calibrated;
		uint16_t PT;
		double  kx1, kx2, kx3,  ky1, ky2, ky3;
};

#endif


#ifdef GDS_CAPABILITIES_LM75

//#define LM75_ADDRESS 0x48
#define LM75_TEMP_REGISTER 0
#define LM75_CONF_REGISTER 1
#define LM75_THYST_REGISTER 2
#define LM75_TOS_REGISTER 3

#define LM75_CONF_SHUTDOWN  0
#define LM75_CONF_OS_COMP_INT 1
#define LM75_CONF_OS_POL 2
#define LM75_CONF_OS_F_QUE 3

class LM75 {
    int address;
    word float2regdata (float);
    float regdata2float (word);
    word _register16 (byte);
    void _register16 (byte, word);
    word _register8 (byte);
    void _register8 (byte, byte);
  public:
    LM75 ();
    LM75 (byte);
    float temp (void);
    byte conf (void);
    void conf (byte);
    float tos (void);
    void tos (float);
    float thyst (void);
    void thyst (float);
    void shutdown (boolean);
    boolean shutdown (void);
};

#endif // GDS_CAPABILITIES_LM75

// *****************************************************************************

#ifdef GDS_CAPABILITIES_TFT

class GDS : public Adafruit_GFX {

	public:

//#if defined USE_GFX_KBV
//	GDS();
//#else
	  GDS(int CS=A3, int RS=A2, int WR=A1, int RD=A0, int RST=A4);
//#endif

		void     reset(void);                                       // you only need the constructor
		void     begin(uint16_t ID = 0x9341);                       // you only need the constructor
		virtual void     drawPixel(int16_t x, int16_t y, uint16_t color);  // and these three
		void     WriteCmdData(uint16_t cmd, uint16_t dat);                 // ?public methods !!!
	  void     pushCommand(uint16_t cmd, uint8_t * block, int8_t N);
		uint16_t color565(uint8_t r, uint8_t g, uint8_t b) { return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3); }
		uint16_t readID(void);
			
		virtual void     fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
		virtual void     drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) { fillRect(x, y, 1, h, color); }
		virtual void     drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) { fillRect(x, y, w, 1, color); }
		virtual void     fillScreen(uint16_t color)                                     { fillRect(0, 0, _width, _height, color); }
		virtual void     setRotation(uint8_t r);
	  virtual void     invertDisplay(boolean i);

		uint16_t readReg(uint16_t reg);
		uint32_t readReg32(uint16_t reg);
		int16_t  readGRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h);
		uint16_t readPixel(int16_t x, int16_t y) { uint16_t color; readGRAM(x, y, &color, 1, 1); return color; }
		void     setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
		void 		 pushColors(const uint16_t color, int16_t n, bool first);
		void     pushColors(uint16_t *block, int16_t n, bool first);
		void     pushColors(uint8_t *block, int16_t n, bool first);
		void     pushColors(const uint8_t *block, int16_t n, bool first);
		void     vertScroll(int16_t top, int16_t scrollines, int16_t offset);
		uint8_t flag_write_bmp;
		#ifdef GDS_CAPABILITIES_LM75
			float temp(void); // Board Temperature
		#endif
	private:
		uint16_t _lcd_ID, _lcd_rev, _lcd_madctl, _lcd_drivOut, _MC, _MP, _MW, _SC, _EC, _SP, _EP;
  	uint16_t  _lcd_xor, _lcd_capable;
		#ifdef GDS_CAPABILITIES_LM75
  		LM75 Sensor;
		#endif
};
#endif // GDS_CAPABILITIES_TFT

#endif // GDSHIELDS_H
