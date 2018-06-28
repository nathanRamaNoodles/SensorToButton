# SensorToButton Arduino Library
This library is meant to eradicate repetitiveness in sensor data and buttons.  [Look here to see what I'm talking about](https://github.com/nathanRamaNoodles/SensorToButton#an-example).
I was inspired by [Jack Christensen's Button Library](https://github.com/JChristensen/JC_Button).
This library is using this [similar techinque](https://www.arduino.cc/en/Tutorial/StateChangeDetection).
It works for all microcontrollers under the Arduino IDE.

---
## Why?
**In a short sentence**: If you want to make a simple threshold detector and avoid overflowing your Serial Monitor with your data **or** activating other functions in your code too many times, then this library will make your life easier.  

**In a longer sentence**: This is extremely efficient and useful for advanced users in Arduino who just want to get a sensor to tell something changed without having to be stuck in a loop of continuous data.  This will bring more functionality with your other methods(the functions that will benefit from this are those who are called when the data meets a condition too often).  **Sure, you could make a boolean to keep track if each method was called more than once, but your code will become inefficient**.

## Benefits
+ Efficient.
+ Neat Code.
+ Low memory usage
+ Debouncing included
+ Easy To Use ;)
---
## Directions
1. [Download the library](https://github.com/nathanRamaNoodles/SensorToButton/archive/master.zip) as a Zip file.
2. Add it to your libraries just like any [other Arduino Library](https://www.arduino.cc/en/guide/libraries).
3. Get a Button or any Sensor and try one of the [examples](https://github.com/nathanRamaNoodles/SensorToButton/tree/master/examples).

---
## An Example
+ [For example](https://github.com/nathanRamaNoodles/SensorToButton/blob/master/examples/pingToButton/pingToButton.ino), if you want to use an Ultrasonic **(range)** Sensor to print **"Hi"** when your hand is 2 cm close and print **"Bye"** when further than 2 cm, then this library will do it.
  + This is what it would look like in the Serial Monitor **without** the Library.
      ```
      Hi
      Hi
      Hi
      Hi
      Bye
      Bye
      Bye
      Bye
      Bye
      ... //Goes for infinity
      ```
  + This is what it looks like **with** the library.
      ```
      Hi
      Bye
      ```
      + It does exactly what you think it does :D
---

## Functions
```
//Used for sensors
SensorToButton(uint16_t threshold, bool dir, uint8_t debs);//what is the threshold, pressUp or pressDown, debounce Time
void read(uint16_t reading);//Put this in loop()

//Used For Regular Buttons
SensorToButton(uint8_t pin, uint8_t debs);//Button Pin, debounce Time
void read();        //Put this in loop()

//For Both
bool isPressed();   //Used when threshold is reached

bool wasPressed();  //Used when threshold was reached once.
bool wasReleased(); //Used when threshold was left once.
```

+ Note that wasPressed() is not the same as isPressed().
+ **pressUp** means that **bigger** values than your threshold mean the "Button" is pressed.
+ **pressDown** means that **smaller** values than your threshold mean the "Button" is pressed.
