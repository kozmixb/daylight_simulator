#include "Arduino.h"
#include "realtime.h"
#include "DS3231.h"
#include "Wire.h"

DS3231 Clock;
bool h12;
bool PM;

rclass::rclass() {
}

void rclass::SETUP() {
  Wire.begin();
  }

int rclass::getUniqueTimestamp()
{
  byte hour = Clock.getHour(h12, PM); 
  byte minute = Clock.getMinute();
  byte second = Clock.getSecond();

  int result = (hour *360) + (minute * 6) + (second / 10);
  return result;
}



rclass realtime = rclass();
