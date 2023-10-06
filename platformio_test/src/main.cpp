/*
2023/10/04 install
*/
#include <Arduino.h>

void Ltika();
void serial_test();
int i=0;
int root=2;

void setup() {
    Serial.begin(9600);
    pinMode( 13, OUTPUT );
}

void loop() {
  if(root==1){
    Ltika();
  }else if(root ==2){
    serial_test();
  }
}

void Ltika(){
  digitalWrite( 13, HIGH );
  Serial.println("HIGH");
  delay(100);
  digitalWrite( 13, LOW );
  Serial.println("LOW");
  delay(200);
}

void serial_test(){
  Serial.println(i);
  delay(100);
  i++;
  if(i==100){
    i=0;
  }
}
