

// Legge la configurazione  N.B. mettere su 3,3 V i due jumper di M0 e M1

#include "Arduino.h"
#include "LoRa_E32.h"

LoRa_E32 e32ttl100(3, 2); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);

void setup() {
  Serial.begin(9600);
  delay(500);

  // Startup all pins and UART
  e32ttl100.begin();

  ResponseStructContainer c;
  c = e32ttl100.getConfiguration();
  // It's important get configuration pointer before all other operation
  Configuration configuration = *(Configuration*) c.data;
  Serial.println(c.status.getResponseDescription());
  Serial.println(c.status.code);

  printParameters(configuration);

  ResponseStructContainer cMi;
  cMi = e32ttl100.getModuleInformation();
  // It's important get information pointer before all other operation
  ModuleInformation mi = *(ModuleInformation*)cMi.data;

  Serial.println(cMi.status.getResponseDescription());
  Serial.println(cMi.status.code);

  printModuleInformation(mi);

  c.close();
  cMi.close();
}

void loop() {

}
void printParameters(struct Configuration configuration) {
  Serial.println("----------------------------------------");

  Serial.print(F("HEAD BIN: "));  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
  Serial.println(F(" "));
  Serial.print(F("AddH BIN: "));  Serial.println(configuration.ADDH, DEC);
  Serial.print(F("AddL BIN: "));  Serial.println(configuration.ADDL, DEC);
  Serial.print(F("Chan BIN: "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
  Serial.println(F(" "));
  Serial.print(F("SpeedParityBit BIN    : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
  Serial.print(F("SpeedUARTDataRate BIN : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
  Serial.print(F("SpeedAirDataRate BIN  : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());

  Serial.print(F("OptionTrans BIN       : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
  Serial.print(F("OptionPullup BIN      : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
  Serial.print(F("OptionWakeup BIN      : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
  Serial.print(F("OptionFEC BIN         : "));  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
  Serial.print(F("OptionPower BIN       : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());

  Serial.println("----------------------------------------");

}
void printModuleInformation(struct ModuleInformation moduleInformation) {
  Serial.println("----------------------------------------");
  Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);

  Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
  Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
  Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
  Serial.println("----------------------------------------");

}



// Fonte Aliverti https://github.com/zmaker/arduino_cookbook/blob/42e6575560c91528fc52b95cf95c65c95019a244/551-Lora_teoria/A551-LORA.pdf
//                https://www.youtube.com/watch?v=_eCTdPFvZsc
//                https://www.youtube.com/watch?v=6O2C53QfySY
// Fonte libreria Mischianti  https://www.mischianti.org/2019/10/29/lora-e32-device-for-arduino-esp32-or-esp8266-configuration-part-3







/*

// Ripristina le condizioni di fabbrica  N.B. mettere su 3,3 V i due jumper di M0 e M1

#include "Arduino.h"
#include "LoRa_E32.h"
 
SoftwareSerial mySerial(3, 2); // e32 TX e32 RX
 
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
  delay(500);

  //Factory reset - MO e M1 su H
  byte buf[] = { 0xC0, 0x00, 0x00, 0x1A, 0x06, 0x44 };
  mySerial.write((uint8_t *)buf, 6);
  delay(500);
    
  Serial.println("Factory Reset!");  
}
 
void loop() {
  if (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);
  }
  
}




// Fonte Aliverti https://github.com/zmaker/arduino_cookbook/blob/42e6575560c91528fc52b95cf95c65c95019a244/551-Lora_teoria/A551-LORA.pdf
//                https://www.youtube.com/watch?v=_eCTdPFvZsc
//                https://www.youtube.com/watch?v=6O2C53QfySY
// Fonte libreria Mischianti  https://www.mischianti.org/2019/10/29/lora-e32-device-for-arduino-esp32-or-esp8266-configuration-part-3

*/
