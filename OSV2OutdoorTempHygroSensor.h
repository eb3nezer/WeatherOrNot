#ifndef OSV2OUTDOORTEMPHYGROSENSOR_H_
#define OSV2OUTDOORTEMPHYGROSENSOR_H_

#include "Sensor.h"

class OSV2OutdoorTempHygroSensor: public Sensor {
private:
	byte sensorID;
	int tempField;
	int humidityField;

public:
	OSV2OutdoorTempHygroSensor();
	bool canDecode(const byte *data, byte numBytes);
	void decode(const byte *data, byte numBytes, WeatherData *weatherData);
	byte getSensorID();
	void setTemperatureField(int);
	void setHumidityField(int);
};

#endif /* OSV2INDOORTEMPHYGROSENSOR_H_ */
