#ifndef SNES_H_
#define SNES_H_

#include <arduino2.h>

#include "es_gamepad.h"


class SNESGamepad: public ESGamepad {
  public:
    static const button_t BUTTON_B=0;
    static const button_t BUTTON_Y=1;
    static const button_t BUTTON_SELECT=2;
    static const button_t BUTTON_START=3;
    static const button_t BUTTON_UP=4;
    static const button_t BUTTON_DOWN=5;
    static const button_t BUTTON_LEFT=6;
    static const button_t BUTTON_RIGHT=7;
    static const button_t BUTTON_A=8;
    static const button_t BUTTON_X=9;
    static const button_t BUTTON_L=10;
    static const button_t BUTTON_R=11;
    
    SNESGamepad(GPIO_pin_t clock, GPIO_pin_t latch, GPIO_pin_t data);

  private:
    const char* buttonLabel(button_t button) override;
    unsigned char shiftRegisterBitCount() override;

};

#endif