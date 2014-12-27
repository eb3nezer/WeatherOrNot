#include "WeatherOrNot.h"
#include "DecodeOOK.h"
#include <SPI.h>
#include <Arduino.h>
#include <pins_arduino.h>

// Interrupt handling code from Mike Cook

// Store functions to call when there is a signal on the appropriate input pin
static WeatherOrNot* objectRef[24] = {
  NULL };

volatile static uint8_t PCintLast[3];

//static word last;

/* Pin to interrupt map:
 * D0-D7 = PCINT 16-23 = PCIR2 = PD = PCIE2 = pcmsk2
 * D8-D13 = PCINT 0-5 = PCIR0 = PB = PCIE0 = pcmsk0
 * A0-A5 (D14-D19) = PCINT 8-13 = PCIR1 = PC = PCIE1 = pcmsk1
 */

volatile uint8_t *port_to_pcmask[] = {
  &PCMSK0,
  &PCMSK1,
  &PCMSK2
};


// common code for isr handler. "port" is the PCINT number.
// there isn't really a good way to back-map ports and masks to pins.
static void PCint(uint8_t port) {
  uint8_t bit;
  uint8_t curr;
  uint8_t mask;
  uint8_t pin;

  // get the pin states for the indicated port.
  curr = *portInputRegister(port+2);
  mask = curr ^ PCintLast[port];
  PCintLast[port] = curr;
  // mask is pins that have changed. screen out non pcint pins.
  if ((mask &= *port_to_pcmask[port]) == 0) {
    return;
  }
  // mask is pcint pins that have changed.
  for (uint8_t i=0; i < 8; i++) {
    bit = 0x01 << i;
    if (bit & mask) {
      pin = port * 8 + i;
      if (objectRef[pin] != NULL) {
    	  (*(objectRef[pin])).dataReceived(pin);
      }
    }
  }
}

SIGNAL(PCINT0_vect) {
  PCint(0);
}
SIGNAL(PCINT1_vect) {
  PCint(1);
}
SIGNAL(PCINT2_vect) {
  PCint(2);
}

// Copyright (c) 2014 Ben Kelley.
//
// MIT License http://opensource.org/licenses/MIT

WeatherOrNot::WeatherOrNot() {
    dataPin = -1;
    weatherData = NULL;
}

void WeatherOrNot::addDecoder(DecodeOOK *decoderIn) {
	if (decoderCount < 10) {
		(decoders[decoderCount]) = decoderIn;
		decoderCount++;
	}
}

int WeatherOrNot::getDecoderCount() {
	return decoderCount;
}

void WeatherOrNot::setDataPin(uint8_t dataPinIn) {
    dataPin = dataPinIn;
}

void WeatherOrNot::dataReceived(int pin)
{
    static word last;
    // determine the pulse length in microseconds, for either polarity
    pulse = micros() - last;
    last += pulse;

    bool found = false;

    for (int loop = 0; (loop < decoderCount) && (!found); loop++) {

    	if (decoders[loop]->nextPulse(pulse)) {
    		if (decoders[loop]->canDecode()) {
    			found = true;
    			decoders[loop]->getWeatherData(weatherData);
    			decoders[loop]->resetDecoder();
    			callback(weatherData);
    		}
    		else {
    			// Decoder recognises the bit stream, but no sensor for that decoder
    			// recognised the data
    		}
    	}
    }
}

void WeatherOrNot::setCallback(weatherFuncPtr newCallback, WeatherData *weatherDataPtr)
{
	callback = newCallback;
	weatherData = weatherDataPtr;
}

bool WeatherOrNot::setInterrupt(bool enable) {
	bool result = true;

	if (dataPin < 0) {
		result = false;
	} else {

	    uint8_t bit = digitalPinToBitMask(dataPin);
	    uint8_t port = digitalPinToPort(dataPin);
	    uint8_t slot;
	    volatile uint8_t *pcmask;
	    if (port == NOT_A_PORT) {
	    	Serial.print("Could not map pin ");
	    	Serial.print(dataPin);
	    	Serial.println(" to a port!");
	    	result = false;
	    }
	    else
	    {
	    	port -= 2;
	    	pcmask = port_to_pcmask[port];
		    slot = port * 8 + (dataPin % 8);
		    //Serial.print("Slot is ");
		    //Serial.println(slot);
		    objectRef[slot] = this;
		    if (enable) {
		        // set the mask
		        *pcmask |= bit;
		        objectRef[slot] = this;
		        // enable the interrupt
		        PCICR |= 0x01 << port;
		    }
		    else {
		        // clear the mask
		        *pcmask &= ~bit;
		        objectRef[slot] = NULL;
		        // disable the interrupt
		        PCICR &= ~(0x01 << port);
		    }
	    }
	}

	return result;
}

