/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

#include <string.h>

#include "Parola_Fonts_data.h"
#include "misakiUTF16FontData.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN 52   // or SCK
#define DATA_PIN 50  // or MOSI
#define CS_PIN 53    // or SS

void setting_value();
void print_at_display();

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

Adafruit_BME280 bme;  // I2C
unsigned long delayTime;

void setup() {
  P.displayReset();
  P.begin();
  P.setFont(fontKatakana);  //アルファベットの時はコメントアウト
                            //P.print("Hello, world!");
  Serial.begin(9600);
  while (!Serial)
    ;  // time to get serial running
  Serial.println(F("BME280 test"));

  unsigned status;

  // default settings
  status = bme.begin(0x76);
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}

int currentState = 4;
String temp = "";
String pres = "";
String humi = "";

String abc = "aiueo";

void loop() {
  setting_value();
  print_at_display();
  printValues();
  delay(delayTime);
}

void print_at_display() {
  if (P.displayAnimate()) {
    switch (currentState) {
      case 1:
        P.setFont(fontArabic);
        P.displayText("SAGA U deLab", PA_LEFT, 75, 1000, PA_SCROLL_LEFT, PA_SCROLL_DOWN);
        delay(100);  // 1秒待つ (あるいは他の適切な待ち時間)
        currentState = 2;
        break;

      case 2:
        P.setFont(fontKatakana);
        P.displayText("\xbb\xb6\xde\xc0\xde\xb2\xc3\xde\xd7\xce\xde", PA_LEFT, 75, 1000, PA_SCROLL_LEFT, PA_SCROLL_DOWN);
        delay(100);  // 1秒待つ (あるいは他の適切な待ち時間)
        currentState = 3;
        break;

      case 3:
        P.setFont(fontArabic);
        P.displayText(abc.c_str(), PA_LEFT, 75, 500, PA_SCROLL_LEFT, PA_SCROLL_DOWN);
        delay(100);  // 1秒待つ (あるいは他の適切な待ち時間)
        currentState = 1;
        break;

      case 4:
        P.setFont(fontArabic);
        //P.setFont(fontArabic);
        P.displayText(temp.c_str(), PA_LEFT, 10, 100, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        //delay(100);  // 1秒待つ (あるいは他の適切な待ち時間)
        currentState = 5;
        break;

      case 5:
        P.setFont(fontArabic);
        P.displayText(pres.c_str(), PA_LEFT, 10, 100, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        //delay(100);  // 1秒待つ (あるいは他の適切な待ち時間)
        currentState = 6;
        break;

      case 6:

        P.displayText(humi.c_str(), PA_LEFT, 10, 100, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        //delay(100);  // 1秒待つ (あるいは他の適切な待ち時間)
        currentState = 4;
        break;
    }
  }
}

void setting_value() {
  temp = String(bme.readTemperature(), 1);
  temp += " °C";  // 1桁の小数点で表示
  pres = String(bme.readPressure() / 100.0F, 1);
  pres += " hPa";  // hPaに変換して、1桁の小数点で表示
  humi = String(bme.readHumidity(), 1);
  humi += " %";  // 1桁の小数点で表示
}


void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}
