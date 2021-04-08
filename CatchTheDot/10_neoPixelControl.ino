
#include <Adafruit_NeoPixel.h>
#define MATRIX_ROWS 8
#define MATRIX_COLS 8
#define MATRIX_TOTAL 64

#define PIN 6         // Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MATRIX_TOTAL, PIN, NEO_GRB + NEO_KHZ800);

#define ROBIN_LEN 12
int Robin[ROBIN_LEN] = { 21,20,19,18,26,34,42,43,44,45,37,29 };
#define Ring2_Len 20
int Robin2[Ring2_Len] = { 14,13,12,11,10,9,17,25,33,41,49,50,51,52,53,54,46,38,30,22 };
int middleRect[4] = { 27,28,35,36 };
int currentPos = 0;
int currColorIndex = 0;

uint32_t dotColors[3] = {   strip.Color(30, 30, 30),
                            strip.Color(30, 0 ,0),
                            strip.Color(0, 30, 0) };
void neoSetup() {
    strip.begin();
}
void slowLightAll(uint32_t clr) {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, clr);
        strip.show();
        delay(20);
    }
}
void slowOffAll() {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
        strip.show();
        delay(40);
    }
    delay(200);
}
void MatOffAll() {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
    }
    strip.show();
}
void lightRobinPixel( uint32_t clr) {
    //int pixelNum = Robin[currentPos];
    int pixelNum = Robin2[currentPos];
    strip.setPixelColor(pixelNum, clr);
    strip.show();
}
void NextRobin() {
    lightRobinPixel(strip.Color(0, 0, 0));
    currentPos++;
    //currentPos %= ROBIN_LEN;
    currentPos %= Ring2_Len;
    lightRobinPixel(dotColors[currColorIndex]);
}
void newRound() {
    colorsEnabled = false;
    currentPos = 0;
    currColorIndex = 0;
    lastLightStartedMs = millis();
    lastOffStartTimeMs = millis();
}
void chooseColor() {
    if (colorsEnabled) {
        if (colorIsOn) {
            if (millis() - lastColoredStartTimeMs >= colorONtimeMs) {
                currColorIndex = 0;
                colorIsOn = false;
                lastOffStartTimeMs = millis();
                colorsEnabled = false;
            }
        }
        else {
            if (random(10) >= 7) {
                colorIsOn = true;
                lastColoredStartTimeMs = millis();
                currColorIndex = random(1, 3);
            }
        }
    }
    else {
        currColorIndex = 0;
        colorIsOn = false;
        if (millis() - lastOffStartTimeMs >= colorOFFtimeMs) {
            colorsEnabled = true;
        }
    }
}
bool isRed() {
    return (colorIsOn && currColorIndex == 1);
}
bool isGreen() {
    return (colorIsOn && currColorIndex == 2);
}
void LightUpperLineInGreen() {
    for (int pixelNum = 56; pixelNum < 64; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 30, 0));
    }
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(0, 30, 0));
    }
    strip.show();
    delay(500);
    for (int pixelNum = 56; pixelNum < 64; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
    }
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(0, 0, 0));
    }
    strip.show();

}
void LightLowerLineInRed() {
    for (int pixelNum = 0; pixelNum < 8; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(30, 0, 0));
    }
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(30, 0, 0));
    }
    strip.show();
    delay(500);
    for (int pixelNum = 0; pixelNum < 8; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
    }
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(0, 0, 0));
    }
    strip.show();

}