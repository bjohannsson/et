#include <EEPROM.h>
#include "PacketSerial.h"
#include "Arduino.h"
#include "core.h"




//Handle commands. USER CAN ADD MODE COMMANDS IF NECESSARY
void handleCommands(char src, char dst, char internal, char tcp, char fwd, char counterH, char counterL, char datalen, char command, char *data)
{

    char tempData[32] = {0};
    data = data + 1;

    switch(command)
    {
      case MOVEFORWARD : Command = MOVEFORWARD;
                         moveForward();
                         break;

      case MOVEFORWARDTIME: Command = MOVEFORWARDTIME;
                            moveForwardForTime(data);
                            break;

      case MOVEBACK: Command = MOVEBACK;
                     moveBack();
                     break;

      case MOVEBACKTIME: Command = MOVEBACKTIME;
                         moveBackForTime(data);
                         break;

      case STOP: Command = STOP;
                 stopMotors();
                 break;

      case TURNLEFT: Command = TURNLEFT;
                     turnLeft(data);
                     break;

      case TURNRIGHT: Command = TURNRIGHT;
                      turnRight(data);
                      break;

      case DISTANCEFRONT: distance = getDistanceFront();
                          if(distance > 254)
                          {
                           distance = 254;
                          }
                          tempData[0] = command;
                          tempData[1] = distance & 0xFF;
                          tempData[2] = 0;
                          sendPacket(dst, src, internal, tcp, ACK, counterH, counterL, 2, tempData);
                          break;
//
//      case DISTANCELEFT: distance = getDistanceLeft();
//                         if(distance > 254)
//                         {
//                          distance = 254;
//                         }
//                         tempData[0] = command;
//                         tempData[1] = distance & 0xFF;
//                         tempData[2] = 0;
//                         sendPacket(dst, src, internal, tcp, ACK, counterH, counterL, 2, tempData);
//                         break;

      case DISTANCERIGHT: distance = getDistanceRight();
                          if(distance > 254)
                          {
                           distance = 254;
                          }
                          tempData[0] = command;
                          tempData[1] = distance & 0xFF;
                          tempData[2] = 0;
                          sendPacket(dst, src, internal, tcp, ACK, counterH, counterL, 2, tempData);
                          break;

      case GETMGN: break;

      case GETID: nodeID = getID();
                  tempData[0] = command;
                  tempData[1] = nodeID;
                  sendPacket(dst, src, internal, tcp, ACK, counterH, counterL, 2, tempData);
                  break;

      case FORWARD_COMMAND:
        Command = FORWARD_COMMAND;
         if (nodeID==server){
          CreatePacket(nodeID, slave, ADHOC, 3, testData);
         }
         break;

      case SEND_VALUE:
        Command = SEND_VALUE;
        rData = (*data << 8 ) | (*(data+1)); // received value
        break;

    }
  }



void initGPIO()
{
 pinMode(ULTRASONIC_FRONT_TRIGGER, OUTPUT);
 pinMode(ULTRASONIC_LEFT_TRIGGER, OUTPUT);
 pinMode(ULTRASONIC_RIGHT_TRIGGER, OUTPUT);
 pinMode(ULTRASONIC_FRONT_ECHO, INPUT);
// pinMode(ULTRASONIC_LEFT_ECHO, INPUT);
 pinMode(ULTRASONIC_RIGHT_ECHO, INPUT);

 pinMode(MOTOR_RIGHT_P, OUTPUT);
 pinMode(MOTOR_RIGHT_N, OUTPUT);
 pinMode(MOTOR_LEFT_P, OUTPUT);
 pinMode(MOTOR_LEFT_N, OUTPUT);

 pinMode(LED, OUTPUT);

 stopMotors();
}


void initTimer()
{
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = TIMER1COUNT;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}




//Get RSSI from ESP8266
/*
 * Get RSSI from ESP8266 with internal command INT_RSSI. ^M
 * Once ESP8266 reads its RSSI, it replies to Arduino with ^M
 * internal command "INT_RSSI". Reception of RSSI is handled ^M
 * in onPacket function^M
 */

void getRSSI()
{
  char data[1];
  sendPacket(nodeID, nodeID, INT_RSSI, TCP, FWD, 0, 0, 0, data);
  //RSSI value is updated in RSS_Value variable as soon as there is reply from ESP8266. This is implemented in OnPacket() function
}

//This is internal API used to enable demo mode in ESP8266. Demo mode should be enabled in all the robots to make it work
void enableDemo()
{
  char data[1];
  sendPacket(nodeID, nodeID, INT_DEMO , TCP, FWD, 0, 0, 0, data);
}

//Get ID of robot
char getID()
{
  return EEPROM.read(ADDRESS);
}

//Set ID of robot
void setID(char ID)
{
  EEPROM.write(ADDRESS, ID);
  delay(50);
  nodeID = getID();
}

//Send ID of robot to ESP8266
void sendID()
{
  nodeID = getID();
  sendPacket(nodeID,nodeID,INT_ID,TCP,FWD,0,0,1,&nodeID);
}

//Send connection matrix to ESP8266
void sendMatrix()
{
  nodeID = getID();
  sendPacket(nodeID,nodeID,INT_MATRIX,TCP,FWD,0,0,NODECOUNT,(char*)matrix[nodeID-1]);
}

//Send IP address of server to ESP8266
void sendIP()
{
  sendPacket(nodeID,nodeID,INT_IP,TCP,FWD,0,0,sizeof(ip),ip);
}

//Send AP SSID and password to ESP8266
void sendSSIDandPassword()
{
  char *ssid_pwd = (char*)calloc(strlen(ssid)+strlen(password)+2,sizeof(char));
  strcpy(ssid_pwd,ssid);
  int delimiterLoc = strlen(ssid);
  ssid_pwd[delimiterLoc] = 0xA9;
  strcat(ssid_pwd,password);
  sendPacket(nodeID,nodeID,INT_SSID_PWD,TCP,FWD,0,0,strlen(ssid_pwd),ssid_pwd);
  free(ssid_pwd);
}

//This function is called when data is received from serial port (from PacketSerial library)
void onPacket(const uint8_t* buffer, size_t size)
{
  unsigned char src, dst, internal, tcp, fwd, counterH, counterL, datalen, command, *data;
  nodeID = getID();
  if((buffer[0] != STARTBYTE))
  {
    return;
  }
  src = (buffer[1] >> 4) & 0x0F;
  dst = buffer[1] & 0x0F;
  internal = (buffer[3] >> 5) & 0x07;
  tcp = (buffer[3] >> 4) & 0x01;
  fwd = (buffer[3] >> 3) & 0x01;
  counterH = buffer[4];
  counterL = buffer[5];
  datalen = buffer[6];
  command = buffer[7];
  data = (buffer + 7);
  // Checksum is not calculated. Can be implemented if necessary

//  if (*data == 0x30) {
//    toggleLed();
//  }

  //Check if the command is internal, especially get RSSI from ESP8266
  if(internal == INT_RSSI)
  {
    if(datalen != 4)
    {
      return;
    }
    //Update RSSI_Value variable with hlatest RSSI
    RSSI_Value = (buffer[7] << 24) | (buffer[8] << 16) | (buffer[9] << 8) | (buffer[10]);

  }

  //Call callback function
  OnReceive(src, dst, internal, tcp, fwd, counterH, counterL, datalen, command, data);
}

//For internal use only
void sendPacket(char src, char dst, char internal, char isTCP, char isACK, char counterHigh, char counterLow, char dataLength, char *data)
{
 char packet[PACKETSIZE] = {0};
 int index = 0;
 char checksum = 0;
 nodeID = getID();

 packet[0] = STARTBYTE;
 packet[1] = (src<<4) | (dst & 0x0F);
 packet[2] = nodeID << 4;
 packet[3] = (internal << 5) | (isTCP << 4) | (isACK << 3);
 packet[4] = counterHigh;
 packet[5] = counterLow;
 packet[6] = dataLength;
 for(index=0; index<dataLength; index++)
 {
  packet[7+index] = data[index];
 }
// packet[7+index] = checksum;  // Checksum is not calculated. Can be implemented if necessary
 packetSerial.send(packet,7+index);
}




/** USER FUNCTION FOR AD-HOC NETWORKS COURSE. Create function and send over WiFi network
src -> ID of robot. Send nodeID variable here (This is don't care for TCP packet)
dst -> ID of robot to which you want to send the packet (This is don't care for TCP packet)
isTCP -> Set with macro TCP or ADHOC depending where you want to send
dataLength -> Length of data
data -> Data that has to be sent. The first byte is COMMAND and subsequent bytes are arguments
**/
void CreatePacket(char src, char dst, char isTCP, char dataLength, char *data)
{
  PacketCounter++;
  char counterLow = PacketCounter & 0xFF;
  char counterHigh = (PacketCounter >> 8) & 0xFF;
  sendPacket(src, dst, 0x00, isTCP, FWD, counterHigh, counterLow, dataLength, data);

}

/** USER FUNCTION FOR AD-HOC NETWORKS COURSE. This function is called when a packet is received from TCP or AD-HOC node
//void onPacket(const uint8_t* buffer, size_t size) calls this function after parsing the packet.
**/
void OnReceive(char src, char dst, char internal, char tcp, char fwd, char counterH, char counterL, char datalen, char command, char *data)
{

  //Execute commands if the command is from TCP OR if ID is equal to destination (in Ad-hoc mode)
  if(tcp == TCP || ((tcp == ADHOC) && (nodeID == dst)))
  {
      handleCommands(src, dst, internal, tcp, fwd, counterH, counterL, datalen, command, data);
  }
}
