// ---------- INCLUDES ---------- //
#include "color.h"


void setup() {
  Serial.begin(9600);
  color.SETUP(9,11,10);
}

void loop() {
  for (int i = 2200; i < 8640; i++) {

    color.setLedBasedOnTime(i);
    delay(100);
  }
}
