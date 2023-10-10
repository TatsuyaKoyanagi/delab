#include <Arduino.h>
#include <ArduinoJson.h>

#define ES_BUTTON 2  //緊急停止ボタン
#define ES_LED 7     //ボタンLED

volatile bool Stop = false;  // 割り込みからアクセスされる変数はvolatileとして宣言

const int INPUT_PINS[] = { A0, A1, A2, A3 };  //ly,lx,ry,rx,lz,rz
String axis[]={"ly","lx","ry","rx"};
const int NUM_PINS = sizeof(INPUT_PINS) / sizeof(INPUT_PINS[0]);


const int MAX = 1.00;  //1023
const int MID = 512;
const int MIN = -1.00;  //0

float INPUT_RES[NUM_PINS];
int OFFSET_RES[NUM_PINS];


volatile int flag = 0;
volatile int ES_value = 0;


void set_offset();
void serialEvent();
void read_resister();
void print_resister();
void send_resister();
void pause();

void setup() {
  pinMode(ES_LED, OUTPUT);
  pinMode(ES_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ES_BUTTON), toggleLED, CHANGE);  // ボタンの状態が変わるたびにtoggleLED関数を呼び出す
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(INPUT_PINS[i], INPUT);
  }
  Serial.begin(9600);
  set_offset();
}

void loop() {
  if (flag == 1) {
    pause();
  } else {
    read_resister();
    //send_resister();
    send_json();
  }
}

void set_offset() {
  for (int i = 0; i < NUM_PINS; i++) {
    INPUT_RES[i] = analogRead(INPUT_PINS[i]);
  }
  for (int i = 0; i < NUM_PINS; i++) {
    OFFSET_RES[i] = MID - INPUT_RES[i];
  }
}

void toggleLED() {
  if (digitalRead(ES_BUTTON) == LOW) {  // ボタンが押された場合
    digitalWrite(ES_LED, LOW);          // LEDを点灯
    ES_value = 0;
  } else {                       // ボタンが放された場合
    digitalWrite(ES_LED, HIGH);  // LEDを消灯
    ES_value = 1;
  }
}

void serialEvent() {  // シリアルイベント関数
  while (Serial.available()) {
    char receivedChar = Serial.read();
    //offsetのリセット
    if (receivedChar == 'r' || receivedChar == 'R') {
      set_offset();
    }
    //一時停止
    if (receivedChar == 'c' || receivedChar == 'C') {
      if (flag == 1) {
        flag = 0;
        digitalWrite(ES_LED, LOW);
      } else {
        flag = 1;
        digitalWrite(ES_LED, HIGH);
      }
    }
  }
}

void read_resister() {
  for (int i = 0; i < NUM_PINS; i++) {
    //INPUT_RES[i] = analogRead(INPUT_PINS[i]);
    //INPUT_RES[i] = analogRead(INPUT_PINS[i]) + OFFSET_RES[i];
    int rawValue = analogRead(INPUT_PINS[i]);
    int mappedValue = map(rawValue, 0, 1023, -1000, 1000);
    float finalValue = mappedValue / 1000.0;
    INPUT_RES[i] = finalValue;
  }
}

void send_resister() {
  String resStr = "";
  for (int i = 0; i < NUM_PINS; i++) {
    resStr += String(INPUT_RES[i]);
    resStr += ",";
  }
  resStr += String(ES_value);
  Serial.println(resStr);
}

void send_json() {
  StaticJsonDocument<200> doc;  // JSONドキュメントを作成。必要なサイズを指定。
  // JSONデータを追加
  for (int i = 0; i < NUM_PINS; i++) {
    String pinName = axis[i];
    float truncatedValue = static_cast<int>(INPUT_RES[i] * 100) * 0.01f;
    doc[pinName] = truncatedValue;
  }
  doc["button"] = ES_value;
  // JSONデータをシリアル通信で送信
  serializeJson(doc, Serial);
  Serial.println();  // 改行を追加
}

void pause() {
  delay(1);
}
