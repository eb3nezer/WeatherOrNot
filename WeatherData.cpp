// Copyright (c) 2014 Ben Kelley.
//
// MIT License http://opensource.org/licenses/MIT

#include "WeatherData.h"

WeatherData::WeatherData() {
    int loop;
    for(loop = 0; loop < MAX_DATA_FIELDS; loop++) {
        key[loop] = -1;
        value[loop] = 0;
        dataIsSet[loop] = false;
        multiplier[loop] = 1;
    }
}

void WeatherData::setDataField(int field, int valueIn) {
    // Find where this is already set, or an empty slot
    bool found = false;
    int loop;
    for (loop = 0; loop < MAX_DATA_FIELDS && !found; loop++) {
        if (key[loop] == field || key[loop] == -1) {
            found = true;
            value[loop] = valueIn;
            dataIsSet[loop] = true;
            multiplier[loop] = 1;
            key[loop] = field;
        }
    }
}

void WeatherData::setDataField(int field, float valueIn, int multiplierIn) {
    // Find where this is already set, or an empty slot
    bool found = false;
    int loop;
    for (loop = 0; loop < MAX_DATA_FIELDS && !found; loop++) {
        if (key[loop] == field || key[loop] == -1) {
            found = true;
            value[loop] = valueIn * (float) multiplierIn;
            dataIsSet[loop] = true;
            multiplier[loop] = multiplierIn;
            key[loop] = field;
        }
    }
}

void WeatherData::clearDataFields() {
    bool found = false;

    for (int loop = MAX_DATA_FIELDS; loop >= 0; loop--) {
        key[loop] = -1;
        dataIsSet[loop] = false;
    }
}

int WeatherData::getDataAsInt(int fieldIn) {
    int result = 0;
    bool found = false;
    
    for (int loop = 0; loop < MAX_DATA_FIELDS && !found; loop++) {
        if (key[loop] == fieldIn) {
            found = true;
            if (dataIsSet[loop]) {
                result = value[loop];
            }
        }
    }
    
    return result;
}

float WeatherData::getDataAsFloat(int fieldIn) {
    
    float result = 0.0;
    bool found = false;
    
    for (int loop = 0; loop < MAX_DATA_FIELDS && !found; loop++) {
        if (key[loop] == fieldIn) {
            found = true;
            if (dataIsSet[loop]) {
                result = (float) value[loop] / (float) multiplier[loop];
            }
        }
    }
    
    return result;
}

bool WeatherData::isSet(int fieldIn) {
    bool result = false;
    bool found = false;
    
    for (int loop = 0; loop < MAX_DATA_FIELDS && !found; loop++) {
        if (key[loop] == fieldIn || key[loop] == -1) {
            found = true;
            if (key[loop] == fieldIn) {
                result = dataIsSet[loop];
            }
        }
    }

    return result;
}
    
//void WeatherData::setSensorName(char *name) {
//	strcpy(sensorName, name);
//}

//char * WeatherData::getSensorName() {
//	return sensorName;
//}
