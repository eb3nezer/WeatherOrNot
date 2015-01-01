// Copyright (c) 2014 Ben Kelley.
//
// MIT License http://opensource.org/licenses/MIT

#ifndef _WeatherData_h
#ifdef __cplusplus
#define _WeatherData_h

#define MAX_DATA_FIELDS 6

class WeatherData {
    private:
        int key[MAX_DATA_FIELDS];
        int value[MAX_DATA_FIELDS];
        bool dataIsSet[MAX_DATA_FIELDS];
        int multiplier[MAX_DATA_FIELDS];
        //char sensorName[16];
    
    public:
        enum {OUTDOOR_TEMP,
        	OUTDOOR_HUMIDITY,
        	WIND_SPEED,
        	WIND_GUST,
        	WIND_DIRECTION,
        	BATTERY_PERCENT,
        	RAIN_RATE,
        	RAIN_TOTAL,
        	// Pressure in hPa
        	BAROMETRIC_PRESSURE,
        	COMFORT,
        	FORECAST,
        	DEW_POINT,
        	INDOOR_TEMP,
        	INDOOR_HUMIDITY};
        WeatherData();
        int getDataAsInt(int field);
        float getDataAsFloat(int field);
        bool isSet(int field);
        void setDataField(int field, int valueIn);
        void setDataField(int field, float value, int multiplier);
        void clearDataFields();
        //void setSensorName(char *);
        //char * getSensorName();
};

#endif
#endif

