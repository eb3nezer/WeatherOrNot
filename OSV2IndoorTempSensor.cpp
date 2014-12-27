/*
 * OSV2IndoorTempSensor.cpp
 * Reads data from an "indoor" temperature sensor such as THN122N
 */

#include "OSV2IndoorTempSensor.h"

OSV2IndoorTempSensor::OSV2IndoorTempSensor() {
	channelNumber = 0;
	tempField = WeatherData::OUTDOOR_TEMP;
}

bool OSV2IndoorTempSensor::canDecode(const byte * data, byte numBytes) {
	bool result = false;

    if (data[0] == 0xEA && data[1] == 0x4c) {

    	if (channelNumber == 0) {
    		// Don't care what channel
    		result = true;
    	} else {
    		int channelIn = -1;

            switch (data[2]) {
            case 0x10:
              channelIn = 1;
              break;
            case 0x20:
              channelIn = 2;
              break;
            case 0x40:
              channelIn = 3;
              break;
            }
    		if (channelIn == channelNumber) {
    			result = true;
    		}
    	}
    }
	return result;
}

void OSV2IndoorTempSensor::decode(const byte * data, byte numBytes, WeatherData *weatherData) {
    int celsius= ((data[5]>>4) * 100)  + ((data[5] & 0x0F) * 10) + ((data[4] >> 4));
    if ((data[6] & 0x0F) >= 8) celsius=-celsius;
    float tempC = celsius / 10.0f;
    weatherData->setDataField(tempField, tempC, 10);

    if ((data[4] & 0x0F) >= 4) {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 100);
    }
    else {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 0);
    }
    // Possibly this should be (data[4] & 0xF0) >> 4;
    sensorID = data[4];
}

// Set the channel number that we are interested in (1-3). If you have multiple sensors
// of this type with different channels, use this to differentiate.
// If you don't set the channel number, then this sensor responds to transmissions
// on any channel number.
void OSV2IndoorTempSensor::setChannelNumber(int num) {
	channelNumber = num;
}

byte OSV2IndoorTempSensor::getSensorID() {
	return sensorID;
}

// Set the field to use when reporting the temperature. The default is WeatherData::OUTDOOR_TEMP
void OSV2IndoorTempSensor::setTemperatureField(int value) {
	tempField = value;
}
