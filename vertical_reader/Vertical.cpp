#include "Arduino.h"
#include "Vertical.h"

Vertical::Vertical(int pin) {
  _pin = pin;
}

void Motion::start() {
  _start = millis();
  _duration = 0;
  _end = 0;
};

void Motion::end() {
  _end = millis();
  _duration = _end - _start;
};

unsigned long Motion::time_start() {
  return _start;
}
unsigned long Motion::time_end() {
  return _end;
}
unsigned long Motion::duration() {
  return _duration;
}

int Vertical::motion() {
  return _motion;
}

int Vertical::read() {
  int analog_value = analogRead(_pin);
  int new_direction = _motion;
  if (_motion == 0) {
    if (analog_value > 395 && analog_value < 425) {
      // Still Stopped
      new_direction = 0;
    } 
    else if (analog_value <=400 ) {
      // Started up motion
      new_direction = 1;
      _up.start();
    } 
    else if (analog_value >= 420) {
      // Started down
      new_direction = -1;
      _down.start();
    }
  } 
  else {
    //int new_read = analogRead(_pin);
    if (analog_value > 405 && analog_value < 410) 
    {
      // Stopped
      new_direction = 0;
      if (_motion > 0 ) {
        _up.end();
      } 
      else {
        _down.end();
      }
    }
  }    
  _motion = new_direction;
  return analog_value;
};

int Vertical::light() {
  /// Still moving
  if (_motion != 0) {
    Serial.println("In Motion");
    return 0;
  }

  // up after down
  if (_up.time_start() > _down.time_start()) {
    Serial.println("Wrong Order");
    return 0;
  }

  // either longer then .5 seconds
  if (_up.duration() > 750) {
    Serial.println("Up too long");
    return 0;
  }

  if (_down.duration() > 750) {
    Serial.println("Down too long");
    return 0;
  }

  // entire motion longer than 1.5 seconds
  if (( _down.time_end() - _up.time_start()) > 2000) {
    Serial.println("Too far apart");
    return 0;
  }
  
  // ended longed than .5 seconds ago
  if ((millis() - _down.time_end()) > 500) {
    Serial.println("Too long ago");
    return 0;
  }
  
  return 1;
}



