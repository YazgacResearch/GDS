#include <Adafruit_GFX.h>    // Core graphics library
#include <GDShield_Capabilities.h>
#include <GDShields.h>

GDS tft;

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410

float version = GDSHIELDS_VERSION;

void setup()
{
    Serial.begin(115200);
    if (!Serial) delay(5000);           //allow some time for Leonardo
    uint16_t ID = tft.readID(); //
    Serial.println(F("Diagnose whether this controller is supported"));
    Serial.println(F(""));
    Serial.print(F("tft.readID() finds: ID = 0x"));
    Serial.println(ID, HEX);
    Serial.println(F(""));
	  Serial.print(F("GDS Shield version: "));
    Serial.print(String(version,2));
    
    tft.begin(ID);

    Serial.println(F(""));
    Serial.print(F("PORTRAIT is "));
    Serial.print(tft.width());
    Serial.print(F(" x "));
    Serial.println(tft.height());
    Serial.println(F(""));
    Serial.println(F("Run the examples/OpenSmart_ILI9327_Test sketch"));
    Serial.println(F("All colours, text, directions, rotations, scrolls"));
    Serial.println(F("should work.  If there is a problem,  make notes on paper"));
    Serial.println(F("Post accurate description of problem to Forum"));
    Serial.println(F("Or post a link to a video (or photos)"));
    Serial.println(F(""));
    Serial.println(F("I rely on good information from remote users"));
}

void loop()
{
    static uint8_t aspect = 0;
    const char *aspectname[] = {
        "PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV"
    };
    const char *colorname[] = { "BLUE", "GREEN", "RED", "GRAY" };
    uint16_t colormask[] = { BLUE, GREEN, RED, GRAY };
    uint16_t ID = tft.readID(); //
    tft.setRotation(aspect);
    int width = tft.width();
    int height = tft.height();
    tft.fillScreen(colormask[aspect]);
    tft.drawRect(0, 0, width, height, WHITE);
    tft.drawRect(32, 32, width - 64, height - 64, WHITE);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.setCursor(40, 40);
    tft.print("ID=0x");
    tft.print(ID, HEX);
    if (ID == 0xD3D3) tft.print(" w/o");
    tft.setCursor(40, 70);
    tft.print(aspectname[aspect]);
    tft.setCursor(40, 100);
    tft.print(width);
    tft.print(" x ");
    tft.print(height);
    tft.setTextColor(WHITE);
    tft.setCursor(40, 130);
    tft.print(colorname[aspect]);
    tft.setCursor(40, 160);
    tft.setTextSize(1);
    tft.print("gdsshields.h = ");
    tft.print(String(version,2));
    if (++aspect > 3) aspect = 0;
    delay(5000);
}
