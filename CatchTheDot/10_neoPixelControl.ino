
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
int currentPos = 0;
int currColorIndex = 0;

uint32_t dotColors[3] = {   strip.Color(30, 30, 30),
                            strip.Color(30, 0 ,0),
                            strip.Color(0, 30, 0) };
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
void lightRobinPixel( uint32_t clr) {
    int pixelNum = Robin[currentPos];
    strip.setPixelColor(pixelNum, clr);
    strip.show();
}
void NextRobin() {
    lightRobinPixel(strip.Color(0, 0, 0));
    currentPos++;
    lightRobinPixel(dotColors[currColorIndex]);
}
