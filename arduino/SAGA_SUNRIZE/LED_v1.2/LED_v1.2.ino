#include <Adafruit_NeoPixel.h>

#define PIN 6         // Neopixelのデータピン
#define NUMPIXELS 60  // Neopixelの総LED数

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int redChunkPosition = 0;  // 赤色の塊の位置

void setup() {
  strip.begin();
  strip.show();  // 初期化時に全てのLEDをオフにする
}

void loop() {
  setStaticColors();           // 特定のセグメントで静的な色を設定
  moveRedChunkWithInterval();  // 赤色の塊を移動
  gradientOrangeToBlue();      // LED番号29から32までをオレンジから青のグラデーションにする
  strip.show();                // LEDの状態を更新
  delay(50);                   // 少し遅延を入れる
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

void moveRedChunkWithInterval() {
  int redChunkSize = 2;                     // 赤色の塊のサイズ
  int interval = 3;                         // 間隔のサイズ
  int totalSize = redChunkSize + interval;  // 塊と間隔の合計サイズ

  for (int i = redChunkPosition; i < redChunkPosition + redChunkSize && i < 60; i++) {
    if (redChunkPosition < 30) {
      strip.setPixelColor(i, 255, 0, 0);  // 赤色の塊
    } else {
      strip.setPixelColor(i, 0, 255, 255);  // 赤色の塊
    }
  }

  redChunkPosition++;  // 赤色の塊の位置を1つずらす

  if (redChunkPosition > 60 - totalSize) {  // 赤色の塊が範囲の最後を超えたら
    redChunkPosition = 0;                   // 赤色の塊の位置を0にリセット
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
