#include <Adafruit_NeoPixel.h>
#define PIN            6  // NeoPixelデータピン
#define NUM_PIXELS     60  // LEDの数
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show();  // 初期化
}
void loop() {
  // ライトの塊が左から右に流れるアニメーション（赤色）
  theaterChase(strip.Color(255, 0, 0), 50); // 赤色、50msごとに更新
}
// ライトの塊が左から右に流れるアニメーション
void theaterChase(uint32_t color, int wait) {
  for(int j = 0; j < 10; j++) {  // 10回繰り返す（ライトの塊を10個表示）
    for(int i = 0; i < strip.numPixels(); i = i + 5) { // 光の間隔を小さくするために5に変更
      strip.setPixelColor(i + j, color);  // ライトの塊を進める
    }
    strip.show();
    delay(wait);
    colorWipe(strip.Color(255, 80, 0), 0);  // すべてのLEDをオレンジにする
  }
}
// 指定した色がLEDテープを流れるアニメーション
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(wait);
}
//--------------------------------------------------------------------------------------//
#include <Adafruit_NeoPixel.h>
#define PIN            6  // NeoPixelデータピン
#define NUMPIXELS      10 // NeoPixelの数
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
/*----------------------------------*/
#include <Adafruit_NeoPixel.h>
#define PIN            6  // NeoPixelデータピン
#define NUM_PIXELS     60  // LEDの数
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show();  // 初期化
}
void loop() {
  // ライトの塊が左から右に流れるアニメーション（青色）
  theaterChase(strip.Color(0, 0, 255), 50); // 青色、50msごとに更新
}
// ライトの塊が左から右に流れるアニメーション
void theaterChase(uint32_t color, int wait) {
  for(int j = 0; j < 10; j++) {  // 10回繰り返す（ライトの塊を10個表示）
    for(int i = 0; i < strip.numPixels(); i = i + 10) {
      strip.setPixelColor(i + j, color);  // ライトの塊を進める
    }
    strip.show();
    delay(wait);
    colorWipe(strip.Color(173, 216, 240), 0);  // すべてのLEDを水色にする
  }
}
// 指定した色がLEDテープを流れるアニメーション
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(wait);
}

//
上みっつをLED番号1から25,26から35、36から60で動かしたくて
//

#include <Adafruit_NeoPixel.h>
#define PIN            6  // NeoPixelデータピン
#define NUMPIXELS      60 // NeoPixelの数
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show(); // NeoPixelを初期化して消灯状態にする
}
void loop() {
  // 各LED番号によって異なるプログラムを同時に実行
  applyProgram1(); // LED番号1から25までのプログラム
  applyProgram2(); // LED番号26から35までのプログラム
  applyProgram3(); // LED番号36から60までのプログラム
  delay(50); // 各LEDに対するプログラムが実行される時間を設定（適宜調整）
  strip.clear();
  strip.show();
}
// LED番号1から25までのプログラム
void applyProgram1() {
  for (int i = 0; i < 25; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // 赤
  }
}
// LED番号26から35までのプログラム
void applyProgram2() {
  for (int i = 25; i < 35; i++) {
    int blueValue = map(i, 25, 34, 255, 0);
    strip.setPixelColor(i, strip.Color(0, 0, blueValue)); // 青いグラデーション
  }
}
// LED番号36から60までのプログラム
void applyProgram3() {
  for (int i = 35; i < 60; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 255)); // 水色
  }
}