#include <Arduino.h>

#include "nes.h"

#define NES_SHIFT_REGISTER_BIT_COUNT 8

static const char* NES_BUTTON_LABELS[] = {"A", "B", "Select", "Start",
                        "Up", "Down", "Left", "Right" };

NESGamepad::NESGamepad(GPIO_pin_t clock, GPIO_pin_t latch, GPIO_pin_t data) : ESGamepad(clock, latch, data) {}

/**
 * Returns the number of buttons on this gamepad
 */
inline unsigned char NESGamepad::shiftRegisterBitCount() {
  return NES_SHIFT_REGISTER_BIT_COUNT;
}

/**
 * Returns the label for the given buton id
 */
inline const char* NESGamepad::buttonLabel(button_t button) {
  return NES_BUTTON_LABELS[button];
}
