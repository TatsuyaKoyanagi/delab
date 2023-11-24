#include <Adafruit_NeoPixel.h>
#define PIN 6           // NeoPixelデータピン
#define NUMPIXELS_1 25  // 1-25の数
#define NUMPIXELS_2 5   // 26-30NeoPixelの数
#define NUMPIXELS_2 30  // 31-60NeoPixelの数

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS_1, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS_2, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIXELS_3, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // NeoPixelを初期化して消灯状態にする
}
void loop() {
  // 各LED番号によって異なるプログラムを同時に実行
  prog_1to25();   // LED番号1から25までのプログラム
  prog_26to35();  // LED番号26から35までのプログラム
  prog_36to60();  // LED番号36から60までのプログラム
  delay(50);      // 各LEDに対するプログラムが実行される時間を設定（適宜調整）
  strip.clear();
  strip.show();
}
// LED番号1から25までのプログラム
void prog_1to25() {
  theaterChase(strip.Color(255, 0, 0), 50);  // 赤色、50msごとに更新
}

// LED番号26から35までのプログラム
void prog_26to35() {
  gradientColorWipe(strip.Color(170, 80, 0), strip.Color(173, 216, 170), 50, 2, 4);
}
// LED番号36から60までのプログラム
void prog_36to60() {
  theaterChase(strip.Color(0, 0, 255), 50);  // 青色、50msごとに更新
}

// グラデーションで指定した範囲のNeopixelを色で埋める関数
void gradientColorWipe(uint32_t colorFrom, uint32_t colorTo, int wait, int start, int end) {
  // 1番は常にオレンジ
  strip.setPixelColor(0, strip.Color(255, 80, 0));
  strip.show();
  delay(wait);
  for (int i = start; i <= end; i++) {
    // グラデーションで色が変化する
    int red = map(i, start, end, (colorFrom >> 16) & 0xFF, (colorTo >> 16) & 0xFF);
    int green = map(i, start, end, (colorFrom >> 8) & 0xFF, (colorTo >> 8) & 0xFF);
    int blue = map(i, start, end, colorFrom & 0xFF, colorTo & 0xFF);
    strip.setPixelColor(i - 1, strip.Color(red, green, blue));
    strip.show();
    delay(wait);
  }
  // 10番は常に水色
  strip.setPixelColor(4, strip.Color(173, 216, 240));
  strip.show();
  delay(wait);
}

// ライトの塊が左から右に流れるアニメーション
void theaterChase(uint32_t color, int wait) {
  for (int j = 0; j < 10; j++) {                         // 10回繰り返す（ライトの塊を10個表示）
    for (int i = 0; i < strip.numPixels(); i = i + 5) {  // 光の間隔を小さくするために5に変更
      strip.setPixelColor(i + j, color);                 // ライトの塊を進める
    }
    strip.show();
    delay(wait);
    colorWipe(strip.Color(255, 80, 0), 0);  // すべてのLEDをオレンジにする
  }
}

// 指定した色がLEDテープを流れるアニメーション
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(wait);
}

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
