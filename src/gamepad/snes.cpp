#include <Arduino.h>

#include "snes.h"

#define SNES_SHIFT_REGISTER_BIT_COUNT 16

static const char* SNES_BUTTON_LABELS[] = {"B", "Y", "Select", "Start",
                        "Up", "Down", "Left", "Right",
                        "A", "X", "L", "R"
                       };

SNESGamepad::SNESGamepad(GPIO_pin_t clock, GPIO_pin_t latch, GPIO_pin_t data) : ESGamepad(clock, latch, data) {}

/**
 * Returns the number of buttons on this gamepad
 */
inline unsigned char SNESGamepad::shiftRegisterBitCount() {
  return SNES_SHIFT_REGISTER_BIT_COUNT;
}

/**
 * Returns the label for the given buton id
 */
inline const char* SNESGamepad::buttonLabel(button_t button) {
  return SNES_BUTTON_LABELS[button];
}
