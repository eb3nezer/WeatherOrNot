// Copyright (c) 2014 Ben Kelley.
//
// MIT License http://opensource.org/licenses/MIT

#include "DewpointCalculator.h"
#include <math.h>

void calculateDewpoint(WeatherData *weatherData) {
	if (weatherData->isSet(WeatherData::OUTDOOR_TEMP) &&
		weatherData->isSet(WeatherData::OUTDOOR_HUMIDITY)) {

			float temperature = weatherData->getDataAsFloat(WeatherData::OUTDOOR_TEMP);
			int humidity = weatherData->getDataAsInt(WeatherData::OUTDOOR_HUMIDITY);

			double b = (log(humidity / 100.0) + ((17.27 * temperature) / (237.3 + temperature))) / 17.27;

			double dewpoint = (237.3 * b) / (1 - b);

			weatherData->setDataField(WeatherData::DEW_POINT, dewpoint, 10);
	}
}

