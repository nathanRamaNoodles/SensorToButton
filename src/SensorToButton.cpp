#include "Arduino.h"
#include "SensorToButton.h"


SensorToButton::SensorToButton(uint16_t threshold, bool dir, uint8_t debs){
  myThreshold=threshold;
  myDir=dir;
  myDebs=debs;
}
SensorToButton::SensorToButton(uint8_t pin, uint8_t debs){
  _pin=pin;
  pinMode(_pin, INPUT_PULLUP);
  myThreshold=1;
  myDir=false;
  myDebs=debs;
}
void SensorToButton::read(){
  debounceIt(digitalRead(_pin));
}
void SensorToButton::read(uint16_t reading){
  debounceIt(reading);
}
void SensorToButton::debounceIt(uint16_t r){
  changed = defaultTo;     //true for isWasPressed(), false for isWasReleased()
  if (r >= myThreshold) {
    state = myDir;
    heldTime = millis();
  }
  else {
    state = !myDir;
  }
  if (millis() - pM > myDebs) {
    if (state != pState) {
      pState = state;
      changed = state;
      defaultTo = !state;
    }
    pM = millis();
  }
}
bool SensorToButton::isPressed(){
  return pState;
}
bool SensorToButton::wasPressed() {
  return changed && state && pState;
}
bool SensorToButton::wasReleased() {
  return !changed && !state && !pState;  //weird combo, but I don't care.  It works like a charm :D
}
bool SensorToButton::wasHeldFor(uint32_t held_time){
  if (!wasReleased() && (millis() - heldTime>=held_time)) {
    // heldTime = millis();
    return true;
  }
  return false;
}
