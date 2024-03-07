//----------------------------------------------------------
// Driver class for passive tilt sensor
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

#include <Arduino.h>
class TiltSensor
{
  public:
    //--- Constructor ---
    TiltSensor(int gpiopin, int detectRisingEdge);
    ~TiltSensor() { deactivate(); }
    
    //--- millis() time when we last triggered, 0 means none
    unsigned long lastTriggerTime() { return trigTime; }
    
    // true if we triggered with the last xms
    int triggeredWithin(unsigned long xms);
    
    // how many times it triggered since last time we checked by calling currentTriggers
    unsigned long currentTriggers();
    
    int activate();
    
    int deactivate();

    int trigCount() { return triggerCount; }
	
	int currentState() { return (gpioPin == -1) ? 0 : digitalRead(gpioPin); }
	
  private:
    void ARDUINO_ISR_ATTR isr() { triggerCount++; trigTime = millis(); }
    int gpioPin;
	int isRisingEdge;
    unsigned long triggerCount;
    unsigned long trigTime;
    unsigned long lastReadTriggerCount; // trigger count last time we checked
};
