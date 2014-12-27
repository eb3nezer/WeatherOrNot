#ifndef OSV2OUTDOORTEMPHYGROBAROSENSOR_H_
#define OSV2OUTDOORTEMPHYGROBAROSENSOR_H_

#include "Sensor.h"

class OSV2OutdoorTempHygroBaroSensor: public Sensor {
private:
	byte sensorID;
	int tempField;
	int humidityField;

public:
	OSV2OutdoorTempHygroBaroSensor();
	bool canDecode(const byte *data, byte numBytes);
	void decode(const byte *data, byte numBytes, WeatherData *weatherData);
	byte getSensorID();
	void setTemperatureField(int);
	void setHumidityField(int);
};

#endif /* OSV2OUTDOORTEMPHYGROBAROSENSOR_H_ */
