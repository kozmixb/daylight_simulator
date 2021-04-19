#ifndef color_h
#define color_h


class cclass {
  public:
    cclass();
    void SETUP(byte pin1, byte pin2, byte pin3);
    void setLedBasedOnTime(int utimestamp);
    void setColor();
};

extern cclass color;
#endif
