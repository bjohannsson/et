#include <EEPROM.h>
#include "PacketSerial.h"
#include "Arduino.h"
#include "core.h"


//bool ledOn = false;
void toggleLed() {
  if (ledOn) {
    digitalWrite(LED, LOW);
    ledOn = false;
  }
  else
  {
    digitalWrite(LED, HIGH);
    ledOn = true;
  }
}
