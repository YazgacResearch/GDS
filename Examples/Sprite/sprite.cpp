#include <Adafruit_GFX.h>    // Core graphics library
#include <GDShield_Capabilities.h>
#include <GDShields.h>
#include "sprite.h"

Sprite::Sprite(GDS *tft, const uint16_t sprite[], uint16_t _width, uint16_t _height, uint16_t velocity, uint16_t backgroundcolor)
{
	uint16_t i;
	uint16_t mask;
	
	width = _width;
	height = _height;
  speed = velocity;
  bkcolor = backgroundcolor;
  P = Point(0, 0);
  
  // Set sprite buffer
	len = width * height;
  sbuf = (uint16_t *)malloc(len);
  sbuf[0] = pgm_read_word_near(sprite);
	mask = sbuf[0];
  for (i = 0; i < len; i++) {
    sbuf[i] = pgm_read_word_near(sprite + i);
    if (sbuf[i] == mask) sbuf[i] = bkcolor;
  }
}

void Sprite::Draw(GDS *tft, uint16_t x, uint16_t y)
{
	tft->setAddrWindow(x, y, width - 1, height - 1);
  tft->pushColors(sbuf, len, true);
  P = Point(x, y);
}

void Sprite::VScroll(GDS *tft, uint16_t xend, uint16_t yend)
{
  uint16_t ny, bl;
  bool ud;
  int dy;
  
  tft->readGRAM(P.x, P.y, sbuf, width, height);
  dy = speed;
  bl = dy * width;
  ud = (P.y < yend) ? true : false;
  if (!ud) dy = -dy;

  for (ny = P.y; (ud) ? ny < yend: ny > yend; ) {
    ny = ny + dy;

    tft->setAddrWindow(P.x, ny, P.x + width - 1, ny + height - 1);
    tft->pushColors(sbuf, len, true);
    
    if (ud) {
      tft->setAddrWindow(P.x, P.y, P.x + width - 1, ny - 1);
    } else {
      tft->setAddrWindow(P.x, ny + height, P.x + width - 1, P.y + height - 1);
    }
    tft->pushColors(bkcolor, bl, true);

    P.y = ny;
  }
}

void  Sprite::HScroll(GDS *tft, uint16_t xend, uint16_t yend)
{
  uint16_t nx, bl;
  bool lr;
  int dx;
  
  tft->readGRAM(P.x, P.y, sbuf, width, height);
  dx = speed;
  bl = dx * height;
  lr = (P.x < xend) ? true : false;
  if (!lr) dx = -dx;

  for (nx = P.x; (lr) ? nx < xend: nx > xend; ) {
    nx = P.x + dx;
    
    tft->setAddrWindow(nx, P.y, nx + width - 1, P.y + height - 1);
    tft->pushColors(sbuf, len, true);
    
    if (lr) {
      tft->setAddrWindow(P.x, P.y, nx - 1, P.y + height - 1);
    } else {
      tft->setAddrWindow(nx + width, P.y, P.x + width - 1, P.y + height - 1);
    }
    tft->pushColors(bkcolor, bl, true);
    
    P.x = nx;
  }
}


void Sprite::MoveTo(GDS *tft, int16_t xend, int16_t yend)
{
  uint16_t nx, ny;
  int16_t dx, dy;
  uint16_t ww, hh;
  uint16_t c;

  
  tft->readGRAM(P.x, P.y, sbuf, width, height);
  ww = abs(P.x - xend);
  hh = abs(P.y - yend);
  if (ww == 0) {
    VScroll(tft, xend, yend);
    return;
  }
  if (hh == 0) {
    HScroll(tft, xend, yend);
    return;
  }

  if ((P.x < xend) && (P.y < yend)) c = 1;
  if ((P.x > xend) && (P.y < yend)) c = 2;
  if ((P.x < xend) && (P.y > yend)) c = 3;
  if ((P.x > xend) && (P.y > yend)) c = 4;

  switch (c) {
  case 1:
  case 2: {
            for (nx = P.x, ny = P.y; (c == 1) ? (nx < xend) && (ny < yend) : (nx > xend) && (ny < yend); ) {
              ww = abs(P.x - xend);
              hh = abs(P.y - yend);
              dx = speed;
              dy = (hh * dx) / ww;
              if (dy == 0) {
                dy++;
                dx = ww*dy / hh;
              }
              if (c == 2) dx = -dx;
              nx = P.x + dx;
              ny = P.y + dy;
              tft->setAddrWindow(nx, ny, nx + width - 1, ny + height - 1);
              tft->pushColors(sbuf, len, true);

              tft->setAddrWindow(P.x, P.y, P.x + width - 1, ny - 1);
              tft->pushColors(bkcolor, dy * width, true);
              if (c == 1) {
                tft->setAddrWindow(P.x, ny, nx - 1, P.y + height - 1);
                tft->pushColors(bkcolor, dx * (height - dy), true);
              } else {
                tft->setAddrWindow(nx + width, ny, P.x + width , P.y + height - 1);
                tft->pushColors(bkcolor, -dx * (height - dy), true);
              }
              P.x = nx;
              P.y = ny;
            } 
            break;
          }
  case 3:
  case 4: {
            for (nx = P.x, ny = P.y; (c == 3) ? (nx < xend) && (ny > yend) : (nx > xend) && (ny > yend); ) {
              ww = abs(P.x - xend);
              hh = abs(P.y - yend);
              dx = speed;
              dy = (hh * dx) / ww;
              if (dy == 0) {
                dy++;
                dx = ww*dy / hh;
              }
              if (c == 4) dx = -dx;
              nx = P.x + dx;
              ny = P.y - dy;
              
              tft->setAddrWindow(nx, ny, nx + width - 1, ny + height - 1);
              tft->pushColors(sbuf, len, true);

              tft->setAddrWindow(P.x , ny + height, P.x + width - 1, P.y + height - 1);
              tft->pushColors(bkcolor, dy * width, true);
              if (c == 3) {              
                tft->setAddrWindow(P.x, P.y, P.x + dx - 1, ny + height - 1);
                tft->pushColors(bkcolor, dx * (height - dy), true);
              } else {
                tft->setAddrWindow(nx + width, P.y, P.x + width - 1, ny + height - 1);
                tft->pushColors(bkcolor, -dx * (height - dy), true);
              }
              P.x = nx;
              P.y = ny;
            }
            break;
          }
  }
}
