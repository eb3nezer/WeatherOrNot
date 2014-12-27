/*
 * OSV2OutdoorTempHygroSensor.cpp
 * Reads data from an "outdoor" temperature/hygro sensor such as THGR918, THGR810v1, THGR810
 */

#include "OSV2OutdoorTempHygroSensor.h"

OSV2OutdoorTempHygroSensor::OSV2OutdoorTempHygroSensor() {
	tempField = WeatherData::OUTDOOR_TEMP;
	humidityField = WeatherData::OUTDOOR_HUMIDITY;
}

bool OSV2OutdoorTempHygroSensor::canDecode(const byte * data, byte numBytes) {
	bool result = false;

    if ((data[0] == 0x1A && data[1] == 0x3D) ||
    	(data[0] == 0x3A && data[1] == 0x0D) ||
    	(data[0] == 0xF8 && data[1] == 0x24) ||
    	(data[0] == 0x1D && data[1] == 0x20)) {

    	//Checksum - add all nibbles from 0 to 8, subtract A and compare to byte 9, should = 0
		int cs = 0;
		for (byte i = 0; i < numBytes-1; ++i) {
			//all but last byte
		   cs += data[i] >> 4;
		   cs += data[i] & 0x0F;
		}
		int csc = ((data[8] >> 4)*16) + (data[8] & 0x0F);
		cs -= 10;
		if (csc == cs) {
			result = true;
		} else {
			// seems like the correct sensor, but bad checksum
		}
    }
	return result;
}

void OSV2OutdoorTempHygroSensor::decode(const byte * data, byte numBytes, WeatherData *weatherData) {
    int celsius= ((data[5]>>4) * 100)  + ((data[5] & 0x0F) * 10) + ((data[4] >> 4));
    if ((data[6] & 0x0F) >= 8) celsius=-celsius;
    float tempC = celsius / 10.0f;
    weatherData->setDataField(tempField, tempC, 10);

    // int humidity = ((data[7] & 0x0F)*10)+ (data[4] >> 4);
    int humidity = ((data[7] & 0x0F)*10)+ (data[6] >> 4);
    weatherData->setDataField(humidityField, humidity);

    if ((data[4] & 0x0F) >= 4) {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 100);
    }
    else {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 0);
    }
    // Possibly this should be (data[4] & 0xF0) >> 4;
    sensorID = data[4];
}

byte OSV2OutdoorTempHygroSensor::getSensorID() {
	return sensorID;
}

// Set the field to use when reporting the temperature. The default is WeatherData::OUTDOOR_TEMP
void OSV2OutdoorTempHygroSensor::setTemperatureField(int value) {
	tempField = value;
}

// Set the field to use when reporting the humidity. The default is WeatherData::OUTDOOR_HUMIDITY
void OSV2OutdoorTempHygroSensor::setHumidityField(int value) {
	humidityField = value;
}
