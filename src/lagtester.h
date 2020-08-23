#ifndef LAG_TESTER_H_
#define LAG_TESTER_H_

#include "gamepad/gamepad.h"
#include "vplayer.h"

class LagTester {
  private:
    VirtualPlayer* vplayer; 
    Gamepad* gamepad;
    unsigned long waitUntilReleased();
    unsigned long waitUntilPressed();
  public:
    LagTester(VirtualPlayer* vplayer, Gamepad* gamepad, unsigned long randomSeed);
    
    unsigned long buttonPressLag(int delayms);
    unsigned long buttonReleaseLag(int delayms);
    
    void runStandardHarness(int sampleCount);
    void gamepadReadHarness(int sampleCount);

    void runFixedHarness(int sampleCount, int delayms);
    void runButtonPressedHarness(int sampleCount, int delayms);
    void runButtonReleasedHarness(int sampleCount, int delayms);

    void runRandomHarness(int sampleCount, int mindelayms, int maxdelayms);
    void runButtonPressedRandomHarness(int sampleCount, int mindelayms, int maxdelayms);
    void runButtonReleasedRandomHarness(int sampleCount, int mindelayms, int maxdelayms);
};

#endif