/*
 * generate testcard similar to BMP
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <GDShield_Capabilities.h>
#include <GDShields.h>
#if defined(_GFXFONT_H_)           //are we using the new library?
#include <Fonts/FreeSans9pt7b.h>
#define ADJ_BASELINE 11            //new fonts setCursor to bottom of letter
#else
#define ADJ_BASELINE 0             //legacy setCursor to top of letter
#endif

GDS tft;

#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))
#define GREY      RGB(127, 127, 127)
#define DARKGREY  RGB(64, 64, 64)
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,128,64)

#include <stdio.h>


uint16_t ID;

void setup(void)
{
    Serial.begin(115200);
    tft.reset();
    ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    //    if (ID == 0xD3D3) ID = 0x9481; // write-only shield
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
#if defined(_GFXFONT_H_)
    tft.setFont(&FreeSans9pt7b);
#endif
}

void CalibrationScreen(int offset, int duration, bool ShowEnd = true)
{

//  Local Definitions

    int16_t x, y, dx, dy, radius = 108, idx;
    uint16_t w, h, len, mask;
    uint16_t colors[8] = { BLACK, WHITE, YELLOW, CYAN, GREEN, MAGENTA, RED, BLUE };
    uint16_t height, width;
    uint8_t hh, mm, ss; //containers for current time
    uint16_t delay_count = 0;
    const char *timep = __TIME__ ;
    char *p;
    
    width = tft.width();
    height = tft.height();

    // Decode time
    p = timep;
    hh = 10 * (*p - '0') + (*++p - '0');
    p = timep + 3;
    mm = 10 * (*p - '0') + (*++p - '0');
    p = timep + 6;
    ss = 10 * (*p - '0') + (*++p - '0');

    // Draw Test
    tft.fillRect(offset + 0, 0, 7, 3, WHITE);
    tft.fillRect(offset + 313, 0, 7, 3, WHITE);
    tft.fillRect(offset + 0, 237, 7, 3, WHITE);
    tft.fillRect(offset + 313, 237, 7, 3, WHITE);
    for (y = 0, w = 18, h = 3; y < 240; y += 13 * w + h) {
        for (x = offset + 25; x < offset + 320 - 18; x += 2 * w) {
            tft.fillRect(x, y, w, h, WHITE);
        }
    }
    for (x = offset + 0, w = 7, h = 18; x < offset + 320; x += 17 * h + w) {
        for (y = 21; y < 240 - 18; y += 2 * h) {
            tft.fillRect(x, y, w, h, WHITE);
        }
    }
    tft.fillRect(offset + 7, 3, 17 * 18, 13 * 18, GREY);
    for (x = offset + 7, y = 0, w = 1, h = 240; x < offset + 320; x += 18) {
        tft.fillRect(x, y, w, h, WHITE);
    }
    for (x = offset + 0, y = 3, w = 320, h = 1; y < 240; y += 18) {
        tft.fillRect(x, y, w, h, WHITE);
    }
    tft.fillRect(offset + 26, 22, 17, 99, TURQUOISE);
    tft.fillRect(offset + 26, 120, 17, 99, PINK);
    tft.fillRect(offset + 44, 22, 17, 35, AZURE);
    tft.fillRect(offset + 44, 184, 17, 35, ORANGE);
    tft.fillRect(offset + 260, 22, 17, 35, AZURE);
    tft.fillRect(offset + 260, 184, 17, 35, ORANGE);
    tft.fillRect(offset + 278, 22, 17, 99, OLIVE);
    tft.fillRect(offset + 278, 120, 17, 99, PURPLE);

    for (dx = radius; dx > -radius; dx--) {
        w = sqrt(radius * radius - dx * dx);
        y = 120 - dx;
        dy = (y - 3) / 18;
        mask = 7;
        colors[0] = (dy == 3) ? DARKGREY : BLACK;
        switch (dy) {
            case 0:
            case 1: idx = 1; len = 0; break;
            case 2: idx = 0; len = 0; break;
            case 3: idx = 0; len = 13; mask = 1; break;
            case 4:
            case 5: idx = 2; len = 38; break;
            case 6:
            case 7:
            case 8: idx = 0; len = 0; break;
            case 9: for (idx = 2; idx < 8; idx++) {
                    //dy = 0xFF >> (7 - idx);
                    dy = (idx - 2) * 51;
                    colors[idx] = tft.color565(dy, dy, dy);
                }
                idx = 2; len = 38; break;
            case 10: idx = 1; len = 0; break;
            case 11:
            case 12: colors[2] = YELLOW; idx = 2; len = 0; break;
        }
        if (len == 0)
            tft.fillRect(offset + 160 - w, y, w * 2, 1, colors[idx]);

        else {
            if (mask == 1) idx = 1 + (w) / len;
            dy = w % len;
            for (x = offset + 160 - w; x < offset + 160 + w; idx++) {
                tft.fillRect(x, y, dy, 1, colors[idx & mask]);
                x += dy;
                if (x + len > offset + 160 + w) dy = w % len;
                else dy = len;
            }
        }

    }
    for (x = offset + 72, y = 129, dx = 5, dy = 0; dx > 0; x += 2 * dx) {
        tft.fillRect(x, y, dx, 36, WHITE);
        dy += dx * 2;
        if (dy >= 36) {
            dy = 0;
            dx--;
        }
    }
    tft.fillRect(offset + 160 - 8, 5 * 18 + 3, 17, 3 * 18, BLACK);
    for (x = offset + 3 * 18 + 7, y = 6 * 18 + 3, w = 1, h = 18; x < offset + 160 + 108; x += 18) {
        tft.fillRect(x, y, w, h, WHITE);
    }
    tft.fillRect(offset + 160 - 108, 120, 108 * 2, 1, WHITE);
    tft.fillRect(offset + 160, 5 * 18 + 3, 1, 3 * 18, WHITE);
    tft.fillRect(offset + 108, 2 * 18 + 3, 6 * 18, 18, WHITE);
    //    tft.fillRect(108, 10 * 18 + 3, 6 * 18, 18, BLACK);

    tft.fillRect(offset + 160 - 8, 11 * 18 + 3, 17, radius - 18*9/2, RED);
    tft.setCursor(offset  + 160 - 36, 24 + ADJ_BASELINE);
    tft.setTextColor(BLACK);
    tft.setTextSize(1);
    tft.print("320x240");
    tft.setCursor(offset + 119, 43 + ADJ_BASELINE);
    tft.setTextColor(BLACK);
    tft.setTextSize(1);
    tft.print("ID=0x");
    tft.print(tft.readID(), HEX);
    tft.setTextColor(WHITE, BLACK);
    //    tft.setFont(NULL);
    //    tft.setTextSize(2);
    
    while (1) {
        if (++ss > 59) {
            ss = 0;
            mm++;
            if (mm > 59) {
                mm = 0;
                hh++;
                if (hh > 23) hh = 0;
            }
        }
        char buf[20];
        sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
        tft.fillRect(offset + 108, 10 * 18 + 3, 6 * 18, 18, BLACK);
        tft.setCursor(offset + 128, 187 + ADJ_BASELINE);
        tft.print(buf);
        delay(1000);
        delay_count += 1;
        if (delay_count > duration) break;
    }
    if ( ShowEnd ) {
      tft.fillRect(0, 0, width, height, BLACK);
      tft.setCursor(offset + 128, 187 + ADJ_BASELINE);
      tft.print("the end");
      delay(5000);
    }
}

void loop(void)
{
 CalibrationScreen(40, 60, false);  
}
