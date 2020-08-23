#ifndef GAMEPAD_H_
#define GAMEPAD_H_

typedef unsigned char button_t;

class Gamepad {
  public:
    virtual const char* buttonLabel(button_t button) = 0;
    virtual bool buttonPressed(button_t button) = 0;
    virtual void printPressedButtons() = 0;
    virtual void read() = 0;
};

#endif
