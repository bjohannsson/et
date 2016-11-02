#include <EEPROM.h>
#include "PacketSerial.h"
#include "Arduino.h"
#include "core.h"

//Timer 1 interrupt service routine
ISR(TIMER1_OVF_vect)
{

 long time = millis();

 switch(Command)
 {

  case MOVEFORWARDTIME:
  case TURNLEFT:
  case TURNRIGHT:
  case MOVEBACKTIME: if((millis() - tempMovementTime) >= movementTime)
                      {
                        stopMotors();
                        Command = NOCOMMAND;
                      }
                     break;
 }

 TCNT1 = TIMER1COUNT;
}

//Move forward
void moveForward()
{
  digitalWrite(MOTOR_LEFT_P,LOW);
  digitalWrite(MOTOR_LEFT_N,HIGH);
  digitalWrite(MOTOR_RIGHT_P,HIGH);
  digitalWrite(MOTOR_RIGHT_N,LOW);
}

//Stop movement
void stopMotors()
{
  digitalWrite(MOTOR_LEFT_P,LOW);
  digitalWrite(MOTOR_LEFT_N,LOW);
  digitalWrite(MOTOR_RIGHT_P,LOW);
  digitalWrite(MOTOR_RIGHT_N,LOW);
  tempMovementTime = 0;
}

//Move forward for specific time (in seconds)
void moveForwardForTime(char *data)
{
  moveForward();
  movementTime = *data*1000;
  tempMovementTime = millis();
}

//Move back for specific time (in seconds)
void moveBackForTime(char *data)
{
  moveBack();
  movementTime = *data*1000;
  tempMovementTime = millis();
}

//Move back
void moveBack()
{
  digitalWrite(MOTOR_LEFT_P,HIGH);
  digitalWrite(MOTOR_LEFT_N,LOW);
  digitalWrite(MOTOR_RIGHT_P,LOW);
  digitalWrite(MOTOR_RIGHT_N,HIGH);
}

//Turn left for specific time (in seconds)
void turnLeft(char *data)
{
  digitalWrite(MOTOR_LEFT_P,LOW);
  digitalWrite(MOTOR_LEFT_N,HIGH);
  digitalWrite(MOTOR_RIGHT_P,LOW);
  digitalWrite(MOTOR_RIGHT_N,LOW);
  movementTime = *data*1000;
  tempMovementTime = millis();
}

//Turn right for specific time (in seconds)
void turnRight(char *data)
{
  digitalWrite(MOTOR_LEFT_P,LOW);
  digitalWrite(MOTOR_LEFT_N,LOW);
  digitalWrite(MOTOR_RIGHT_P,HIGH);
  digitalWrite(MOTOR_RIGHT_N,LOW);
  movementTime = *data*1000;
  tempMovementTime = millis();
}
