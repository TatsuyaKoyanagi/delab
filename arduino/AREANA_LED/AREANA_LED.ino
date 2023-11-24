#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
const uint16_t NUMBER_OF_LEDS = 60;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  gradientTheaterChase(100); }

void gradientTheaterChase(uint8_t wait) {
  // 赤から青
  uint32_t gradient[NUMBER_OF_LEDS];
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    uint8_t redValue = 255 - (i * 255 / NUMBER_OF_LEDS);
    uint8_t blueValue = i * 255 / NUMBER_OF_LEDS;
    gradient[i] = strip.Color(redValue, 0, blueValue);
  }

  for (int j = 0; j < 10; j++) { 
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor((i + q) % NUMBER_OF_LEDS, gradient[(i + q) % NUMBER_OF_LEDS]);
      }
      strip.show();
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor((i + q) % NUMBER_OF_LEDS, 0);
      }
    }
  }
}
