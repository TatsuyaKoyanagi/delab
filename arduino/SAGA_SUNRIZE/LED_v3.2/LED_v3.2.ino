#include <Adafruit_NeoPixel.h>

#define PIN 6         // Neopixelのデータピン
#define NUMPIXELS 60  // Neopixelの総LED数

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// 最大の光の塊の数
const int maxNumOfBlobs = 10;  // 必要に応じてこの値を調整

// 各塊の開始と終了位置を格納する配列
int redStart[maxNumOfBlobs];
int redEnd[maxNumOfBlobs];

// 光の塊の数と塊間の間隔の変数
int numOfBlobs = 4;           // ここでは光の塊を4つに設定
int spacingBetweenBlobs = 5;  // 各塊の間隔を5LEDに設定

// その他の必要なグローバル変数
int blobSize = 2;  // 各塊の大きさ（LEDの数）



void setup() {
  strip.begin();
  strip.show();  // 初期化時に全てのLEDをオフにする

  // 各塊の開始と終了位置を設定するための配列を初期化
  for (int i = 0; i < numOfBlobs; i++) {
    redStart[i] = i * (blobSize + spacingBetweenBlobs);
    redEnd[i] = redStart[i] + blobSize - 1;
  }
}


void loop() {
  flowRedToOrange();       // LED番号1から25までを赤色の光の塊を流す
  gradientOrangeToCyan();  // LED番号26から30までをオレンジから水色のグラデーションにする
  flowBlueToCyan();        // LED番号31から60までを青色の光の塊を流す
}

void flowRedToOrange() {
  for (int i = 0; i < 25; i++) {
    // 現在のLEDがどの塊にも含まれていない場合はオレンジ色に設定
    bool isBlob = false;
    for (int j = 0; j < numOfBlobs; j++) {
      if (i >= redStart[j] && i <= redEnd[j]) {
        strip.setPixelColor(i, 255, 0, 0);  // 赤色の光の塊
        isBlob = true;
        break;
      }
    }
    if (!isBlob) {
      strip.setPixelColor(i, 255, 80, 0);  // オレンジ
    }
  }
  strip.show();
  delay(50);

  // 各塊を移動
  for (int j = 0; j < numOfBlobs; j++) {
    redStart[j]++;
    redEnd[j]++;
    if (redEnd[j] > 24) {
      redStart[j] = 0;
      redEnd[j] = blobSize - 1;
    }
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
    if ((i >= blueStart1 && i <= blueEnd1) || (i >= blueStart2 && i <= blueEnd2) || (i >= blueStart3 && i <= blueEnd3) || (i >= blueStart4 && i <= blueEnd4) || (i >= blueStart5 && i <= blueEnd5)) {
      int red = 0;
      int green = 0;  // 緑の光の強さを0に設定
      int blue = 255;
      strip.setPixelColor(i, red, green, blue);  // 青色の光の塊
    } else {
      strip.setPixelColor(i, 173, 216, 240);  // 水色
    }
  }

  strip.show();
  delay(50);

  blueStart1++;  // 青色の光の塊1の始まりを1つずらす
  blueEnd1++;    // 青色の光の塊1の終わりを1つずらす
  blueStart2++;  // 青色の光の塊2の始まりを1つずらす
  blueEnd2++;    // 青色の光の塊2の終わりを1つずらす
  blueStart3++;  // 青色の光の塊3の始まりを1つずらす
  blueEnd3++;    // 青色の光の塊3の終わりを1つずらす
  blueStart4++;  // 青色の光の塊4の始まりを1つずらす
  blueEnd4++;    // 青色の光の塊4の終わりを1つずらす
  blueStart5++;  // 青色の光の塊5の始まりを1つずらす
  blueEnd5++;    // 青色の光の塊5の終わりを1つずらす

  if (blueEnd1 > 59 || blueEnd2 > 59 || blueEnd3 > 59 || blueEnd4 > 59 || blueEnd5 > 59) {
    blueStart1 = 30;  // 青色の光の塊1の始まりのLED番号
    blueEnd1 = 31;    // 青色の光の塊1の終わりのLED番号
    blueStart2 = 35;  // 青色の光の塊2の始まりのLED番号
    blueEnd2 = 36;    // 青色の光の塊2の終わりのLED番号
    blueStart3 = 40;
    blueEnd3 = 41;
    blueStart4 = 45;
    blueEnd4 = 46;
    blueStart5 = 50;
    blueEnd5 = 51;
  }
}