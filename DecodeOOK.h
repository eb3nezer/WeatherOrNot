// Oregon V2 decoder added - Dominique Pierre
// Oregon V3 decoder revisited - Dominique Pierre
// New code to decode OOK signals from weather sensors, etc.
// 2010-04-11 <jcw@equi4.com> http://opensource.org/licenses/mit-license.php
// $Id: ookDecoder.pde 5331 2010-04-17 10:45:17Z jcw $

#ifndef _DecodeOOK_h
#ifdef __cplusplus
#define _DecodeOOK_h

#include <Arduino.h>
#include "Sensor.h"
#include "WeatherData.h"

class DecodeOOK {
protected:
    byte total_bits, bits, flip, state, pos, data[25];
    virtual char decode (word width);
    Sensor * sensors[10];
    int sensorCount;
public:
  enum { UNKNOWN, T0, T1, T2, T3, OK, DONE };

  DecodeOOK ();
  bool nextPulse (word width);
  bool isDone () const;
  const byte* getData (byte& count) const;
  void resetDecoder ();
  virtual void gotBit (char value);
  void manchester (char value);
  void alignTail (byte max);
  void reverseBits ();
  void reverseNibbles ();
  void done ();
  void dataReceived();
  void addSensor(Sensor*);
  bool canDecode();
  void getWeatherData(WeatherData*);
  int getSensorCount();
};

#endif
#endif
