// ESPERIMENTO onda sinusoidale
// Testato giugno 2021, ok con oscilloscopio, screenshot su Dropbox
// esce onda con bassa frequenza 1,60 Hz e 0,430 Vpp se manteniamo serial print
// senza serial print esce a 24 Hz e 0,412 Vpp però ho messo limite banda 20 MHz per togliere rumore


// Per vedere l'onda su PC con Plotter Seriale il terminale OUT del modulo va sul pin analogico A0 
// Altrimenti usare oscilloscopio. Col dso138 si vede direi bene


#include "Wire.h"
#define PCF8591 (0x90 >> 1) // I2C bus address

uint8_t onda[128] = {
0x64,0x69,0x6e,0x73,0x78,0x7c,0x81,0x86,
0x8a,0x8f,0x93,0x97,0x9c,0xa0,0xa3,0xa7,
0xab,0xae,0xb1,0xb4,0xb7,0xba,0xbc,0xbe,
0xc0,0xc2,0xc4,0xc5,0xc6,0xc7,0xc8,0xc8,
0xc8,0xc8,0xc8,0xc7,0xc6,0xc5,0xc4,0xc2,
0xc0,0xbe,0xbc,0xba,0xb7,0xb4,0xb1,0xae,
0xab,0xa7,0xa3,0xa0,0x9c,0x97,0x93,0x8f,
0x8a,0x86,0x81,0x7c,0x78,0x73,0x6e,0x69,
0x64,0x5f,0x5a,0x55,0x50,0x4c,0x47,0x42,
0x3e,0x39,0x35,0x31,0x2c,0x28,0x25,0x21,
0x1d,0x1a,0x17,0x14,0x11,0xe,0xc,0xa,
0x8,0x6,0x4,0x3,0x2,0x1,0x0,0x0,
0x0,0x0,0x0,0x1,0x2,0x3,0x4,0x6,
0x8,0xa,0xc,0xe,0x11,0x14,0x17,0x1a,
0x1d,0x21,0x25,0x28,0x2c,0x31,0x35,0x39,
0x3e,0x42,0x47,0x4c,0x50,0x55,0x5a,0x5f
};


void setup(){
  Wire.begin();
  //Serial.begin(9600);
}


void loop(){
  for (int i=0; i<128; i++){
    Wire.beginTransmission(PCF8591); // wake up PCF8591
    Wire.write(0x40); // control byte - turn on DAC (binary 1000000)
    Wire.write(onda[i]);   // Valori inviati al DAC
    Wire.endTransmission(); // end tranmission
  //  int x = analogRead(0);
//    Serial.println(x);
  }
}


// Fonte https://tronixstuff.com/2013/06/17/tutorial-arduino-and-pcf8591-adc-dac-ic/
//       poi modificata con https://daycounter.com/Calculators/Sine-Generator-Calculator.phtml










/*

// Esperimento: GENERATORE DI ONDA TRIANGOLARE

// Modulo con chip PCF8591 - Convertitore analogico digitale DAC (Vcc = +5V) 

// Per vedere l'onda su PC con Plotter Seriale il terminale OUT del modulo va sul pin analogico A0 
// Altrimenti usare oscilloscopio


#include "Wire.h"
#define PCF8591 (0x48 >> 1) // I2C bus address


void setup(){
  //Serial.begin(9600);
  Wire.begin();
}


void loop(){
  int x;
  for (int i=0; i<200; i++){
    Wire.beginTransmission(PCF8591); // wake up PCF8591
    Wire.write(0x40); // control byte - turn on DAC (binary 1000000)
    Wire.write(100*i); // value to send to DAC
    Wire.endTransmission(); // end tranmission
    x = analogRead(0);
    //Serial.println(x);
  }

  for (int i=199; i>=0; --i){
    Wire.beginTransmission(PCF8591); // wake up PCF8591
    Wire.write(0x40); // control byte - turn on DAC (binary 1000000)
    Wire.write(100*i); // value to send to DAC
    Wire.endTransmission(); // end tranmission
    x = analogRead(0);
    //Serial.println(x);
  }
}


// Fonte https://tronixstuff.com/2013/06/17/tutorial-arduino-and-pcf8591-adc-dac-ic/

*/









/*

// Modulo PCF8591 usato per conversione da analogico a digitale

// Lettura da fotoresistore, da termistore o da trimmer o da altro sensore analogico

#include "Wire.h"
#define PCF8591 (0x90 >> 1) // I2C bus address
#define ADC0 0x70  // fotoresistore; invece di 00
#define ADC1 0x60  // termistore; invece di 01
#define ADC2 0x02  // altro sensore
#define ADC3 0x50  // trimmer; invece di 03
byte value0, value1, value2, value3;


void setup(){
  Wire.begin();
  Serial.begin(9600);
}


void loop(){
  Wire.beginTransmission(PCF8591); // wake up PCF8591
  Wire.write(ADC0); // control byte - read ADC0
  Wire.endTransmission(); // end tranmission
  Wire.requestFrom(PCF8591, 2);
  value0=Wire.read();
  value0=Wire.read();
  Wire.beginTransmission(PCF8591); // wake up PCF8591
  Wire.write(ADC1); // control byte - read ADC1
  Wire.endTransmission(); // end tranmission
  Wire.requestFrom(PCF8591, 2);
  value1=Wire.read();
  value1=Wire.read();
  Wire.beginTransmission(PCF8591); // wake up PCF8591
  Wire.write(ADC2); // control byte - read ADC2
  Wire.endTransmission(); // end tranmission
  Wire.requestFrom(PCF8591, 2);
  value2=Wire.read();
  value2=Wire.read();
  Wire.beginTransmission(PCF8591); // wake up PCF8591
  Wire.write(ADC3); // control byte - read ADC3
  Wire.endTransmission(); // end tranmission
  Wire.requestFrom(PCF8591, 2);
  value3=Wire.read();
  value3=Wire.read();
  Serial.print(value0); Serial.print(" ");
  Serial.print(value1); Serial.print(" ");
  Serial.print(value2); Serial.print(" ");
  Serial.print(value3); Serial.print(" ");
  Serial.println();
} 

// Fonte https://tronixstuff.com/2013/06/17/tutorial-arduino-and-pcf8591-adc-dac-ic/
// poi modificata con indicazioni trovate sul web per gli indirizzi corretti

*/











/*

// Presumo Modulo PCF8591 usato per conversione da analogico a digitale

// Example 52.4 PCF8591 ADC demo
// http://tronixstuff.com/tutorials Chapter 52
// John Boxall June 2013
#include "Wire.h"
#define PCF8591 (0x90 >> 1) // I2C bus address
byte value0, value1, value2, value3;
void setup()
{
 Wire.begin();
 Serial.begin(9600);
}
void loop()
{
 Wire.beginTransmission(PCF8591); // wake up PCF8591
 Wire.write(0x04); // control byte - read ADC0 then auto-increment
 Wire.endTransmission(); // end tranmission
 Wire.requestFrom(PCF8591, 5);
 value0=Wire.read();
 value0=Wire.read();
 value1=Wire.read();
 value2=Wire.read();
 value3=Wire.read();
 Serial.print(value0); Serial.print(" ");
 Serial.print(value1); Serial.print(" ");
 Serial.print(value2); Serial.print(" ");
 Serial.print(value3); Serial.print(" ");
 Serial.println();
}

*/
