/*
2023/10/05

Lチカ実装
*/
#include <Arduino.h>
#include <unity.h>

void setup() {
    Serial.begin(9600);
    pinMode( 13, OUTPUT );
}
void loop() {
    digitalWrite( 13, HIGH );
    Serial.println("HIGH");
    delay(100);
    digitalWrite( 13, LOW );
    Serial.println("LOW");
    delay(200);
}
