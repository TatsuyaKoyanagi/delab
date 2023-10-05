/*
2023/10/05
Lチカ実装
*/
#include <Arduino.h>
#include <unity.h>

void setup() {
    pinMode( 13, OUTPUT );
}
void loop() {
    digitalWrite( 13, HIGH );
    delay(100);
    digitalWrite( 13, LOW );
    delay(300);
}
