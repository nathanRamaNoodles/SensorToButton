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
#include <CapacitiveSensor.h> //https://github.com/PaulStoffregen/CapacitiveSensor
#include <SensorToButton.h>   //https://github.com/nathanRamaNoodles/SensorToButton
CapacitiveSensor myCap = CapacitiveSensor(A0, A1);       // 1M resistor between pins A0 & A1, pin A1 is sensor pin, add a wire and or foil if desired
SensorToButton capToButton(2000, pressUp, 50);//  threshold,   Are bigger values than threshold mean Press?(true or false), debounce Time(usually 50 ms).
//pressUp means that the values bigger than your threshold mean the "Sensor" is in the on position, pressDown is vias versa.
const int led = LED_BUILTIN;
void setup()
{
  //myCap.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  //analogRead
  uint16_t reading =  myCap.capacitiveSensor(30);
//  Serial.println(reading);   //I found that 2000 is a good threshold for my capacitie "button".  It may be different for you.
  capToButton.read(reading);

  if (capToButton.isPressed()) {
    digitalWrite(led, HIGH);
    //    Serial.println("Hiya");//This is Bad since, it will over fill the Serial buffer. Instead, put this when using myWasPressed();
  }
  else {
    digitalWrite(led, LOW);
    //    Serial.println("Bye"); //Same as previous explanation
  }
  if (capToButton.wasPressed()) {
    Serial.println("Hiya");//prints one time
  }
  if (capToButton.wasReleased()) {
    Serial.println("Bye");
  }
}
