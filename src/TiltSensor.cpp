//----------------------------------------------------------
// Driver class for passive tilt sensor
//
// Dean Gienger, March 1, 2024
//
// Dean Gienger, March 7, 2024
//
// A tilt sensor is a sensor which has two wires connected
// to a switch.  When the switch package is tilted, the
// switch changes state.   It could be normally open or
// normally closed.  But when it is tilted it changes state.
//
// In this class we attach an interrupt to a GPIO pin and
// watch for a RISING edge (if switch is normally closed) or
// FALLING edge (if switch is normally open).
//
// V1.0 - initial release
//----------------------------------------------------------

#include "TiltSensor.h"
#include <FunctionalInterrupt.h>

//------------------------------------------------
// Constructor
TiltSensor::TiltSensor(int gpiopin, int detectRisingEdge)
{
    gpioPin = gpiopin;
    triggerCount = 0;
    lastReadTriggerCount = 0;
    trigTime = 0;
	isRisingEdge = (detectRisingEdge != 0);
    pinMode(gpioPin,INPUT_PULLUP);
}

//------------------------------------------------
// activate a sensor on a particular pin
int TiltSensor::activate()
{
  triggerCount = 0;
  lastReadTriggerCount = 0;
  trigTime = 0;
  pinMode(gpioPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), 
    std::bind(&TiltSensor::isr,this),
	isRisingEdge ? RISING : FALLING);
  return true; // success
}

//------------------------------------------------
// detach a sensor - make it inactive
int TiltSensor::deactivate()
{
  detachInterrupt(gpioPin);
  gpioPin = -1; // not assigned, not active
  return true; // success
}

//------------------------------------------------
// true if there was a trigger in last xms
int TiltSensor::triggeredWithin(unsigned long xms)
{
  unsigned long x = millis() - trigTime;
  return x <= xms;
}

//------------------------------------------------
// see how many triggers since last time
// this routine was called
unsigned long TiltSensor::currentTriggers() 
{ 
  unsigned long n = triggerCount - lastReadTriggerCount; 
  lastReadTriggerCount = triggerCount; 
  return n;
}
