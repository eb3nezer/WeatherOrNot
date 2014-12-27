#ifndef _WeatherOrNot_h
#ifdef __cplusplus
#define _WeatherOrNot_h

#include <Arduino.h>
#include "WeatherData.h"
#include "DecodeOOK.h"

typedef void (*weatherFuncPtr)(WeatherData *data);

class WeatherOrNot {
    private:
        volatile word pulse;
        uint8_t dataPin;
        DecodeOOK * decoders[10];
        int decoderCount;
        weatherFuncPtr callback;
        WeatherData *weatherData;
    
    public:
        WeatherOrNot();
        void addDecoder(DecodeOOK *decoderIn);
        void setDataPin(uint8_t dataPin);
        bool setInterrupt(bool enable);
        void dataReceived(int dataPin);
        void setCallback(weatherFuncPtr newCallback, WeatherData *weatherDataPtr);
        int getDecoderCount();
};

#endif
#endif

