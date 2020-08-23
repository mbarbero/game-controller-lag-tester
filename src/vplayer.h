#ifndef VPLAYER_H_
#define VPLAYER_H_

#include <arduino2.h>
#include "gamepad/gamepad.h"

class VirtualPlayer {
  private:
    // the pin to which the trigger transistor is connected to
    GPIO_pin_t pin;
    // the buttonId the transistor will trigger
    button_t button;
  public:
    VirtualPlayer(GPIO_pin_t pin, button_t button);
    void pressButton();
    void releaseButton();  
    button_t buttonUnderTest();
};

#endif