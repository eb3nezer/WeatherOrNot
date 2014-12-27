#ifndef OSV2ANEMOMETERSENSOR_H_
#define OSV2ANEMOMETERSENSOR_H_

#include "Sensor.h"

class OSV2AnemometerSensor: public Sensor {
private:
	byte sensorID;

public:
	OSV2AnemometerSensor();
	bool canDecode(const byte *data, byte numBytes);
	void decode(const byte *data, byte numBytes, WeatherData *weatherData);
	byte getSensorID();
};

#endif /* OSV2ANEMOMETERSENSOR_H_ */
