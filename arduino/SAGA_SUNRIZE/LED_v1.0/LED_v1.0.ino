#include <Adafruit_NeoPixel.h>

#define PIN            6  // Neopixelのデータピン
#define NUMPIXELS      60  // Neopixelの総LED数

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // 初期化時に全てのLEDをオフにする
}

void loop() {
  setStaticColors();    // 特定のセグメントで静的な色を設定
  gradientOrangeToBlue(); // LED番号29から32までをオレンジから青のグラデーションにする
  strip.show();  // LEDの状態を更新
  delay(50);     // 少し遅延を入れる
}  

void setStaticColors() {
  // LED番号1から28までオレンジ色に設定
  for (int i = 0; i < 28; i++) {
    strip.setPixelColor(i, 255, 125, 0);  // オレンジ
  }

  // LED番号33から60まで青色に設定
  for (int i = 32; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, 0, 0, 255);  // 青色
  }
}

void gradientOrangeToBlue() {
  for (int i = 28; i < 32; i++) {
    int red = map(i, 28, 32, 255, 0);
    int green = map(i, 28, 32, 165, 0);
    int blue = map(i, 28, 32, 0, 255);
    strip.setPixelColor(i, red, green, blue);  // グラデーション
  }
}
