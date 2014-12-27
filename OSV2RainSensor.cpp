/*
 * OSV2RainSensor.cpp
 * Reads data OS rain guage.
 */

#include "OSV2RainSensor.h"

OSV2RainSensor::OSV2RainSensor() {
}

bool OSV2RainSensor::canDecode(const byte * data, byte numBytes) {
	bool result = false;

    if ((data[0] == 0x2A && data[1] == 0x1D) ||
    	(data[0] == 0x2D && data[1] == 0x10) ||
    	(data[0] == 0x29 && data[1] == 0x14) ||
    	(data[0] == 0x2A && data[1] == 0x19)) {

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

void OSV2RainSensor::decode(const byte * data, byte numBytes, WeatherData *weatherData) {
    int rainRate = ((data[5]>>4) * 100)  + ((data[5] & 0x0F) * 10) + (data[4] >> 4);
    int rainTotal = ((data[7]  >> 4) * 10)  + (data[6]>>4);

    weatherData->setDataField(WeatherData::RAIN_RATE, rainRate);
    weatherData->setDataField(WeatherData::RAIN_TOTAL, rainTotal);

    if ((data[4] & 0x0F) >= 4) {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 100);
    }
    else {
        weatherData->setDataField(WeatherData::BATTERY_PERCENT, 0);
    }
    // Possibly this should be (data[4] & 0xF0) >> 4;
    sensorID = data[4];
}

byte OSV2RainSensor::getSensorID() {
	return sensorID;
}
