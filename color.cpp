#include "Arduino.h"
#include "color.h"

//linear gamma correction values
const uint8_t PROGMEM gamma8[] = {
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,
  2,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   5,   5,   5,
  5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,   8,   9,   9,   9,  10,
  10,  10,  11,  11,  11,  12,  12,  13,  13,  13,  14,  14,  15,  15,  16,  16,
  17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  22,  23,  24,  24,  25,
  25,  26,  27,  27,  28,  29,  29,  30,  31,  32,  32,  33,  34,  35,  35,  36,
  37,  38,  39,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  50,
  51,  52,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  66,  67,  68,
  69,  70,  72,  73,  74,  75,  77,  78,  79,  81,  82,  83,  85,  86,  87,  89,
  90,  92,  93,  95,  96,  98,  99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 196, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

byte red    = 0;
byte green  = 0;
byte blue   = 0;

byte redPin;
byte greenPin;
byte bluePin;

const byte nightLED[] = {0, 32, 50};
const byte sunLED[]   = {255, 157, 64};
const byte dayLED[]   = {255, 255, 164};

// unique timestamp for definig when action need to be taken
// calculated like = Hour * Minute * Second / 10
// Had to divide with 10 otherwise we exceed the limit of int
// (changin color every minute is too quick but every second is unneccesary)
const int sunriseBegin  = 2520; // 07:00
const int dawnBegin     = 2880; // 08:00
const int dayBegin      = 3240; // 09:00
const int sunsetBegin   = 6840; // 19:00
const int duskBegin     = 7200; // 20:00
const int nightBegin    = 7560; // 21:00

cclass::cclass() {
}

void cclass::SETUP(byte pin1, byte pin2, byte pin3) {

  redPin    = pin1;
  greenPin  = pin2;
  bluePin   = pin3;

  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);
}

void cclass::setLedBasedOnTime(int utimestamp)
{
  // Night time
  if (nightBegin <= utimestamp ||  utimestamp < sunriseBegin) {
    Serial.print("NIGHT ");
    red   = nightLED[0];
    green = nightLED[1];
    blue  = nightLED[2];
  }
  // Sunrise
  if (sunriseBegin <=  utimestamp && utimestamp < dawnBegin) {
    Serial.print("SUNRISE ");
    red   = map(utimestamp, sunriseBegin, dawnBegin, nightLED[0], sunLED[0]);
    green = map(utimestamp, sunriseBegin, dawnBegin, nightLED[1], sunLED[1]);
    blue  = map(utimestamp, sunriseBegin, dawnBegin, nightLED[2], sunLED[2]);
  }
  // Dawn
  if (dawnBegin <= utimestamp && utimestamp < dayBegin) {
    Serial.print("DAWN ");
    red   = map(utimestamp, dawnBegin, dayBegin, sunLED[0], dayLED[0]);
    green = map(utimestamp, dawnBegin, dayBegin, sunLED[1], dayLED[1]);
    blue  = map(utimestamp, dawnBegin, dayBegin, sunLED[2], dayLED[2]);
  }
  // Daytime
  if (dayBegin <=  utimestamp && utimestamp < sunsetBegin) {
    Serial.print("DAYTIME ");
    red   = dayLED[0];
    green = dayLED[1];
    blue  = dayLED[2];
  }
  // Sunset
  if (sunsetBegin <=  utimestamp && utimestamp < duskBegin) {
    Serial.print("SUNSET ");
    red   = map(utimestamp, sunsetBegin, duskBegin, dayLED[0], sunLED[0]);
    green = map(utimestamp, sunsetBegin, duskBegin, dayLED[1], sunLED[1]);
    blue  = map(utimestamp, sunsetBegin, duskBegin, dayLED[2], sunLED[2]);
  }
  // Dusk
  if (duskBegin <=  utimestamp && utimestamp < nightBegin) {
    Serial.print("DUSK ");
    red   = map(utimestamp, duskBegin, nightBegin, sunLED[0], nightLED[0]);
    green = map(utimestamp, duskBegin, nightBegin, sunLED[1], nightLED[1]);
    blue  = map(utimestamp, duskBegin, nightBegin, sunLED[2], nightLED[2]);
  }

  Serial.print(utimestamp);
  Serial.print(": ");
  cclass::setColor(red, green, blue);
}

void cclass::setColor() {

  red   = pgm_read_byte(&gamma8[red]);
  green = pgm_read_byte(&gamma8[green]);
  blue  = pgm_read_byte(&gamma8[blue]);

  analogWrite(redPin,   red);
  analogWrite(greenPin, green);
  analogWrite(bluePin,  blue);

  Serial.print("RGB(");
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.print(blue);
  Serial.println(")");

}


cclass color = cclass();
