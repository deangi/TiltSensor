//----------------------------------------------------------
// Test interrupt driven Tilt sensor (or any switch)
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
// *** BEWARE *** - this is a mechanical switch, it may
// "bounce" several times when it changes state.  In the
// testing I've seen it bounce up to several hundred times!
// In some sense it's more of a "mechanical vibration" sensor.
//

#include <Arduino.h>
#include "TiltSensor.h"

#define SENSORPIN 25
#define LEDPIN 2

TiltSensor tilt(SENSORPIN, 1);

void setup() 
{
  Serial.begin(115200);
  Serial.println("\nTilt sensor test\n");
  pinMode(LEDPIN,OUTPUT);
  digitalWrite(LEDPIN,HIGH);
  tilt.activate();
}

void loop() 
{
  delay(500);

  Serial.print("trigTime "); Serial.print(tilt.lastTriggerTime());
  Serial.print(", trigCount "); Serial.print(tilt.trigCount());
  Serial.print(", state "); Serial.println(tilt.currentState());
  
}
