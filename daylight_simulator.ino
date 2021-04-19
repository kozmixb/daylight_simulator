// ---------- INCLUDES ---------- //
#include "color.h"
#include "realtime.h"


void setup() {
  Serial.begin(9600);
  color.SETUP(9, 10, 11);
  realtime.SETUP();
}

void loop() {
  int utime = realtime.getUniqueTimestamp();
  color.setLedBasedOnTime(utime);
  delay(500);
}
