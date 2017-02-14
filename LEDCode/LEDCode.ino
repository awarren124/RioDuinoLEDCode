#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Wire.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);
enum ColorState { inactive, autonomous, tank, mech, depositingGear, shooting};
#define RED 0x00ff0000
#define GREEN 0x0000ff00
#define BLUE 0x000000ff
ColorState cs = inactive;
int mod = 0;

uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t magenta = strip.Color(255, 0, 255);
uint32_t purple = strip.Color(128, 0, 128);
uint32_t orange = strip.Color(255, 165, 0);
uint32_t allianceColor = red;
int start = 0;
uint32_t off = strip.Color(0, 0, 0);
int numPixels = 120;
bool even = false;

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  strip.begin();
  strip.show();
  strip.setBrightness(50);
  cs = mech;
}

void loop() {

  switch (cs) {
    case inactive:
      for (int i = 0; i < numPixels; i++) {
        if (even) {
          if (i % 2 == 0) {
            strip.setPixelColor(i, green);
          }
          else {
            strip.setPixelColor(i, yellow);
          }
        } else {
          if (i % 2 == 0) {
            strip.setPixelColor(i, yellow);
          }
          else {
            strip.setPixelColor(i, green);
          }
        }
      }
      even = !even;
      strip.show();
      delay(1000);
      break;
    case autonomous:
      for (int i = 0; i < numPixels; i++) {
        strip.setPixelColor(i, off);
        strip.show();
      }
      for (int i = 0; i < numPixels; i++) {
        if (i % 2 == 0) {
          strip.setPixelColor(i, yellow);
          strip.show();
          delay(10);
        }
        else {
          strip.setPixelColor(i, allianceColor);
          strip.show();
          delay(10);
        }
      }
      delay(1000);
      break;
    case tank:
      for (int i = 0; i < numPixels; i++) {
        strip.setPixelColor(i, off);
        strip.show();
      }
      for (int i = 0; i < numPixels ; i++) {
        strip.setPixelColor(i, allianceColor);//colors[random(0, 5)]);
        strip.setPixelColor(numPixels - i, yellow);//colors[random(0, 5)]);
        if (i > 10) {
          strip.setPixelColor(i - 10, strip.Color(0, 0, 0));
        }
        if (i < numPixels - 10) {
          strip.setPixelColor(numPixels - i + 10, strip.Color(0, 0, 0));
        }
        strip.show();
        delay(10);
      }
      strip.show();
      delay(10);
      break;
    case depositingGear:



      for (int i = start % 7; i < numPixels; i += 7) {
        strip.setPixelColor(i, red);
      }
      for (int i = (start + 1) % 7; i < numPixels; i += 7) {
        strip.setPixelColor(i, orange);
      }
      for (int i = (start + 2) % 7; i < numPixels; i += 7) {
        strip.setPixelColor(i, yellow);
      }
      for (int i = (start + 3) % 7; i < numPixels; i += 7) {
        strip.setPixelColor(i, green);
      }
      for (int i = (start + 4) % 7; i < numPixels; i += 7) {
        strip.setPixelColor(i, blue);
      }
      for (int i = (start + 5) % 7; i < numPixels; i += 7) {
        strip.setPixelColor(i, magenta);
      }
      for (int i = (start + 6) % 7; i < numPixels; i += 7) {
        strip.setPixelColor(i, purple);
      }
      strip.show();
      start += 1;
      delay(50);
      break;

    case shooting:
      strip.show();
      for (int i = 0; i < 60; i ++) {
        strip.setPixelColor(i, yellow);
        strip.setPixelColor(i - 10, off);

        strip.setPixelColor(i + 50, yellow);
        strip.setPixelColor(i + 50 - 10, off);

        strip.setPixelColor(i + 100, yellow);
        strip.setPixelColor(i + 100 - 10, off);
        strip.show();
      }
      break;

    case mech:
      /*if (allianceColor == red) {
        for (int i = 0; i < numPixels; i++) {
          if (i < 60) {
            strip.setPixelColor(i, allianceColor);
          }
          else {
            strip.setPixelColor(i, blue);
          }
        }
        strip.show();
        for (int g = 0; g < 10; g++) {
          for (int i = 1; i < 11; i++) {
            strip.setPixelColor(59 + i, allianceColor);
            strip.show();
            delay(5);
          }
          for (int i = 1; i < 21; i++) {
            strip.setPixelColor(69 - i, blue);
            strip.show();
            delay(5);
          }
          for (int i = 1; i < 11; i++) {
            strip.setPixelColor(59 + i, allianceColor);
            strip.show();
            delay(5);
          }
        }
        for (int i = 0; i < numPixels; i++) {
          strip.setPixelColor(i, allianceColor);
          strip.show();
          delay(100);
        }
      }
      else {
        for (int i = 0; i < numPixels; i++) {
          if (i < 60) {
            strip.setPixelColor(i, allianceColor);
          }
          else {
            strip.setPixelColor(i, red);
          }
        }
        strip.show();
        for (int g = 0; g < 10; g++) {
          for (int i = 1; i < 11; i++) {
            strip.setPixelColor(59 + i, allianceColor);
            strip.show();
            delay(5);
          }
          for (int i = 1; i < 21; i++) {
            strip.setPixelColor(69 - i, red);
            strip.show();
            delay(5);
          }
          for (int i = 1; i < 11; i++) {
            strip.setPixelColor(59 + i, allianceColor);
            strip.show();
            delay(5);
          }
        }
        for (int i = 0; i < numPixels; i++) {
          strip.setPixelColor(i, allianceColor);
          strip.show();
          delay(100);
        }
      }
      break;*/
      if (allianceColor == red) {
        for (int i = 0; i < numPixels; i++) {
          if (i < 60) {
            strip.setPixelColor(i, allianceColor);
          }
          else{
            strip.setPixelColor(i, blue);
          }
        }
          strip.show();
          for(int g=0; g<10; g++){
            for(int i=1; i<50; i++){
             strip.setPixelColor(99-i,blue);
             strip.show();
             delay(15);
            }
            for(int i=1; i<50; i++){
              strip.setPixelColor(19+i,allianceColor);
              strip.show();
              delay(15);
            }

          }
          for(int i=0; i < numPixels; i++){
            strip.setPixelColor(i,allianceColor);
            strip.show();
            delay(15);
          }
      }
      else {
        for (int i = 0; i < numPixels; i++) {
          if (i < 60) {
            strip.setPixelColor(i, allianceColor);
          }
          else{
            strip.setPixelColor(i, red);
          }
        }
          strip.show();
          for(int g=0; g<10; g++){
            for(int i=1; i<50; i++){
             strip.setPixelColor(99-i,red);
             strip.show();
             delay(15);
            }
            for(int i=1; i<50; i++){
              strip.setPixelColor(19+i,allianceColor);
              strip.show();
              delay(15);
            }

          }
          for(int i=0; i < numPixels; i++){
            strip.setPixelColor(i,allianceColor);
            strip.show();
            delay(15);
          }
        }
      
   
          
     
      break;
  }
}

void receiveEvent(int howMany) {

  String receiveStr = "";
  while ( Wire.available() > 0 ) {
    char n = (char)Wire.read();
    if (((int)n) > ((int)(' ')))
      receiveStr += n;
  }
  if (receiveStr == "autoBlue") {
    cs = autonomous;
    allianceColor = blue;
  } else if (receiveStr == "auto") {
    cs = autonomous;
    allianceColor = red;
  } else if (receiveStr == "tankBlue") {
    cs = tank;
    allianceColor = blue;
  } else if (receiveStr == "tankRed") {
    cs = tank;
    allianceColor = red;
  } else if (receiveStr == "mechBlue") {
    cs = mech;
    allianceColor = blue;
  } else if (receiveStr == "mechRed") {
    cs = mech;
    allianceColor = red;
  } else if (receiveStr == "disableInit") {
    cs = inactive;
  } else if (receiveStr == "depositingGear") {
    cs = depositingGear;
  } else if (receiveStr == "shooting") {
    cs = shooting;
  }
}
