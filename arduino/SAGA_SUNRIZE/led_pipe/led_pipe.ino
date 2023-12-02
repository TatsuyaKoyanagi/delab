#include <Adafruit_NeoPixel.h>
#define PIN            6  // NeoPixelデータピン
#define NUMPIXELS      60 // NeoPixelの数
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show(); // NeoPixelを初期化して消灯状態にする
}
void loop() {
  // オレンジから消灯へのグラデーション
  orangeToOff(50); // グラデーションの速さを設定（適宜調整）
  // 消灯から水色へのグラデーション
  offToCyan(50); // グラデーションの速さを設定（適宜調整）
}
// オレンジから消灯へのグラデーション
void orangeToOff(int wait) {
  for (int i = 255; i >= 0; i--) {
    strip.fill(strip.Color(255, i, 0));
    strip.show();
    delay(wait);
  }
  strip.clear();
  strip.show();
}
// 消灯から水色へのグラデーション
void offToCyan(int wait) {
  for (int i = 0; i <= 255; i++) {
    strip.fill(strip.Color(0, i, 255));
    strip.show();
    delay(wait);
  }
  strip.clear();
  strip.show();
}
