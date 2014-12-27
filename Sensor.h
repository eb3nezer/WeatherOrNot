#ifndef SENSOR_H_
#define SENSOR_H_

#include <Arduino.h>
#include "WeatherData.h"

class Sensor {
public:
	Sensor();
	virtual bool canDecode(const byte * data, byte numBytes);
	virtual void decode(const byte *data, byte numBytes, WeatherData *weatherData);
};

#endif /* SENSOR_H_ */
