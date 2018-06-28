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
const int buttonPin = 8;
SensorToButton simpleButton(buttonPin, 50); //  button pin, debounce Time(usually 50 ms).

const int led = 13;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  simpleButton.read();
  if (simpleButton.isPressed()) {
    digitalWrite(led, HIGH);
    //    Serial.println("Hiya");//This is Bad since, it will over fill the Serial buffer. Instead, print to Serial when using wasPressed();
  }
  else {
    digitalWrite(led, LOW);
    //    Serial.println("Bye"); //Same as previous explanation
  }
  if (simpleButton.wasPressed()) {
    Serial.println("Hiya");//prints one time
  }
  if (simpleButton.wasReleased()) {
    Serial.println("Bye");
  }
}
