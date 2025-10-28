

// TERMOMETRO DS18B20 con LCD1602 - testato ok

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(5);
DallasTemperature temp(&oneWire);

float tc = 0;
float tf = 0;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup(void) {
  Serial.begin(9600);
  temp.begin();
  pinMode(16,OUTPUT);  // pin analogico A2
  digitalWrite(16,LOW);
  pinMode(17,OUTPUT);  // pin analogico 
  digitalWrite(17,HIGH);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}


void loop(void) { 
  temp.requestTemperatures(); 
  tc = temp.getTempCByIndex(0);
  tf = temp.toFahrenheit(tc);
  lcd.setCursor(0,0);
  lcd.print(tc);
  lcd.print(" gradi C");
  lcd.setCursor(0,1);
  lcd.print(tf);
  lcd.print(" gradi F");
  delay(2000);
  lcd.clear();
}


// Fonte per SENSORE corso Aliverti #278
// e per le librerie https://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html
// mentre quella di milesburton su Linux non va
// Fonte per LCD commento in corso Aliverti 219, diverso dallo sketch
// ecco qui http://scienceclub.org.au/download/1602-lcd-display-serial-connection-arduino-library/
// Inoltre: modifica mia per VCC e GND su pin analogici, non dimenticare i2cscanner.ino
