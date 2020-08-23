#include <Arduino.h>
#include "lagtester.h"

LagTester::LagTester(VirtualPlayer* vplayer, Gamepad* gamepad, unsigned long seed) {
  this->vplayer = vplayer;
  this->gamepad = gamepad;
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(seed);
}

void printTime(unsigned long t) {
  Serial.print(t);
  Serial.print(',');
}

void LagTester::gamepadReadHarness(int sampleCount) {
  Serial.print("gamepad(");
  Serial.print(");");
  for (int i = 0; i < sampleCount; i++) {
    unsigned long start_timer = micros();
    gamepad->read();
    printTime(micros() - start_timer);
  }
}

void LagTester::runStandardHarness(int sampleCount) {
  gamepadReadHarness(64);

  runFixedHarness(sampleCount, 1);
  runFixedHarness(sampleCount, 4);
  runFixedHarness(sampleCount, 16);
  runFixedHarness(sampleCount, 64);
  runFixedHarness(sampleCount, 125);
  runFixedHarness(sampleCount, 500);
  runFixedHarness(sampleCount, 1000);
  
  runRandomHarness(sampleCount, 150, 300);
  runRandomHarness(sampleCount, 500, 1000);
  runRandomHarness(sampleCount, 400, 1200);
  runRandomHarness(sampleCount, 250, 1500);
}

void LagTester::runFixedHarness(int sampleCount, int delayms) {
  Serial.print("fixed(");
  Serial.print(delayms);
  Serial.print(");");
  Serial.print("press(");
  Serial.print(gamepad->buttonLabel(vplayer->buttonUnderTest()));
  Serial.print(");");
  runButtonPressedHarness(sampleCount, delayms);
  Serial.println();

  Serial.print("fixed(");
  Serial.print(delayms);
  Serial.print(");");
  Serial.print("release(");
  Serial.print(gamepad->buttonLabel(vplayer->buttonUnderTest()));
  Serial.print(");");
  runButtonReleasedHarness(sampleCount, delayms);
  Serial.println();
}

void LagTester::runRandomHarness(int sampleCount, int mindelayms, int maxdelayms) {
  Serial.print("random(");
  Serial.print(mindelayms);
  Serial.print(",");
  Serial.print(maxdelayms);
  Serial.print(");");
  Serial.print("press(");
  Serial.print(gamepad->buttonLabel(vplayer->buttonUnderTest()));
  Serial.print(");");
  runButtonPressedRandomHarness(sampleCount, mindelayms, maxdelayms);

  Serial.print("random(");
  Serial.print(mindelayms);
  Serial.print(",");
  Serial.print(maxdelayms);
  Serial.print(");");
  Serial.print("press(");
  Serial.print(gamepad->buttonLabel(vplayer->buttonUnderTest()));
  Serial.print(");");
  runButtonReleasedRandomHarness(sampleCount, mindelayms, maxdelayms);
}

void LagTester::runButtonPressedHarness(int sampleCount, int delayms) {
  for (int i = 0; i < sampleCount; i++) {
    printTime(buttonPressLag(delayms)); 
  }
}

void LagTester::runButtonReleasedHarness(int sampleCount, int delayms) {
  for (int i = 0; i < sampleCount; i++) {
    printTime(buttonReleaseLag(delayms));
  }
}

void LagTester::runButtonPressedRandomHarness(int sampleCount, int mindelayms, int maxdelayms) {
  for (int i = 0; i < sampleCount; i++) {
    printTime(buttonPressLag(random(mindelayms, maxdelayms))); 
  }
}

void LagTester::runButtonReleasedRandomHarness(int sampleCount, int mindelayms, int maxdelayms) {
  for (int i = 0; i < sampleCount; i++) {
    printTime(buttonReleaseLag(random(mindelayms, maxdelayms))); 
  }
}

void _delayHalf(int delayms) {
  if (delayms < 32) {
    double halfDelay=((double)(delayms*1000))/((double)2);
#ifdef DEBUG
  Serial.print("delay us="); Serial.println((double)(delayms*1000));
  Serial.print("half delay us="); Serial.println((unsigned int)halfDelay);
#endif
    // Currently, the largest value that will produce an accurate delay is 16383
    // 32ms/2 = 16000us 
    delayMicroseconds(halfDelay);
  } else {
    double halfDelay=((double)delayms)/((double)2);
#ifdef DEBUG
  Serial.print("delay ms="); Serial.println((double)delayms);
  Serial.print("half delay ms="); Serial.println((unsigned long)halfDelay);
#endif
    delay(halfDelay);
  }
}

inline unsigned long LagTester::buttonPressLag(int delayms) {
  // ensure button is in proper state before testing
  vplayer->releaseButton();
  waitUntilReleased();

  _delayHalf(delayms);
  digitalWrite(LED_BUILTIN, HIGH);

  vplayer->pressButton();
  unsigned long start_timer = micros();
  unsigned long ret = waitUntilPressed() - start_timer;
  
  _delayHalf(delayms);
  digitalWrite(LED_BUILTIN, LOW); 

  return ret;
}

inline unsigned long LagTester::buttonReleaseLag(int delayms) {
  // ensure button is in proper state before testing
  vplayer->pressButton();
  waitUntilPressed();

  _delayHalf(delayms);
  digitalWrite(LED_BUILTIN, HIGH);

  vplayer->releaseButton();
  unsigned long start_timer = micros();
  unsigned long ret = waitUntilReleased() - start_timer;

  _delayHalf(delayms);
  digitalWrite(LED_BUILTIN, LOW);

  return ret; 
}

inline unsigned long LagTester::waitUntilReleased() {
  while (gamepad->buttonPressed(vplayer->buttonUnderTest())) {
    gamepad->read();
  }
  return micros();
}

inline unsigned long LagTester::waitUntilPressed() {
  while (!gamepad->buttonPressed(vplayer->buttonUnderTest())) {
    gamepad->read();
  }
  return micros();
}
