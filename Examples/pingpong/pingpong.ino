#include <Adafruit_GFX.h>    // Core graphics library
#include <GDShield_Capabilities.h>
#include <GDShields.h>
#include <SPI.h>          // f.k. for Arduino-1.5.2

GDS tft;

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

void setup(void);
void loop(void);

uint16_t g_identifier;
uint16_t scrollbuf[1600];    // my biggest screen is 320x480
uint16_t backgroundbuf[600];

void setup(void) {
    Serial.begin(9600);
    uint32_t when = millis();
    //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
    if (!Serial) delay(5000);           //allow some time for Leonardo
    Serial.println("Serial took " + String((millis() - when)) + "ms to start");
    //    tft.reset();                 //hardware reset
    uint16_t ID = tft.readID(); //
    Serial.print("ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; // write-only shield
//    ID = 0x9329;                             // force ID
    tft.begin(ID);
    tft.fillRect(0, 0, tft.width(), tft.height(), WHITE);
}

//    tft.pushColors(buf + 0, dx, 0);
/*  
    if (dx) for (int16_t row = 0; row < ht; row++) {
            readGRAM(x, y + row, buf, wid, 1);
            setAddrWindow(x, y + row, x + wid - 1, y + row);
            pushColors(buf + dx, wid - dx, 1);
            pushColors(buf + 0, dx, 0);
        }
    if (dy) for (int16_t col = 0; col < wid; col++) {
            readGRAM(x + col, y, buf, 1, ht);
            setAddrWindow(x + col, y, x + col, y + ht - 1);
            pushColors(buf + dy, ht - dy, 1);
            pushColors(buf + 0, dy, 0);
        }
*/        
TSPoint LeftToRightScroll(int16_t x, int16_t y, int16_t w, int16_t h, int16_t dx, int16_t xend, uint16_t *buf)
{
  uint16_t xx;
  TSPoint p;
  
  tft.readGRAM(x, y, buf, w, h);
  for (xx = x; xx < xend; xx += dx) {
    tft.setAddrWindow(x + dx, y, x + w + dx - 1, y + h - 1);
    tft.pushColors(buf, w * h, true);
    tft.setAddrWindow(x, y, x + dx - 1, y + h - 1);
    tft.pushColors(backgroundbuf, dx * h, true);
    x = x + dx;
  }
  
  p.x = x - dx;
  p.y = y;
  return (p);
}

TSPoint RightToLeftScroll(int16_t x, int16_t y, int16_t w, int16_t h, int16_t dx, int16_t xend, uint16_t *buf)
{
  uint16_t xx;
  TSPoint p;
  
  tft.readGRAM(x, y, buf, w, h);
  for (xx = x; xx > xend; xx -= dx) {
    tft.setAddrWindow(x - dx, y, x + w - dx - 1, y + h - 1);
    tft.pushColors(buf, w * h, true);
    tft.setAddrWindow(x + w - dx, y, x + w - 1, y + h - 1);
    tft.pushColors(backgroundbuf, dx * h, true);
    x = x - dx;
  }
  p.x = x + dx;
  p.y = y;
  return (p);
}

void loop(void) {
  uint16_t pixel;
  uint16_t sw, sh, deg, rgb, width, height;
  uint16_t i, j;
  uint16_t dx, dy, n, r;
  TSPoint p;

  
  extern const uint8_t icon_40x40[];
  sw = 40;  //  icon_40x40[40,40]
  sh = 40;  //  icon_40x40[40,40]

  width = tft.width();
  height = tft.height();
  tft.setRotation(0);

//            extern const uint8_t penguin[];
//            tft.setAddrWindow(wid - 40 - 40, 20 + 0, wid - 1 - 40, 20 + 39);
//            tft.pushColors(penguin, 1600, 1);
//            extern const uint8_t wifi_full[];
//            tft.setAddrWindow(wid - 40 - 40, 20 + 0, wid - 40 - 40 + 31, 20 + 31);
//            tft.pushColors(wifi_full, 1024, 1, true);


  tft.setAddrWindow(0, 0, 40 - 1, 40 - 1);
  tft.pushColors(icon_40x40, 1600, 1);
  for (i=0; i<1600; i++) backgroundbuf[i] = WHITE;
  p.x = 0; p.y = 0;
  p = LeftToRightScroll(p.x, p.y, 40, 40, 2, 200, scrollbuf);
  p = RightToLeftScroll(p.x, p.y, 40, 40, 2, 0, scrollbuf);
  delay(10000);

//    void     windowScroll(int16_t x, int16_t y, int16_t wid, int16_t ht, int16_t dx, int16_t dy, uint16_t *buf);

/*    
    delay(2000);
    for (i = height; i >= sh; i--) {
        tft.vertScroll(0, height, i);
        delay(10);
    }
    for (i = sh; i < height; i++) {
        tft.vertScroll(0, height, i);
        delay(10);
    }
  }    
  delay(10000);
*/  
/*    
  for (i = wid - 40 - 40; i < wid - 40 - 40 + 40; i++) {
    for (j = 20 + 0; j < 20 + 0 + 40; j++) {
      pixel = tft.readPixel(i, j);
      if (pixel == WHITE) tft.drawPixel(i, j, BLACK);
    }
  }
      
    for (i = 1; i <= 15; i++) {
      tft.vertScroll(0, ht, i);
      delay(10);
    }
    delay(5000);
    for (i = ht; i > 60; i--) {
      tft.vertScroll(0, ht, i);
      delay(10);
    }
    delay(5000);
//    tft.setAddrWindow(0, 0, wid - 1, ht - 1);
//    if (aspect & 1) tft.drawRect(wid - 1, 0, 1, ht, WHITE);
//    else tft.drawRect(0, ht - 1, wid, 1, WHITE);
*/
}
