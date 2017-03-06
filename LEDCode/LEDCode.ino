#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Wire.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);
enum ColorState { inactive, autonomous, tank, mech, depositingGear, shooting, climbing, test};
#define RED 0x00ff0000
#define GREEN 0x0000ff00
#define BLUE 0x000000ff
ColorState cs = shooting;

int brightness = 50;
bool goingDown = true;

uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t magenta = strip.Color(255, 0, 255);
uint32_t purple = strip.Color(128, 0, 128);
uint32_t orange = strip.Color(255, 165, 0);
uint32_t allianceColor = blue;
uint32_t white = strip.Color(255, 255, 255);


int start = 0;
uint32_t off = strip.Color(0, 0, 0);
int numPixels = 120;
int mod = numPixels / 2;
bool even = false;

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  strip.begin();
  strip.show();
  strip.setBrightness(25);
  //  for (int i = 0; i < numPixels; i++) {
  //    strip.setPixelColor(i, blue);
  //  }
  //  strip.show();
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
        delay(10);
      }
      for (int i = 0; i < numPixels; i++) {
        if (cs != autonomous) {
          break;
        }
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

      break;
    case tank:

      for (int i = 0; i < numPixels ; i++) {
        if (cs != tank) {
          break;
        }
        strip.setPixelColor(i, allianceColor);//colors[random(0, 5)]);

        strip.setPixelColor(numPixels - 1 - i, yellow);//colors[random(0, 5)]);
        if (i > 9) {
          strip.setPixelColor(i - 10, strip.Color(0, 0, 0));
        }
        if (i < numPixels) {
          strip.setPixelColor(numPixels - 1 - i + 10, strip.Color(0, 0, 0));
        }
        strip.show();
        delay(5);
      }
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
      if (cs != depositingGear) {
        break;
      }
      strip.show();
      start += 1;
      delay(50);
      break;

    case shooting:
      strip.show();
      //      for (int i = 0; i < numPixels / 2; i ++) {
      //        if(cs != shooting){
      //          break;
      //        }
      ////        strip.setPixelColor(i, yellow);
      ////        strip.setPixelColor(i - 10, off);
      ////
      ////        strip.setPixelColor(i + 50, yellow);
      ////        strip.setPixelColor(i + 50 - 10, off);
      ////
      ////        strip.setPixelColor(i + 100, yellow);
      ////        strip.setPixelColor(i + 100 - 10, off);
      //        strip.setPixelColor(i, yellow);
      //
      for (int i = (int)(numPixels / 2) + 1; i < numPixels + 10; i++) {
        strip.setPixelColor(i, yellow);
        //if (i -  (numPixels / 2) > 10) {
         strip.setPixelColor(i - 10, off);
        //}
        strip.show();
        int temp = i;             
        i = numPixels - i;
        strip.setPixelColor(i, yellow);
        strip.setPixelColor(i + 10, off);
        i = temp;
        delay(1);
      }
/*
      for (int i = (int)(numPixels / 2); i > 0; i--) {
        strip.setPixelColor(i, yellow);
        if (i < (numPixels / 2) - 10) {
          strip.setPixelColor(i + 10, off);
        }
      }*/
    
//      delay(50);
      break;



    case mech:
      for (int i = 0; i < numPixels; i++) {
        if (cs != mech) {
          break;
        }
        if (i % mod == 0) {
          strip.setPixelColor(i, allianceColor);
        } else {
          strip.setPixelColor(i, off);
        }
      }
      if (!goingDown) {
        mod++;
      } else {
        mod--;
      }
      if (mod > 4) {
        mod = 4;
        goingDown = true;
      } else if (mod < 1) {
        mod = 1;
        goingDown = false;
      }

      strip.show();
      delay(60);
      break;
    case climbing:
      for (int i = 0; i < numPixels; i++) {
        strip.setPixelColor(i, random(0, 256), random(0, 256), random(0, 256));
      }
      strip.show();
      break;
  }
}

void receiveEvent(int howMany) {

  //  String receiveStr = "";
  //  while ( Wire.available() > 0 ) {
  //    char n = (char)Wire.read();
  //    if (((int)n) > ((int)(' ')))
  //      receiveStr += n;
  //  }
  int receiveInt = 6;
  //  while (Wire.available() > 0){
  //    int n = (int)Wire.read();
  //    recieveInt += n;
  //  }
  receiveInt = (int)Wire.read();
  if (receiveInt == 0) {
    cs = autonomous;
    allianceColor = blue;
  } else if (receiveInt == 1) {
    cs = autonomous;
    allianceColor = red;
  } else if (receiveInt == 2) {
    cs = tank;
    allianceColor = blue;
  } else if (receiveInt == 3) {
    cs = tank;
    allianceColor = red;
  } else if (receiveInt == 4) {
    cs = mech;
    allianceColor = blue;
  } else if (receiveInt == 5) {
    cs = mech;
    allianceColor = red;
  } else if (receiveInt == 6) {
    cs = inactive;
  } else if (receiveInt == 7) {
    cs = depositingGear;
  } else if (receiveInt == 8) {
    cs = shooting;
  } else if (receiveInt == 9) {
    cs = climbing;
  } else if (receiveInt == 10) {
    cs = test;
    for (int i = 0; i < numPixels; i++) {
      strip.setPixelColor(i, red);
    }
  } else if (receiveInt == 11) {
    cs = test;
    for (int i = 0; i < numPixels; i++) {
      strip.setPixelColor(i, yellow);
    }
  } else if (receiveInt == 12) {
    cs = test;
    for (int i = 0; i < numPixels; i++) {
      strip.setPixelColor(i, green);
    }
  } else if (receiveInt == 13) {
    cs = test;
    for (int i = 0; i < numPixels; i++) {
      strip.setPixelColor(i, blue);
    }
  } else if (receiveInt == 14) {
    cs = test;
    for (int i = 0; i < numPixels; i++) {
      strip.setPixelColor(i, purple);
    }
  }
  strip.show();
}
