#include "vplayer.h"

VirtualPlayer::VirtualPlayer(GPIO_pin_t pin, button_t button) {
  this->pin = pin;
  this->button = button;
}

void VirtualPlayer::pressButton() {
  digitalWrite2f(this->pin, HIGH);
}

void VirtualPlayer::releaseButton() {
  digitalWrite2f(this->pin, LOW);
}

button_t VirtualPlayer::buttonUnderTest() {
  return this->button;
}
