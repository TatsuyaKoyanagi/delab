#include <Adafruit_NeoPixel.h>

#define PIN            6  // Neopixelのデータピン
#define NUMPIXELS      60  // Neopixelの総LED数

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int redStart = 0;  // 赤色の光の塊の始まりのLED番号
int redEnd = 2;    // 赤色の光の塊の終わりのLED番号
int blueStart = 30;  // 青色の光の塊の始まりのLED番号
int blueEnd = 32;    // 青色の光の塊の終わりのLED番号

void setup() {
  strip.begin();
  strip.show();  // 初期化時に全てのLEDをオフにする
}

void loop() {
  flowRedToOrange();    // LED番号1から25までを赤色の光の塊を流す
  gradientOrangeToCyan(); // LED番号26から30までをオレンジから水色のグラデーションにする
  flowBlueToCyan();     // LED番号31から60までを青色の光の塊を流す
}  

void flowRedToOrange() {
  for (int i = 0; i < 25; i++) {
    if (i >= redStart && i <= redEnd) {
      strip.setPixelColor(i, 255, 0, 0);  // 赤色の光の塊
    } else {
      strip.setPixelColor(i, 255, 165, 0);  // オレンジ
    }
  }

  strip.show();
  delay(50);

  redStart++;  // 赤色の光の塊の始まりを1つずらす
  redEnd++;    // 赤色の光の塊の終わりを1つずらす

  if (redEnd > 24) {  // 赤色の光の塊がLED番号25を超えたら
    redStart = 0;     // 赤色の光の塊の始まりを0に戻す
    redEnd = 2;       // 赤色の光の塊の終わりを4に戻す
  }
}

void gradientOrangeToCyan() {
  for (int i = 25; i < 30; i++) {
    int red = map(i, 25, 30, 255, 0);
    int green = map(i, 25, 30, 165, 255);
    int blue = map(i, 25, 30, 0, 255);
    strip.setPixelColor(i, red, green, blue);  // グラデーション
  }

  strip.show();
  delay(50);
}

void flowBlueToCyan() {
  for (int i = 30; i < 60; i++) {
    if (i >= blueStart && i <= blueEnd) {
      strip.setPixelColor(i, 0, 0, 255);  // 青色の光の塊
    } else {
      strip.setPixelColor(i, 0, 255, 255);  // 水色
    }
  }

  strip.show();
  delay(50);

  blueStart++;  // 青色の光の塊の始まりを1つずらす
  blueEnd++;    // 青色の光の塊の終わりを1つずらす

  if (blueEnd > 59) {  // 青色の光の塊がLED番号60を超えたら
    blueStart = 30;    // 青色の光の塊の始まりを30に戻す
    blueEnd = 32;      // 青色の光の塊の終わりを34に戻す
  }
}  