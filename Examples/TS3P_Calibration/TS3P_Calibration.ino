#include <Adafruit_GFX.h>    // Core graphics library
#include <GDShield_Capabilities.h>
#include <GDShields.h>

GDS tft;

TouchScreen ts = TouchScreen();
TSPoint tp;

uint16_t g_identifier;

uint16_t w, h;
struct POINT {
   uint16_t x, y;;
   double dx, dy;
};

POINT p1, p2, p3;
double k, kx1,kx2,kx3, ky1,ky2,ky3;
int N = 10;

// *****
void drawCrossHair(int x, int y, uint16_t color)
{
    tft.drawRect(x - 10, y - 10, 20, 20, color);
    tft.drawLine(x - 5, y, x + 5, y, color);
    tft.drawLine(x, y - 5, x, y + 5, color);
}

POINT getTestPoint(uint16_t x, uint16_t y)
{
  POINT p;

  p.x = x;
  p.y = y;
  p.dx = 0;
  p.dy = 0;
  
	return (p);
}

void drawTestBoard(void)
{
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.print("3 point calibration");
  tft.setTextSize(1);

	p1 = getTestPoint(0.25 * w, 0.50 * h);
	p2 = getTestPoint(0.75 * w, 0.25 * h);
	p3 = getTestPoint(0.75 * w, 0.75 * h);
	
  tft.setCursor(p1.x - 10, p1.y - 20);
  tft.print("("+String(p1.x)+","+String(p1.y)+")");
  Serial.println("p1 = ("+String(p1.x)+","+String(p1.y)+")");
  drawCrossHair(p1.x, p1.y, BLUE);
	
  tft.setCursor(p2.x - 10, p2.y - 20);
  tft.print("("+String(p2.x)+","+String(p2.y)+")");
  Serial.println("p2 = ("+String(p2.x)+","+String(p2.y)+")");
  drawCrossHair(p2.x, p2.y, BLUE);

  tft.setCursor(p3.x - 10, p3.y - 20);
  tft.print("("+String(p3.x)+","+String(p3.y)+")");
  Serial.println("p3 = ("+String(p3.x)+","+String(p3.y)+")");
  drawCrossHair(p3.x, p3.y, BLUE);
}

void readTestPointRaw(POINT *p)
{
  ts.setCalibrated(false);
  ts.setPressureThreshhold(150);
  tp = ts.getPoint();
	
  Serial.println("TP = ("+String(p->x)+","+String(p->y)+") ==> RAW = ("+String(tp.x)+","+String(tp.y)+")");
  p->dx = tp.x;
  p->dy = tp.y;
}

void readTestPointRawNTimes(POINT *p)
{
  int i, j;

  ts.setCalibrated(false);
  ts.setPressureThreshhold(150);
  p->dx = 0;
  p->dy = 0;
  j = N;
  for (i = 1; i <= N; i++)
  {
    tft.setTextSize(1);
    tft.fillRect(0, 0, w, 20, BLACK);
    tft.setCursor(0, 0);
    tft.print("Press " + String(j) + " times to (" + String(p->x) + "," + String(p->y) + ")");
    j--;
    tp = ts.getPoint();
    p->dx = p->dx + tp.x;
    p->dy = p->dy + tp.y;   
    drawCrossHair(p->x, p->y, RED);
    delay(1000);
    if (i < N) 
      drawCrossHair(p->x, p->y, BLUE);
  }
  p->dx = trunc(p->dx / (double)N);
  p->dy = trunc(p->dy / (double)N);
  Serial.println("TP = (" +String(p->x)+ ","+ String(p->y)+ ") -> ("+ String(p->dx,0)+ ","+ String(p->dy,0)+")");
}

void Calculate_Tree_Point_Calibration(void)
{
  double X0,X1,X2, Y0,Y1,Y2;
  double x0,x1,x2, y0,y1,y2;

  x0 = p1.x;  y0 = p1.y;
  x1 = p2.x;  y1 = p2.y;
  x2 = p3.x;  y2 = p3.y;

  X0 = p1.dx; Y0 = p1.dy;
  X1 = p2.dx; Y1 = p2.dy;
  X2 = p3.dx; Y2 = p3.dy;

  k = (X0 - X2)*(Y1-Y2) - (X1 - X2)*(Y0 - Y2);
  kx1 = ( (x0 - x2)*(Y1 - Y2) - (x1 - x2)*(Y0 - Y2) ) / k;
  kx2 = ( (x1 - x2)*(X0 - X2) - (x0 - x2)*(X1 - X2) ) / k;
  kx3 = ( Y0*(X2*x1-X1*x2) + Y1*(X0*x2-X2*x0) + Y2*(X1*x0-X0*x1) ) / k;
  Serial.println("******************************************");
  Serial.println("kx1="+String(kx1,8)+", kx2="+String(kx2,8)+", kx3="+String(kx3,8));
  Serial.println("******************************************");

  ky1 = ( (y0 - y2)*(Y1 - Y2) - (y1 - y2)*(Y0 - Y2) ) / k;
  ky2 = ( (y1 - y2)*(X0 - X2) - (y0 - y2)*(X1 - X2) ) / k;
  ky3 = ( Y0*(X2*y1-X1*y2) + Y1*(X0*y2-X2*y0) + Y2*(X1*y0-X0*y1) ) / k;
  Serial.println("******************************************");
  Serial.println("ky1="+String(ky1,8)+", k2y="+String(ky2,8)+", ky3="+String(ky3,8));
  Serial.println("******************************************");
}

void drawCalibrationTestBoard(void)
{
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.print("Press Test Points");
  tft.setTextSize(1);

  p1 = getTestPoint(0.25 * w, 0.50 * h);
  p2 = getTestPoint(0.75 * w, 0.25 * h);
  p3 = getTestPoint(0.75 * w, 0.75 * h);
  
  tft.setCursor(p1.x - 10, p1.y - 20);
  tft.print("("+String(p1.x)+","+String(p1.y)+")");
  Serial.println("p1 = ("+String(p1.x)+","+String(p1.y)+")");
  drawCrossHair(p1.x, p1.y, BLUE);
  
  tft.setCursor(p2.x - 10, p2.y - 20);
  tft.print("("+String(p2.x)+","+String(p2.y)+")");
  Serial.println("p2 = ("+String(p2.x)+","+String(p2.y)+")");
  drawCrossHair(p2.x, p2.y, BLUE);

  tft.setCursor(p3.x - 10, p3.y - 20);
  tft.print("("+String(p3.x)+","+String(p3.y)+")");
  Serial.println("p3 = ("+String(p3.x)+","+String(p3.y)+")");
  drawCrossHair(p3.x, p3.y, BLUE);
}

void readCalibratedTestPoint(POINT *p)
{
  tft.setTextSize(1);
  tft.fillRect(0, 0, w, 20, BLACK);
  tft.setCursor(0, 0);
  tft.print("Press 1 times to (" + String(p->x) + "," + String(p->y) + ")");

  tp = ts.getPoint();
  
  Serial.println("TP = ("+String(p->x)+","+String(p->y)+") ==> RAW = ("+String(tp.x)+","+String(tp.y)+")");
  drawCrossHair(tp.x, tp.y, YELLOW);
  delay(1000);
}
int AcceptOrRetry(void)
{
  tft.fillRect(0, h-20, w/2, h, GREEN);
  tft.fillRect(w/2, h-20, w, h, MAGENTA);

  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.setCursor(40, h-15);
  tft.print("Accept");
  tft.setCursor(140, h-15);
  tft.print("Retry");

  tp.y = 0;
  while (tp.y < (h-20)) tp = ts.getPoint();
  if (tp.x < (w/2)) {
    return (1); // Accept
  } else {
    return (2); // Retry
  }
}

int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t oldcolor, currentcolor;

void Draw_DrawingBoard(void)
{
    BOXSIZE = tft.width() / 6;
    tft.fillScreen(BLACK);

    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);

    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
    currentcolor = RED;
    delay(1000);
}

void setup(void) 
{
  int Ret = 0;
  
  Serial.begin(115200);
  analogReference(INTERNAL2V56);

  Serial.println();
  Serial.println();
  g_identifier = tft.readID(); //
  Serial.print("ID = 0x");
  Serial.println(g_identifier, HEX);

  tft.begin(g_identifier);//to enable ILI9327 driver code

  w = tft.width();    // x direction
  h = tft.height();   // y direction

  N = 2;
  while (1) {
  	drawTestBoard();
    delay(2000);
    readTestPointRawNTimes(&p1);
    readTestPointRawNTimes(&p2);
    readTestPointRawNTimes(&p3);
    Serial.println("Calculating");
    Calculate_Tree_Point_Calibration();
  
    ts.setCalibrationConstants( kx1,kx2,kx3, ky1,ky2,ky3 );
    ts.setCalibrated(true);
  
    drawCalibrationTestBoard();
    delay(2000);
    
    readCalibratedTestPoint(&p1);
    readCalibratedTestPoint(&p2);
    readCalibratedTestPoint(&p3);
  
    switch (Ret = AcceptOrRetry()) {
    case 1:
      Serial.println("Accept");
      break;
    case 2:
      Serial.println("Retry");
      break;
    }
    if (Ret == 1) break;
  }
  Serial.println("Please insert following 6 lines to ""GDShield_Capabilities.h"" file");
  Serial.println("#define TOUCHSCREEN_KX1 ("+String(kx1,16)+")");  
  Serial.println("#define TOUCHSCREEN_KX2 ("+String(kx2,16)+")");  
  Serial.println("#define TOUCHSCREEN_KX3 ("+String(kx3,16)+")");  

  Serial.println("#define TOUCHSCREEN_KY1 ("+String(ky1,16)+")");  
  Serial.println("#define TOUCHSCREEN_KY2 ("+String(ky2,16)+")");  
  Serial.println("#define TOUCHSCREEN_KY3 ("+String(ky3,16)+")");  

  Draw_DrawingBoard();
  ts.setCalibrated(true);
}

void loop(void) 
{
  tp = ts.getPoint();
//  xpos = tp.x;
//  ypos = tp.y;

  // are we in top color box area ?
  if (tp.y < BOXSIZE) {               //draw white border on selected color box
    oldcolor = currentcolor;

    if (tp.x < BOXSIZE) {
      currentcolor = RED;
      tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
    } else 
      if (tp.x < BOXSIZE * 2) {
        currentcolor = YELLOW;
        tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
      } else 
        if (tp.x < BOXSIZE * 3) {
          currentcolor = GREEN;
          tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
        } else 
          if (tp.x < BOXSIZE * 4) {
            currentcolor = CYAN;
            tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);
          } else 
            if (tp.x < BOXSIZE * 5) {
              currentcolor = BLUE;
              tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
            } else 
              if (tp.x < BOXSIZE * 6) {
                currentcolor = MAGENTA;
                tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, WHITE);
              }

        if (oldcolor != currentcolor) { //rub out the previous white border
            if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
            if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
            if (oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
            if (oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
            if (oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
            if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
        }
    }
    // are we in drawing area ?
    if (((tp.y - PENRADIUS) > BOXSIZE) && ((tp.y + PENRADIUS) < tft.height())) {
        tft.fillCircle(tp.x, tp.y, PENRADIUS, currentcolor);
    }
    // are we in erase area ?
    if (tp.y > tft.height() - 40) {
      // press the bottom of the screen to erase
      tft.fillRect(0, BOXSIZE, tft.width(), tft.height() - BOXSIZE, BLACK);
    }
}	
