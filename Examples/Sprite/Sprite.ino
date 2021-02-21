#include <Adafruit_GFX.h>    // Core graphics library
#include <GDShield_Capabilities.h>
#include <GDShields.h>

#include "sprite.h"

GDS tft;


#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif


uint16_t g_identifier;
extern const unsigned int smile_40x40r[];
Sprite Smile(&tft, smile_40x40r, 40, 40, 1, BLACK);
Point P;

void setup(void) {
    Serial.begin(115200);
    uint16_t ID = tft.readID(); //
    tft.begin(ID);
//  tft.setRotation(0);
    //Sprite Smile(&tft, smile_40x40r, 40, 40, 1, BLACK);
    tft.fillRect(0, 0, tft.width(), tft.height(), BLACK);
    Smile.Draw(&tft, 0,0);
//    tft.setAddrWindow(40, 0, 40 + 40 - 1, 40 - 1);
//    tft.pushColors(RED, 1600, true);
//    Smile.VScroll(& tft, 0, 0, 40, 40, 1, 0 , h  - 40);

    
//    Smile.VScroll(&tft, 0, tft.height() - Smile.height);
//    Smile.HScroll(&tft, tft.width() - Smile.width, 0);
//    Smile.VScroll(&tft, tft.width() - Smile.width, 0);
//    Smile.HScroll(&tft, 0, 0);
}

void loop(void) {
  Smile.MoveTo(&tft, tft.width()  - 40, tft.height()  - 40);
  Smile.MoveTo(&tft, 0, 0);
  Smile.HScroll(&tft, tft.width() - Smile.width, 0);
  Smile.MoveTo(&tft, 0, tft.height()  - 40);
  Smile.MoveTo(&tft, tft.width() - Smile.width, 0);
  Smile.MoveTo(&tft, 0, 0);
//  Smile.VScroll(&tft, 0, tft.height() - Smile.height);
//  Smile.VScroll(&tft, 0, 0);
/*
  uint16_t i, j;
  uint16_t w, h;
  uint16_t Sw = 40, Sh = 40;
  int16_t velocity = 1;

  w = tft.width();
  h = tft.height();
*/  

/*
  P = MoveTo(P.x, P.y, 40, 40, velocity, P.x , P.y + h  - 40, sbuf);
  delay(2000);
  P = MoveTo(P.x, P.y, 40, 40, velocity, P.x + w - 40 , 0, sbuf);
  delay(2000);
  P = MoveTo(P.x, P.y, 40, 40, velocity, 0 , h - 40, sbuf);
  delay(2000);
  P = MoveTo(P.x, P.y, 40, 40, velocity, P.x , 0, sbuf);
  delay(2000);
//  P = MoveTo(P.x, P.y, 40, 40, velocity, P.x, 0, sbuf);
//  delay(2000);
//  P = MoveTo(P.x, P.y, 40, 40, velocity, 0, P.y, sbuf);
//  delay(2000);
*/  
}
