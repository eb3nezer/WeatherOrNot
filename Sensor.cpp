#include "Sensor.h"

Sensor::Sensor() {
}

bool Sensor::canDecode(const byte * data, byte numBytes) {
	return false;
}

void Sensor::decode(const byte *, byte numBytes, WeatherData *weatherData) {

}
