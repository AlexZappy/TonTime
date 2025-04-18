#include <TonTime.h>

TonTime resetTimer(false, 5000);

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  if (digitalRead(3) == LOW) {
    resetTimer.reset();
  }

  resetTimer.xStarted = digitalRead(2) == LOW;
  digitalWrite(13, resetTimer.update());
}