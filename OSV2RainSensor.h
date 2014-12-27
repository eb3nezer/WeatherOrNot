#ifndef OSV2RAINSENSOR_H_
#define OSV2RAINSENSOR_H_

#include "Sensor.h"

class OSV2RainSensor: public Sensor {
private:
	byte sensorID;

public:
	OSV2RainSensor();
	bool canDecode(const byte *data, byte numBytes);
	void decode(const byte *data, byte numBytes, WeatherData *weatherData);
	byte getSensorID();
};

#endif /* OSV2RAINSENSOR_H_ */
