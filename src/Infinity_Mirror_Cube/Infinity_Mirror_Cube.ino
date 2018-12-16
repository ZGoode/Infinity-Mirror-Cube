/*
 *Infinity Mirror Cube 
 *Arduino Pro Micro 16Mhz 5v
 *Pattern 1: Rainbow Randomness #1
 *Pattern 2: Rainbow Randomness #2
 *Pattern 3: Color Chasing
 */

#include "patterns.h"

#define buttonPin 4

int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

int currentPattern = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  initializePixels();
}

void loop() {
  if (currentPattern == 0) {
    rainbowCycle0();
  } else if (currentPattern == 1) {
    rainbowCycle1();
  }
  
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
}
