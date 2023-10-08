#include <Arduino.h>

const int INPUT_PINS[] = { A0, A1, A2, A3, A4, A5 };
const int NUM_PINS = sizeof(INPUT_PINS) / sizeof(INPUT_PINS[0]);
const int MID = 512;
int INPUT_RES[NUM_PINS];
int OFFSET_RES[NUM_PINS];

volatile int flag = 0;

void set_offset();
void serialEvent();
void read_resister();
void print_resister();
void send_resister();
void pause();

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(INPUT_PINS[i], INPUT);
  }
  Serial.begin(9600);
  set_offset();
}

void loop() {
  if(flag==1){
    pause();
  }else{
  read_resister();
  print_resister();
  //send_resister();
  Serial.print(0);
  Serial.print(",");
  Serial.print(1000);
  Serial.print(":");
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

void serialEvent() {  // シリアルイベント関数
  while (Serial.available()) {
    char receivedChar = Serial.read();
    //offsetのリセット
    if (receivedChar == 'r' || receivedChar == 'R') {
      set_offset();
    }
    //一時停止
    if (receivedChar == 'c' || receivedChar == 'C') {
      if(flag==1){
        flag=0;
      }else{
        flag = 1;
      }
    }
  }
}

void read_resister() {
  for (int i = 0; i < NUM_PINS; i++) {
    INPUT_RES[i] = analogRead(INPUT_PINS[i]) + OFFSET_RES[i];
    //cINPUT_RES[i] = map(INPUT_RES[i], OFFSET_RES[i], 1023 + OFFSET_RES[i], 0, 1023);
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

void pause(){
  delay(1);
}
