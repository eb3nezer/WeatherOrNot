#include <SPI.h>
#include <WeatherData.h>
#include <WeatherOrNot.h>
#include <OSV2IndoorTempHygroSensor.h>
#include <DecodeOOK.h>
#include <Sensor.h>
#include <OregonDecoderV2.h>
#include <DewpointCalculator.h>

#include <pins_arduino.h>

// The Freetronics 433MHz RF shield sends data on pin 8
#define DATA_PIN 8

// WeatherOrNot does all the work
WeatherOrNot weatherReceiver;

// Declare the decoder for Oregon Scientific V2 protocol sensors
OregonDecoderV2 oregonv2;
// Declare an Oregon Scientific indoor temperature/hygro sensor
OSV2IndoorTempHygroSensor indoorTempHygro;

int dataReceived = 0;
WeatherData currentWeather;

// Callback comes to here
void newWeather(WeatherData *weatherData)
{
    dataReceived = 1;
}

void setup () {
    Serial.begin(4800);
    Serial.println(F("\n[weather...]"));
    
    // Add the Oregon v2 indoor temp/hygro sensor to the Oregon v2 decoder
    oregonv2.addSensor((Sensor *)&indoorTempHygro);
    // Add the Oregon v2 decoder
    weatherReceiver.addDecoder(&oregonv2);

    // Tell it which pin it will see the data on    
    weatherReceiver.setDataPin(DATA_PIN);
    // Tell it to call our newWeather() function
    weatherReceiver.setCallback(newWeather, &currentWeather);
    
    pinMode(DATA_PIN, OUTPUT);
    digitalWrite(DATA_PIN, HIGH);
    digitalWrite(DATA_PIN, LOW);
    pinMode(DATA_PIN, INPUT);
    delay(10);

    // Turn on interrupts    
    weatherReceiver.setInterrupt(true);
    sei();
}

void displayWeather()
{
    float faren;
    float celcius;
    
    if (currentWeather.isSet(WeatherData::OUTDOOR_TEMP)) {
      celcius = currentWeather.getDataAsFloat(WeatherData::OUTDOOR_TEMP); 
      faren = (currentWeather.getDataAsFloat(WeatherData::OUTDOOR_TEMP) * 1.8f) + 32.0f;
      Serial.print("Temperature: ");
      Serial.print(celcius);
      Serial.print("C");
      Serial.print(" ");
      Serial.print(faren);
      Serial.println("F");
    }
    if (currentWeather.isSet(WeatherData::DEW_POINT)) {
      celcius = currentWeather.getDataAsFloat(WeatherData::DEW_POINT); 
      faren = (currentWeather.getDataAsFloat(WeatherData::DEW_POINT) * 1.8f) + 32.0f;
      Serial.print("Dew Point: ");
      Serial.print(celcius);
      Serial.print("C");
      Serial.print(" ");
      Serial.print(faren);
      Serial.println("F");
    }
    if (currentWeather.isSet(WeatherData::OUTDOOR_HUMIDITY)) {
      Serial.print("Humidity: ");
      Serial.print(currentWeather.getDataAsInt(WeatherData::OUTDOOR_HUMIDITY));
      Serial.println("\\%");
    }

}

void loop () {
    if (dataReceived) {
      // Turn off interrupts so we can process the data
      weatherReceiver.setInterrupt(false);
      displayWeather();
      currentWeather.clearDataFields();
      // Turn interrupts back on again
      dataReceived = 0;
      weatherReceiver.setInterrupt(true);
    }

}

