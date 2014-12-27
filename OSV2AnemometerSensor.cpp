/*
 * OSV2AnemometerSensor.cpp
 * Reads data from an "indoor" temperature/hygro sensor such as THGR228N, THGR122X THGR122N
 */

#include "OSV2AnemometerSensor.h"

OSV2AnemometerSensor::OSV2AnemometerSensor() {
}

bool OSV2AnemometerSensor::canDecode(const byte * data, byte numBytes) {
	bool result = false;

    if ((data[0] == 0x3A && data[1] == 0x0D) ||
    	(data[0] == 0x19 && data[1] == 0x84) ||
    	(data[0] == 0x19 && data[1] == 0x94) ||
    	(data[0] == 0x1A && data[1] == 0x89)) {

    	//Checksum - add all nibbles from 0 to 8, subtract A and compare to byte 9, should = 0
		int cs = 0;
		for (byte i = 0; i < numBytes-1; ++i) {
			//all but last byte
		   cs += data[i] >> 4;
		   cs += data[i] & 0x0F;
		}
		int csc = ((data[9] >> 4)*16) + (data[9] & 0x0F);
		cs -= 10;
		if (csc == cs) {
			result = true;
		} else {
			// seems like the correct sensor, but bad checksum
		}
    }
	return result;
}

void OSV2AnemometerSensor::decode(const byte * data, byte numBytes, WeatherData *weatherData) {
    int direction = ((data[5]>>4) * 100)  + ((data[5] & 0x0F * 10) ) + (data[4] >> 4);
    float gust = (((data[7] & 0x0F) * 100)  + ((data[6]>>4) * 10)  + ((data[6] & 0x0F))) / 10.0;
    float average = (((data[8]>>4) * 100)  + ((data[8] & 0x0F) * 10)+((data[7] >>4))) / 10.0;

    weatherData->setDataField(WeatherData::WIND_DIRECTION, direction);
    weatherData->setDataField(WeatherData::WIND_GUST, gust, 10);
    weatherData->setDataField(WeatherData::WIND_SPEED, average, 10);

    if ((data[4] & 0x0F) >= 4) {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 100);
    }
    else {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 0);
    }
    // Possibly this should be (data[4] & 0xF0) >> 4;
    sensorID = data[4];
}

byte OSV2AnemometerSensor::getSensorID() {
	return sensorID;
}
