#include <EEPROM.h>
#include "PacketSerial.h"
#include "Arduino.h"
#include "core.h"


//Get distance in cm from front ultrasonic sensor (In blocking mode)
unsigned long getDistanceFront()
{
 digitalWrite(ULTRASONIC_FRONT_TRIGGER, LOW);
 delayMicroseconds(2);

 digitalWrite(ULTRASONIC_FRONT_TRIGGER, HIGH);
 delayMicroseconds(10);

 digitalWrite(ULTRASONIC_FRONT_TRIGGER, LOW);
 long duration = pulseIn(ULTRASONIC_FRONT_ECHO, HIGH);

 return duration/58.2;
}

//Get distance from left ultrasonic sensor (In blocking mode)
//unsigned long getDistanceLeft()
//{
// digitalWrite(ULTRASONIC_LEFT_TRIGGER, LOW);
// delayMicroseconds(2);
//
// digitalWrite(ULTRASONIC_LEFT_TRIGGER, HIGH);
// delayMicroseconds(10);
//
// digitalWrite(ULTRASONIC_LEFT_TRIGGER, LOW);
// long duration = pulseIn(ULTRASONIC_LEFT_ECHO, HIGH);
//
// return duration/58.2;
//}

//Get distance from right ultrasonic sensor (In blocking mode)
unsigned long getDistanceRight()
{
 digitalWrite(ULTRASONIC_RIGHT_TRIGGER, LOW);
 delayMicroseconds(2);

 digitalWrite(ULTRASONIC_RIGHT_TRIGGER, HIGH);
 delayMicroseconds(10);

 digitalWrite(ULTRASONIC_RIGHT_TRIGGER, LOW);
 long duration = pulseIn(ULTRASONIC_RIGHT_ECHO, HIGH);

 return duration/58.2;
}
