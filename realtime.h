#ifndef realtime_h
#define realtime_h


class rclass {
  public:
    rclass();
    void SETUP();
    int getUniqueTimestamp();
};

extern rclass realtime;
#endif
