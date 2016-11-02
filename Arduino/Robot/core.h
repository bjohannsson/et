#ifndef CORE_H
#define CORE_H

#include <EEPROM.h>
#include "PacketSerial.h"
#include "Arduino.h"

#define STARTBYTE 0xFF
#define PACKETSIZE 254
#define MINPACKET 8
#define TCP 1
#define ADHOC 0
#define FWD 0
#define ACK 1
#define ADDRESS 0
#define MOTOR_RIGHT_P  9
#define MOTOR_RIGHT_N  10
#define MOTOR_LEFT_P  3
#define MOTOR_LEFT_N  11
#define ULTRASONIC_FRONT_TRIGGER   4
#define ULTRASONIC_LEFT_TRIGGER   12
#define ULTRASONIC_RIGHT_TRIGGER   7
#define ULTRASONIC_FRONT_ECHO   5
//#define ULTRASONIC_LEFT_ECHO   13
#define LED 13
#define ULTRASONIC_RIGHT_ECHO   2
#define TIMER1COUNT 64286  //50Hz
#define TIMER2COUNT 255

#define VERYQUICK 30
#define QUICK 60
#define MEDIUM  720
#define LONG  1440


//External commands, communicated with another robot (in Adhoc mode) or TCP
#define NOCOMMAND 0
#define MOVEFORWARD 0x01
#define MOVEFORWARDTIME 0x02
#define MOVEBACK 0x03
#define MOVEBACKTIME 0x04
#define TURNLEFT 0x05
#define TURNRIGHT 0x06
#define STOP 0x07
#define DISTANCELEFT 0x08
#define DISTANCERIGHT 0x09
#define DISTANCEFRONT 0x0A
#define TARGET_RSSI 0x0B
//#define FORWARD_COMMAND 0x0C
#define GETMGN 0x0D
#define GETID 0x0F

//Internal commands, communicated with ESP8266
#define INT_ID 0x01
#define INT_SSID_PWD 0x02
#define INT_MATRIX 0x03
#define INT_RSSI 0x04
#define INT_IP 0x05
#define INT_DEMO 0x06

#define NODECOUNT 12
char matrix[NODECOUNT][NODECOUNT]={{0,1,0,0,1,0,0,1,0,0,1,0},
                                   {1,0,1,1,0,0,1,0,0,1,0,0},
                                   {0,1,0,0,0,1,0,1,0,0,0,1},
                                   {0,1,0,0,1,0,0,1,0,0,0,1},
                                   {1,0,0,1,0,1,1,0,0,0,1,0},
                                   {0,0,1,0,1,0,0,0,1,0,0,1},
                                   {1,0,0,0,0,1,0,1,0,1,0,0},
                                   {0,1,0,0,1,0,1,0,1,0,0,1},
                                   {0,0,1,0,0,1,0,1,0,0,1,0},
                                   {1,0,0,1,0,0,1,0,0,0,1,0},
                                   {1,0,0,0,1,0,0,0,1,1,0,1},
                                   {0,1,0,1,0,1,0,1,0,0,1,0}};
//char ssid[] = "wifi_ssid";
//char password[] = "password";
//char ip[] = {192,168,43,193};


char ssid[] = "G2_7354";
char password[] = "87654321";
char ip[] = {192,168,43,70};

int targetRSSI = 0;
char slave = 12;
char server = 11;
char master = 10;
bool ledOn = false;
uint16_t tim2Counter = 0;
uint16_t ledSpeed = LONG;

char testData[3];

//char rData = 0x00;
int16_t rData = 0;

char tData = MOVEFORWARD;


char Command = 0;
long Rssi = 0;
unsigned long distance = 0;

char nodeID = 0;
unsigned long movementTime = 0;
unsigned long tempMovementTime = 0;

uint16_t PacketCounter = 0;
long RSSI_Value = 0;

PacketSerial packetSerial;






#endif
