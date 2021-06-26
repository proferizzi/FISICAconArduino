
// ESPERIMENTO: onda triangolare e misure manuali  
// Testato giugno 2021, ok con oscilloscopio, screenshots su Dropbox
// esce onda con bassa frequenza 765 mHz e 4,84 Vpp


#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;


void setup(void) {
  //Serial.begin(9600);
  dac.begin(0x60);  // 61 o 60 
  //Serial.println("Generating a triangle wave");
}


void loop(void) {
  uint32_t counter;
  // Run through the full 12-bit scale for a triangle wave
  for (counter = 0; counter < 4095; counter++){
    dac.setVoltage(counter, false);
    //Serial.println(analogRead(A0));
  }
  for (counter = 4095; counter > 0; counter--){
    dac.setVoltage(counter, false);
    //Serial.println(analogRead(A0));
  }
}


// Fonte esempio da libreria Adafruit, usato anche da Aliverti









/*
// i2c_scanner

#include <Wire.h>
    
void setup(){
  Wire.begin();
  Serial.begin(9600);
  while(!Serial);             
  Serial.println("\nI2C Scanner");
}
    
void loop(){
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");   
  nDevices = 0;
  for(address = 1; address < 127; address++ ){
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
      Serial.print("I2C device found at address 0x");
      if (address<16) Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    }else if (error==4){
          Serial.print("Unknown error at address 0x");
          if (address<16) Serial.print("0");
          Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)  Serial.println("No I2C devices found\n");
  else Serial.println("done\n");
  delay(5000);           // wait 5 seconds for next scan
}

*/





