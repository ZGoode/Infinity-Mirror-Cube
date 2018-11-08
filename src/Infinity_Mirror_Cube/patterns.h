#include <Adafruit_NeoPixel.h>

#define totalPixels 60
const int perEdge = totalPixels / 12;
#define PIN 5
#define PIN1 6
#define PIN2 7
#define PIN3 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel((totalPixels), PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel((totalPixels), PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel((totalPixels), PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel((totalPixels), PIN3, NEO_GRB + NEO_KHZ800);

void organizeArray();
void initializePixels();
void rainbowCycle();
uint32_t Wheel(byte WheelPos);

int arbitraryNumber = 256;

uint32_t cube[totalPixels];

int previousMillis0 = 0;
int previousMillis1 = 0;

int rainbowCycleLoop0 = 0;
int rainbowCycleLoop1 = 0;

void organizeArray() {
  for (int i = 0; i < totalPixels; i++) {
    //write code once order of wiring is written
  }
  pixels1.show();
  pixels2.show();
  pixels3.show();
}

void initializePixels() {
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  pixels1.show();
  pixels2.show();
  pixels3.show();
  //  pixels.setBrightness(50);
}

void rainbowCycle0() {
  if (rainbowCycleLoop0 < 256) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis0 > 1) {
      previousMillis0 = currentMillis;
      for (int i = 0; i < totalPixels; i++) {
        cube[i] = Wheel(((i * 256 / arbitraryNumber) + rainbowCycleLoop0) & 255);
        //pixels.setPixelColor(i, Wheel(((i * 256 / arbitraryNumber) + rainbowCycleLoop) & 255));
      }
      organizeArray();
    }
    rainbowCycleLoop0++;
  } else if (rainbowCycleLoop0 >= 256) {
    rainbowCycleLoop0 = 0;
  }
}

void rainbowCycle1() {
  boolean isOdd;
  uint32_t edgeHalfTemp[((perEdge / 2) + 1)];
  if (perEdge % 2 == 1) {
    isOdd = true;
  } else if (perEdge % 2 == 0) {
    isOdd = false;
  }
  if (rainbowCycleLoop1 < 256) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis1 > 1) {
      previousMillis0 = currentMillis;
      for (int i = 0; i < (perEdge / 2); i++) {
        edgeHalfTemp[i] = Wheel(((i * 256 / arbitraryNumber) + rainbowCycleLoop1) & 255);
      }
      uint32_t tempEdge[perEdge];
      int tempCount;
      if (isOdd == true) {
        int tempCount = (perEdge / 2) + 1;
      } else if (isOdd == false) {
        tempCount = perEdge / 2;
      }
      for (int j = 0; j < tempCount; j++) {
        tempEdge[((perEdge / 2) + j)] = edgeHalfTemp[j];
        tempEdge[((perEdge / 2) - j)] = edgeHalfTemp[j];
      }
      for (int k = 0; k < pixels1.numPixels(); k++) {
        for (int l = 0; l < (pixels1.numPixels() / perEdge); l++) {
          pixels1.setPixelColor(((perEdge * l) + k), tempEdge[k]);
        }
      }
      for (int m = 0; m < pixels2.numPixels(); m++) {
        for (int n = 0; n < (pixels2.numPixels() / perEdge); n++) {
          pixels1.setPixelColor(((perEdge * n) + m), tempEdge[m]);
        }
      }
      for (int o = 0; o < pixels3.numPixels(); o++) {
        for (int p = 0; p < (pixels3.numPixels() / perEdge); p++) {
          pixels1.setPixelColor(((perEdge * p) + o), tempEdge[o]);
        }
      }
      pixels1.show();
      pixels2.show();
      pixels3.show();
    }
    rainbowCycleLoop1++;
  } else if (rainbowCycleLoop1 >= 256) {
    rainbowCycleLoop1 = 0;
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
