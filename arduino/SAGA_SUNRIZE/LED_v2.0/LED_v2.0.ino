#include <Adafruit_NeoPixel.h>

#define PIN            6  // Neopixelのデータピン
#define NUMPIXELS      60  // Neopixelの総LED数

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int redChunkStart = 0;  // 赤色の塊の始まりのLED番号

void setup() {
  strip.begin();
  strip.show();  // 初期化時に全てのLEDをオフにする
}

void loop() {
  setStaticColors();    // 静的な色を設定
  moveRedChunk();       // 赤色の塊を移動
  gradientOrangeToBlue(); // オレンジから青へのグラデーションを設定
  strip.show();  // LEDの状態を更新
  delay(50);     // 少し遅延を入れる
}  

void setStaticColors() {
  // LED番号1から28までオレンジ色に設定
  for (int i = 0; i < 28; i++) {
    strip.setPixelColor(i, 255, 165, 0);  // オレンジ
  }

  // LED番号33から60まで青色に設定
  for (int i = 32; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, 0, 0, 255);  // 青色
  }
}

void moveRedChunk() {
  for (int i = redChunkStart; i < redChunkStart + 5 && i < 60; i++) {
    if(redChunkStart<30){
      strip.setPixelColor(i, 255, 0, 0);  // 赤色の塊
    }else{
      strip.setPixelColor(i, 0, 255, 255);  // 赤色の塊
    }
  }
  redChunkStart++;  // 赤色の塊の始まりを1つずらす
  if (redChunkStart > 60) {  // 赤色の塊がLED番号28を超えたら
    redChunkStart = 0;       // 赤色の塊の始まりを0に戻す
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
