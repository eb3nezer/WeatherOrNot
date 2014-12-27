/*
 * OSV2IndoorTempHygroSensor.cpp
 * Reads data from an "indoor" temperature/hygro sensor such as THGR228N, THGR122X THGR122N
 */

#include "OSV2IndoorTempHygroSensor.h"

OSV2IndoorTempHygroSensor::OSV2IndoorTempHygroSensor() {
	channelNumber = 0;
	tempField = WeatherData::OUTDOOR_TEMP;
	humidityField = WeatherData::OUTDOOR_HUMIDITY;
}

bool OSV2IndoorTempHygroSensor::canDecode(const byte * data, byte numBytes) {
	bool result = false;

    	//Serial.print("q");
    if ((data[0] == 0x1A && data[1] == 0x2D) ||
    	(data[0] == 0x1D && data[1] == 0x20) ||
    	(data[0] == 0xFA && data[1] == 0x28)) {
    	//Serial.print("w");

    		result = true;
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
    	//Serial.print("9");
    }
	return result;
}

void OSV2IndoorTempHygroSensor::decode(const byte * data, byte numBytes, WeatherData *weatherData) {
    	//Serial.print("f");
    int celsius= ((data[5]>>4) * 100)  + ((data[5] & 0x0F) * 10) + ((data[4] >> 4));
    if ((data[6] & 0x0F) >= 8) celsius=-celsius;
    float tempC = celsius / 10.0f;
    //weatherData.setDataField(tempField, tempC, 10);
    weatherData->setDataField(WeatherData::OUTDOOR_TEMP, tempC, 10);

    int humidity = ((data[7] & 0x0F)*10)+ (data[6] >> 4);
    //weatherData.setDataField(humidityField, humidity);
    weatherData->setDataField(WeatherData::OUTDOOR_HUMIDITY, humidity);

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
void OSV2IndoorTempHygroSensor::setChannelNumber(int num) {
	channelNumber = num;
}

byte OSV2IndoorTempHygroSensor::getSensorID() {
	return sensorID;
}

// Set the field to use when reporting the temperature. The default is WeatherData::OUTDOOR_TEMP
void OSV2IndoorTempHygroSensor::setTemperatureField(int value) {
	tempField = value;
}

// Set the field to use when reporting the humidity. The default is WeatherData::OUTDOOR_HUMIDITY
void OSV2IndoorTempHygroSensor::setHumidityField(int value) {
	humidityField = value;
}
