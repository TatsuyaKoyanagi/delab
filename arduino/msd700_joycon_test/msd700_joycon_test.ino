#include <Arduino.h>

#define ES_BUTTON 2  //緊急停止ボタン
#define ES_LED 7     //ボタンLED

volatile bool Stop = false;  // 割り込みからアクセスされる変数はvolatileとして宣言

const int INPUT_PINS[] = { A0, A1, A3, A4 };  //ly,lx,ry,rx,lz,rz
const int NUM_PINS = sizeof(INPUT_PINS) / sizeof(INPUT_PINS[0]);

const int MAX = 1.00;  //1023
const int MID = 512;
const int MIN = -1.00;  //0

float INPUT_RES[NUM_PINS];
int OFFSET_RES[NUM_PINS];


volatile int flag = 0;

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
  if (!Stop) {
    if (flag == 1) {
      pause();
    } else {
      read_resister();
      print_resister();
      //send_resister();
      Serial.print(0);
      Serial.print(",");
      Serial.print(1000);
      Serial.print(":");
    }
  } else {
    exit;
    while (1) {
    }
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
    digitalWrite(ES_LED, LOW);  // LEDを点灯
  } else {  // ボタンが放された場合
    digitalWrite(ES_LED, HIGH);  // LEDを消灯
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

void print_resister() {
  for (int i = 0; i < NUM_PINS; i++) {
    Serial.print(INPUT_RES[i]);
    if (i != NUM_PINS - 1) {
      Serial.print(",");
    }
  }
  Serial.println();
}

void send_resister() {
  String resStr = "";
  for (int i = 0; i < NUM_PINS; i++) {
    resStr += String(INPUT_RES[i]);
    if (i != NUM_PINS - 1) {
      resStr += ",";
    }
  }
  Serial.println(resStr);
}

void pause() {
  delay(1);
}
