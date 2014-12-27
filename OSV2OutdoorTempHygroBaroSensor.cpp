/*
 * OSV2OutdoorTempHygroBaroSensor.cpp
 * Reads data from an "outdoor" temperature/hygro/barometric sensor such as BTHR918, BTHR968
 */

#include "OSV2OutdoorTempHygroBaroSensor.h"

OSV2OutdoorTempHygroBaroSensor::OSV2OutdoorTempHygroBaroSensor() {
	tempField = WeatherData::OUTDOOR_TEMP;
	humidityField = WeatherData::OUTDOOR_HUMIDITY;
}

bool OSV2OutdoorTempHygroBaroSensor::canDecode(const byte * data, byte numBytes) {
	bool result = false;

    if ((data[0] == 0x5A && data[1] == 0x5D) ||
    	(data[0] == 0x5D && data[1] == 0x60)  ||
    	(data[0] == 0x5A && data[1] == 0x6D)) {

		result = true;
    }
	return result;
}

void OSV2OutdoorTempHygroBaroSensor::decode(const byte * data, byte numBytes, WeatherData *weatherData) {
    int celsius= ((data[5]>>4) * 100)  + ((data[5] & 0x0F) * 10) + ((data[4] >> 4));
    if ((data[6] & 0x0F) >= 8) celsius=-celsius;
    float tempC = celsius / 10.0f;
    weatherData->setDataField(tempField, tempC, 10);

    int humidity = ((data[7] & 0x0F)*10)+ (data[6] >> 4);
    weatherData->setDataField(humidityField, humidity);

    int pressure = (data[8])+856;
    weatherData->setDataField(WeatherData::BAROMETRIC_PRESSURE, pressure);

    int comfort = -1;
    switch (data[7] & 0xC0) {
    	case 0x00:
    		// Normal
    		comfort = 0;
    		break;
    	case 0x40:
    		// Comfortable
    		comfort = 1;
    		break;
    	case 0x80:
    		// Dry
    		comfort = 2;
    		break;
    	case 0xC0:
    		// Wet
    		comfort = 3;
    		break;
    }
    if (comfort >= 0) {
        weatherData->setDataField(WeatherData::COMFORT, comfort);
    }

    int forecast = -1;
    switch (data[9] >> 4) {
    	case 0x0C:
    		// Sunny
    		forecast = 0;
    		break;
    	case 0x06:
    		// Partly Cloudy
    		forecast = 1;
    		break;
    	case 0x02:
    		// Cloudy
    		forecast = 2;
    		break;
    	case 0x03:
    		// Rain
    		forecast = 3;
    		break;
    }
    if (forecast >= 0) {
        weatherData->setDataField(WeatherData::FORECAST, forecast);
    }

    if ((data[4] & 0x0F) >= 4) {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 100);
    }
    else {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 0);
    }
    // Possibly this should be (data[4] & 0xF0) >> 4;
    sensorID = data[4];
}

byte OSV2OutdoorTempHygroBaroSensor::getSensorID() {
	return sensorID;
}

// Set the field to use when reporting the temperature. The default is WeatherData::OUTDOOR_TEMP
void OSV2OutdoorTempHygroBaroSensor::setTemperatureField(int value) {
	tempField = value;
}

// Set the field to use when reporting the humidity. The default is WeatherData::OUTDOOR_HUMIDITY
void OSV2OutdoorTempHygroBaroSensor::setHumidityField(int value) {
	humidityField = value;
}
