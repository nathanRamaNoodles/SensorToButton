/*
SensorToButton.h - Library for converting sensors into buttons with debouncing.
SensorToButton Library created by Nathan Ramanathan(nathan6ramanathan@gmail.com), May 20, 2018
Released into the public domain.
*/

#ifndef SensorToButton_h
#define SensorToButton_h

#define pressUp true
#define pressDown false

#include "Arduino.h"
class SensorToButton
{
public:
  SensorToButton(uint16_t threshold, bool dir, uint8_t debs);
  SensorToButton(uint8_t pin, uint8_t debs);
  void read();
  void read(uint16_t reading);
  bool isPressed();
  bool wasPressed();
  bool wasReleased();

private:
  void debounceIt(uint16_t r);
  uint16_t myThreshold, myDebs;
  uint8_t _pin;
  bool pState,state,changed, myDir;
  bool defaultTo=true;
  uint32_t pM = 0;
};
#endif
