#include <Adafruit_NeoPixel.h>

#define PIN            6  // Neopixelのデータピン
#define NUMPIXELS      60  // Neopixelの総LED数

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int redStart1 = 0;  // 赤色の光の塊1の始まりのLED番号
int redEnd1 = 2;    // 赤色の光の塊1の終わりのLED番号
int redStart2 = 5;  // 赤色の光の塊2の始まりのLED番号
int redEnd2 = 7;    // 赤色の光の塊2の終わりのLED番号
int redStart3 = 10;
int redEnd3 = 12;  
int redStart4 = 15;
int redEnd4 = 17; 
int blueStart1 = 30;  // 青色の光の塊1の始まりのLED番号
int blueEnd1 = 32;    // 青色の光の塊1の終わりのLED番号
int blueStart2 = 35;  // 青色の光の塊2の始まりのLED番号
int blueEnd2 = 37;    // 青色の光の塊2の終わりのLED番号
int blueStart3 = 40;
int blueEnd3 = 42;
int blueStart4 = 45;
int blueEnd4 = 47;


void setup() {
  strip.begin();
  strip.show();  // 初期化時に全てのLEDをオフにする
}

void loop() {
  flowRedToOrange();    // LED番号1から25までを赤色の光の塊を流す
  gradientOrangeToCyan(); // LED番号26から30までをオレンジから水色のグラデーションにする
  flowBlueToCyan();     // LED番号31から60までを青色の光の塊を流す
}  // ここに`}`を追加して、`void loop()`という関数のブロックを終わらせる

void flowRedToOrange() {

  for (int i = 0; i < 25; i++) {
    if ((i >= redStart1 && i <= redEnd1) || (i >= redStart2 && i <= redEnd2)|| (i >= redStart3 && i <= redEnd3)|| (i >= redStart4 && i <= redEnd4)) {  // LED番号iが赤色の光の塊1か2の範囲にあるとき
      int red = 255;
      int green = map(i, min(redStart1, redStart2), max(redEnd1, redEnd2), 0, 165);  // 緑の色成分を変化させる
      int blue = 0;
      strip.setPixelColor(i, red, green, blue);  // 赤色の光の塊
    } else {
      strip.setPixelColor(i, 255, 165, 0);  // オレンジ
    }
  }

  strip.show();
  delay(50);

  redStart1++;  // 赤色の光の塊1の始まりを1つずらす
  redEnd1++;    // 赤色の光の塊1の終わりを1つずらす
  redStart2++;  // 赤色の光の塊2の始まりを1つずらす
  redEnd2++;    // 赤色の光の塊2の終わりを1つずらす
  redStart3++;  // 赤色の光の塊3の始まりを1つずらす
  redEnd3++;    // 赤色の光の塊3の終わりを1つずらす
  redStart4++;  // 赤色の光の塊4の始まりを1つずらす
  redEnd4++;    // 赤色の光の塊4の終わりを1つずらす

  if (redEnd1 > 24 || redEnd2 > 24 || redEnd3 > 24 || redEnd4 > 24) {  // 赤色の光の塊1か2か３か４がLED番号25を超えたら
    redStart1 = 0;     // 赤色の光の塊1の始まりを0に戻す
    redEnd1 = 2;       // 赤色の光の塊1の終わりを4に戻す
    redStart2 = 5;    // 赤色の光の塊2の始まりを12に戻す
    redEnd2 = 7;      // 赤色の光の塊2の終わりを16に戻す
    redStart3 = 10;
    redEnd3 = 12;  
    redStart4 = 15;
    redEnd4 = 17; 
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
    if ((i >= blueStart1 && i <= blueEnd1) || (i >= blueStart2 && i <= blueEnd2)|| (i >= blueStart3 && i <= blueEnd3)|| (i >= blueStart4 && i <= blueEnd4)) {  // LED番号iが青色の光の塊1か2か３か４の範囲にあるとき
      int red = 0;
      int green = map(i, min(blueStart1, blueStart2), max(blueEnd1, blueEnd2), 0, 255);  // 緑の色成分を変化させる
      int blue = 255;
      strip.setPixelColor(i, red, green, blue);  // 青色の光の塊
    } else {
      strip.setPixelColor(i, 0, 255, 255);  // 水色
    }
  }

  strip.show();
  delay(50);

  blueStart1++;  // 青色の光の塊1の始まりを1つずらす
  blueEnd1++;    // 青色の光の塊1の終わりを1つずらす
  blueStart2++;  // 青色の光の塊2の始まりを1つずらす
  blueEnd2++;    // 青色の光の塊2の終わりを1つずらす
  blueStart3++;  // 青色の光の塊1の始まりを1つずらす
  blueEnd3++;    // 青色の光の塊1の終わりを1つずらす
  blueStart4++;  // 青色の光の塊2の始まりを1つずらす
  blueEnd4++;    // 青色の光の塊2の終わりを1つずらす

  if (blueEnd1 > 59 || blueEnd2 > 59|| blueEnd3 > 59|| blueEnd4 > 59) {  // 青色の光の塊1か2がLED番号60を超えたら
    blueStart1 = 30;  // 青色の光の塊1の始まりのLED番号
    blueEnd1 = 32;    // 青色の光の塊1の終わりのLED番号
    blueStart2 = 35;  // 青色の光の塊2の始まりのLED番号
    blueEnd2 = 37;    // 青色の光の塊2の終わりのLED番号
    blueStart3 = 40;
    blueEnd3 = 42;
    blueStart4 = 45;
    blueEnd4 = 47;
  }
}