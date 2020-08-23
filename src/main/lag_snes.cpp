#include <Arduino.h>
#include "../gamepad/snes.h"
#include "../vplayer.h"
#include "../lagtester.h"

#define SAMPLES 800

int main() {
  init();

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  SNESGamepad* gamepad = new SNESGamepad(DP3, DP4, DP2);
  VirtualPlayer* vplayer = new VirtualPlayer(DP8, SNESGamepad::BUTTON_L);
  LagTester* harness = new LagTester(vplayer, gamepad, 16);
  
  harness->runStandardHarness(SAMPLES);
    
  Serial.println("Done.");
  delay(1000);

  return 0;
}
