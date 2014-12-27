#ifndef OSV2INDOORTEMPSENSOR_H_
#define OSV2INDOORTEMPSENSOR_H_

#include "Sensor.h"

class OSV2IndoorTempSensor: public Sensor {
private:
	int channelNumber;
	byte sensorID;
	int tempField;

public:
	OSV2IndoorTempSensor();
	void setChannelNumber(int num);
	bool canDecode(const byte *data, byte numBytes);
	void decode(const byte *data, byte numBytes, WeatherData *weatherData);
	byte getSensorID();
	void setTemperatureField(int);
};

#endif /* OSV2INDOORTEMPSENSOR_H_ */
