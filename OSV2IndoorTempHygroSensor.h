#ifndef OSV2INDOORTEMPHYGROSENSOR_H_
#define OSV2INDOORTEMPHYGROSENSOR_H_

#include "Sensor.h"

class OSV2IndoorTempHygroSensor: public Sensor {
private:
	int channelNumber;
	byte sensorID;
	int tempField;
	int humidityField;

public:
	OSV2IndoorTempHygroSensor();
	void setChannelNumber(int num);
	bool canDecode(const byte *data, byte numBytes);
	void decode(const byte *, byte, WeatherData *);
	byte getSensorID();
	void setTemperatureField(int);
	void setHumidityField(int);
};

#endif /* OSV2INDOORTEMPHYGROSENSOR_H_ */
