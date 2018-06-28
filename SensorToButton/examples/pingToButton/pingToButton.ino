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
#include <NewPing.h>  //https://playground.arduino.cc/Code/NewPing
#include <SensorToButton.h>
SensorToButton pingToButton(10, pressDown, 100);//  threshold is 10 cm,   Are bigger values than threshold mean Press?(true or false), debounce Time(usually 50 ms).

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
const int led = 13;
void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  pinMode(led, OUTPUT);
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
//  Serial.print("Ping: ");
//  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
//  Serial.println("cm");
  pingToButton.read(sonar.ping_cm());

  if (pingToButton.isPressed()) {
    digitalWrite(led, HIGH);
    //    Serial.println("Hiya");//This is Bad since, it will over fill the Serial buffer. Instead, put this when using myWasPressed();
  }
  else {
    digitalWrite(led, LOW);
    //    Serial.println("Bye"); //Same as previous explanation
  }
  if (pingToButton.wasPressed()) {//does stuff only once
    Serial.println("Hiya");//prints one time
  }
  if (pingToButton.wasReleased()) {//does stuff only once
    Serial.println("Bye");
  }
}
