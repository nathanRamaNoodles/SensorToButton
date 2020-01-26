/*
  MIT License

  Copyright (c) 2018 Nathan Ramanathan

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include <SensorToButton.h>
const int buttonPin = 2;
SensorToButton simpleButton(buttonPin, 50); //  button pin, debounce Time(usually 50 ms).

const int led = 3;
bool buttonHolds[3];
bool fadeLED = false;

const int minPWM = 0;
const int maxPWM = 255;
bool b = true, fadePowerOff = false;
int fadeValue = 0;
byte fadeIncrement = 5;
unsigned long previousFadeMillis;
int defaultFadeInterval = 30;
int fadeInterval = defaultFadeInterval;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void doTheFade() {
  // is it time to update yet?
  // if not, nothing happens
  if (millis() - previousFadeMillis >= fadeInterval) {
    // yup, it's time!
    if (b && !fadePowerOff) {
      fadeValue += fadeIncrement;
      if (fadeValue >= maxPWM) {
        // At max, limit and change direction
        fadeValue = maxPWM;
        b = false;
      }
    } else {
      //if we aren't going up, we're going down
      fadeValue -= fadeIncrement;
      if (fadeValue <= minPWM) {
        // At min, limit and change direction
        fadeValue = minPWM;
        b = true;
      }
    }
    // Only need to update when it changes
    analogWrite(led, fadeValue);
    // reset millis for the next iteration (fade timer only)
    previousFadeMillis = millis();
  }
}

void loop()
{
  simpleButton.read();
  if (simpleButton.wasPressed()) {
    Serial.println("Hiya");//prints one time
  }
  if (simpleButton.wasReleased()) {
    Serial.println("Bye");
    memset(buttonHolds, false, sizeof(buttonHolds) / sizeof(buttonHolds[0]));
  }
  if (!buttonHolds[0] && simpleButton.wasHeldFor(1000)) {
    Serial.println("Button held for 1 second");
    if (fadeLED) {
      if (fadeInterval == defaultFadeInterval) {
        fadeInterval = 3;
        Serial.println("\t\tSearching for devices...");
      }
      else {
        fadeInterval = defaultFadeInterval;
        Serial.println("\t\tScan Stopped");
      }
    }
    fadePowerOff = false;
    fadeLED = true;
    buttonHolds[0] = true;
  }
  if (!buttonHolds[1] && simpleButton.wasHeldFor(2000)) {
    Serial.println("Button held for 2 seconds");
    buttonHolds[1] = true;
  }
  if (!buttonHolds[2] && simpleButton.wasHeldFor(3000)) {
    Serial.println("Button held for 3 seconds");
    fadePowerOff = true;
    fadeInterval = defaultFadeInterval;
    buttonHolds[2] = true;
  }
  if (fadeLED) {
    doTheFade();
    if (fadePowerOff && (fadeValue == minPWM)) {
      fadeLED = false;
    }
  }
}
