# Game controller lag tester

Lag tester for various controllers (currently NES and SNES) based on atmega328p microcontroller (e.g. Arduino Uno).

## Requirements

* GNU AVR Toolchain 
  * https://github.com/osx-cross/homebrew-avr for macOS
* Fast digital IO library
  * https://www.codeproject.com/Articles/732646/Fast-digital-I-O-for-Arduino

## Run

```make upload_snes && cat /dev/cu.usbmodem301 | tee snes_8bitdo_sn30-BT_model-DIYSN180320-1318_boardBT-v140506-0118.txt```