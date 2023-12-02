#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 60
#define MAX_VAL 65  // 最大輝度の設定をする(暗い←0 ～ 255→明い)
#define DELAY_TIME 50 //待ち時間1の設定
#define DELAY_TIME2 20 //待ち時間2の設定

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS_ALL, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:

}

void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
}

void colorwave(){
  colorWipe(strip.Color(MAX_VAL,0,0),DELAY_TIME);
}