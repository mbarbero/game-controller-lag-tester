#ifndef ES_GAMEPAD_H_
#define ES_GAMEPAD_H_

#include <arduino2.h>

#include "gamepad.h"

class ESGamepad: public Gamepad {
  public:
    ESGamepad(GPIO_pin_t clock, GPIO_pin_t latch, GPIO_pin_t data);
    bool buttonPressed(button_t button) override;
    void printPressedButtons() override;
    void read() override;
  protected: 
    virtual unsigned char shiftRegisterBitCount() = 0;
  private:
    int b_states;
    GPIO_pin_t clock, latch, data;
    
    void init();
    void pulseLatch();
    void pulseClock();
};

#endif
