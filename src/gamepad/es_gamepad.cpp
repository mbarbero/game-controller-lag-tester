#include <Arduino.h>

#include "es_gamepad.h"

#define HALF_CYCLE_US 6
#define FULL_CYCLE_US 12

ESGamepad::ESGamepad(GPIO_pin_t clock, GPIO_pin_t latch, GPIO_pin_t data) {
  this->clock = clock;
  this->latch = latch;
  this->data = data;
  init();
}

void ESGamepad::init() {
  // Deck keeps CLOCK -> HIGH 
  pinMode2f(this->clock, OUTPUT);
  digitalWrite2f(this->clock, HIGH);

  // Deck keeps LATCH -> LOW
  pinMode2f(this->latch, OUTPUT);
  digitalWrite2f(this->latch, LOW);

  // Deck keeps DATA -> HIGH
  pinMode2f(this->data, INPUT_PULLUP);

#ifdef DEBUG
  Serial.print("CLOCK="); Serial.println(digitalRead2f(this->clock));
  Serial.print("LATCH="); Serial.println(digitalRead2f(this->latch));
  Serial.print("DATA="); Serial.println(digitalRead2f(this->data));
#endif
}

inline void ESGamepad::pulseLatch() {
  // Latch HIGH for 12us
  // Shift registers stores buttons statess
  digitalWrite2f(this->latch, HIGH);
  delayMicroseconds(FULL_CYCLE_US);
  digitalWrite2f(this->latch, LOW);
  
  // wait half cycle, clock will be pulsed soon after
  delayMicroseconds(HALF_CYCLE_US);
}

inline void ESGamepad::pulseClock() {
  // pull low the clock so shift register put next button state in data 
  digitalWrite2f(this->clock, LOW);
  delayMicroseconds(HALF_CYCLE_US);
  // pull back to high until next read
  digitalWrite2f(this->clock, HIGH);
  delayMicroseconds(HALF_CYCLE_US);
}

/**
 * See http://repairfaq.cis.upenn.edu/Misc/REPAIR/F_SNES.html#SNES_005
 * for communication protocol
 */
void ESGamepad::read() {
  //reinit
  this->b_states = 0;
  pulseLatch();
  // read first as first button is already in data after latch
  for (int i = 0; i < this->shiftRegisterBitCount(); i++) {
    if (digitalRead2f(this->data) == 0) {
      this->b_states |= 1 << i;
    }
    pulseClock();
  }
}

/**
 * Returns !=0 if given button id is pressed
 */
bool ESGamepad::buttonPressed(button_t button) {
  return this->b_states & (1 << button);
}

/**
 * Print on the Serial output the set of pressed button
 */
void ESGamepad::printPressedButtons() {
  Serial.print("( ");
  for (int i = 0; i < this->shiftRegisterBitCount(); i++) {
    if (this->buttonPressed(i)) {
      Serial.print(this->buttonLabel(i));
      Serial.print(" ");
    }
  }
  Serial.println("");
}
