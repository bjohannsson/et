#include <EEPROM.h>
#include "PacketSerial.h"
#include "core.h"



//Initial setup
void setup()
{
//setID(0x0A);
nodeID = getID();
packetSerial.setPacketHandler(&onPacket);
packetSerial.begin(9600);
initGPIO();
initTimer();
delay(1000);
sendID();
delay(1000);
sendMatrix();
delay(1000);
sendIP();
delay(1000);
sendSSIDandPassword();

testData[0] = MOVEBACKTIME;
testData[1] = 0x30;
testData[2] = 0x01;


}


uint32_t startCounter = 0;
bool isConnected = false;


void loop()
{
//  while(startCounter <= 5000) {
//    packetSerial.update();
//    delay(1);
//    startCounter ++;
//  }
  
  packetSerial.update();
  
//  if (nodeID==server){
//    CreatePacket(nodeID, slave, ADHOC, 2, testData);
//  }
  if (rData == 12289)
  {
    digitalWrite(LED, HIGH);
  }


}


