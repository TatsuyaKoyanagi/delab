#include <Arduino.h>

int i=0;

void setUp(void) {
// set stuff up here
Serial.begin(9600);
}

void tearDown(void) {
// clean stuff up here
Serial.println(i);
i++;
delay(1000);
if(i==10){
    i=0;
}
}