#ifndef Vertical_h
#define Vertical_h

#include "Arduino.h"

class Motion
{
public:
  void start(void);
  void end(void);
  unsigned long time_start();
  unsigned long time_end();
  unsigned long duration();
private:
  unsigned long _start;
  unsigned long _end;
  unsigned long _duration;

};

class Vertical
{
public:
  Vertical(int pin);
  int read();
  int motion();
  int light();
private:
  int _pin;
  Motion _up;
  Motion _down;
  int _motion;
};

#endif


