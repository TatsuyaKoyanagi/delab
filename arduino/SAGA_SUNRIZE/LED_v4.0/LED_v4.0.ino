#include <Adafruit_NeoPixel.h>

#define PIN1 6
#define PIN2 7
#define PIN3 8
#define PIN4 9
#define PIN5 10
#define PIN6 11

#define SummerButtunPin 19
#define WinterButtunPin 20

#define NUMPIXELS 60
#define NumStrips 6

int season = 0;

//Aパート
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_RGB + NEO_KHZ800);
//Bパート
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_RGB + NEO_KHZ800);
//Cパート
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_RGB + NEO_KHZ800);
//Dパート
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUMPIXELS, PIN4, NEO_RGB + NEO_KHZ800);
//Eパート
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUMPIXELS, PIN5, NEO_RGB + NEO_KHZ800);
//Fパート
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(NUMPIXELS, PIN6, NEO_RGB + NEO_KHZ800);

/*
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(NUMPIXELS, PIN7, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(NUMPIXELS, PIN8, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(NUMPIXELS, PIN9, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(NUMPIXELS, PIN10, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_RGB + NEO_KHZ800);
*/

int pins[NumStrips] = { PIN1, PIN2, PIN3, PIN4, PIN5, PIN6};
Adafruit_NeoPixel strips[NumStrips];

void setup() {
  pinMode(SummerButtunPin, INPUT_PULLUP);
  pinMode(WinterButtunPin, INPUT_PULLUP);
  for (int i = 0; i < NumStrips; i++) {
    strips[i] = Adafruit_NeoPixel(NUMPIXELS, pins[i], NEO_RGB + NEO_KHZ800);
    strips[i].begin();
  }
}

void loop() {
}

// Function to update a single strip
void updateStrip(Adafruit_NeoPixel &strip, uint16_t i) {
  strip.fill(strip.Color(255, 0, 0), i, 3);
  strip.fill(strip.Color(0, 0, 0), 0, i);
  strip.show();
  delay(10);  // Delay for the fill effect
}

//アリーナ内の照明
void ArenaLED() {
  strip6.fill(strip6.Color(0, 0, 0));
  strip6.show();
}
