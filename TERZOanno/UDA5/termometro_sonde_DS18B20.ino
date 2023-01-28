/*



// Sonda termometro DS18B20


#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(8);
DallasTemperature temp(&oneWire);

float tc = 0;
float tf = 0;


void setup(void) {
  Serial.begin(9600);
  temp.begin();
}


void loop(void) { 
  temp.requestTemperatures(); 
  tc = temp.getTempCByIndex(0);
  tf = temp.toFahrenheit(tc);
  Serial.print(" T = ");
  Serial.print(tc);
  Serial.print(" °C ");
  Serial.print(" = ");
  Serial.print(tf);
  Serial.println(" °F ");
  delay(1000);
}


// Fonte Aliverti https://www.youtube.com/watch?v=FK-Kb_X2sA8


*/









// Sonde multiple termometro DS18B20

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(8);
DallasTemperature temp(&oneWire);

float tc = 0;
float tf = 0;

int nsonde = 0;

void setup(void) {
  Serial.begin(9600);
  temp.begin();
  nsonde = temp.getDeviceCount();
  Serial.print("Numero totale di sonde: ");
  Serial.println(nsonde);
  Serial.println(" ");
}

void loop(void) { 
  
  temp.requestTemperatures(); 
  for (int i = 0; i < nsonde; i++) {
    Serial.print("Sonda n°");
    Serial.println(i+1);
    tc = temp.getTempCByIndex(i);
    tf = temp.toFahrenheit(tc);
    Serial.print(" T = ");
    Serial.print(tc);
    Serial.print(" °C ");
    Serial.print(" = ");
    Serial.print(tf);
    Serial.println(" °F "); 
  }
  Serial.println("---");
  delay(1000);
}


// Fonte Aliverti https://www.youtube.com/watch?v=1bzECKUhuWA

// Test di gennaio 2023: usate 4 sonde in acqua a 19,5 °C circa ognuna,
//                       con breadboard a 4,7 Ohm di resistenza
//                       groviglio di cavi... Ma ok


