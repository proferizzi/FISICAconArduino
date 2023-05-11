/*

// TERMOMETRO DS18B20 - testato ok

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
  Serial.print(" C  ");
  Serial.print(tc);
  Serial.print(" F  ");
  Serial.println(tf);
  delay(1000);
}

// Fonte corso Aliverti #278
// e per le librerie https://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html
// mentre quella di milesburton su Linux non va

*/







/*

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
  
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  //lcd.print("Hello, world!");
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
  delay(500);
}


// Fonte per SENSORE corso Aliverti #278
// e per le librerie https://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html
// mentre quella di milesburton su Linux non va
// Fonte per LCD commento in corso Aliverti 219, diverso dallo sketch
// ecco qui http://scienceclub.org.au/download/1602-lcd-display-serial-connection-arduino-library/
// Inoltre: modifica mia per VCC e GND su pin analogici, non dimenticare i2cscanner.ino

*/





















/*

// da testare


// TMP36
int val_Adc = 0;
float temp = 0;
 
void setup() {
   // init seriale
   Serial.begin(9600);
   // utilizzando l'istruzione analogReference indico al convertitore AD che deve impiegare
   // la tensione presente sul pin AREF come valore di riferimento per la conversione
   analogReference(EXTERNAL);
}
 
void loop() {
   // ritardo di mezzo secondo
   delay(500);
   // init variabile
   val_Adc = 0;
   // eseguo un ciclo
   for(byte Ciclo = 0; Ciclo<100; Ciclo++) {
  // acquisisco il valore e lo sommo alla variabile
  val_Adc += analogRead(0);
  // questo ritardo serve per dare il tempo all' ADC di eseguire correttamente
  // la prossima acquisizione
  delay(10);
  }
  // eseguo la media dei 100 valori letti
   val_Adc /= 100;
   // calcolo la temperatura in °C
   temp = ((val_Adc * 0.0032) - 0.5) / 0.01;
   // invio i dati al computer
   Serial.println(temp);
}
// fonte Marco Lai: https://www.logicaprogrammabile.it/arduino-sensore-di-temperatura-tmp36/


*/








/*

// TMP36 termometro e serial monitor
int sensore=A0;
float val=0;
float temp=0;

void setup() {
  pinMode(sensore, INPUT);
  Serial.begin(9600);
}

void loop() {
  val=analogRead(sensore);
  Serial.print("Valore non convertito: ");
  Serial.println(val);
  delay(1000);
  temp= ((val*0.00488)-0.5)/0.01;
  Serial.print("Valore temperatura: ");
  Serial.print(temp);
  Serial.println(" gradi");
  delay(1000);
}

*/













/*

//  tmp36 termometro e display lcd i2c
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 3F oppure 27

const int sensore = A0;
float val=0;
float temp=0;

void setup() {
  lcd.begin(16, 2);  // initialize the lcd
  lcd.clear();
  
  pinMode(sensore, INPUT);
  //Serial.begin(9600);
}

void loop() {
  val = analogRead(sensore);
  //Serial.print("Valore non convertito: ");
  //Serial.println(val);
  delay(500);
  temp = ((val*0.00488)-0.5)/0.01;
  //Serial.print("Valore temperatura: ");
  //Serial.print(temp);
  //Serial.println(" gradi");
  //delay(100);
  
  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.print(" gradi C");
  //lcd.setCursor(6, 1);
  //lcd.print(temp2);
  delay(500);
  //lcd.clear();
}

*/











/*

// xxx non va

// termometri tm36 e ds18b20 e display lcd i2c
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 3F oppure 27

const int sensore = A0;
const int sensore2 = A0;
const int sensore3 = A0;
float val = 0;
float temp = 0;
float val2 = 0;
float temp2 = 0;
float val3 = 0;
float temp3 = 0;


#include <OneWire.h>
 
byte G_addr[10][8]; //qui memorizzo fino a 10 indirizzi
byte G_Devices; // variabile usata per tenere traccia del numero di sensori riconosciuti nel bus
OneWire ow(8); // inizializza il bus onewire sulla porta n°8 (se avete collegato i sensori su un'altro pin dovete modificare qui)
 
float GetTemp(OneWire *,byte *);
void PrintAddress(byte *);
void lookUpSensors();
int CheckSensor(byte *);


void setup() {
  lcd.begin(16, 2);  // initialize the lcd
  lcd.clear();
  
  pinMode(sensore, INPUT);
  pinMode(sensore2, INPUT);
  Serial.begin(9600);

  G_Devices=0;      // imposta a 0 il numero di sensori attualmente riconosciuti
  lookUpSensors(); // avvia la ricerca delle sonde di temperatura
}

void lookUpSensors()
{
byte address[8]; // questo array conterrà l'indirizzo locale dei sensori
 
Serial.print("--Ricerca avviata--"); // avvia la ricerca e lo scrive sulla porta seriale
 
while (ow.search(address)) // loop finchè trova nuovi dispositivi
{
// Se il primo byte dell'indirizzo è 0x10, si tratta di una sonda DS18S20
// il primo byte dell'indirizzo identifica il tipo di sensore
// se  0x10 è un DS18S20, se è 0x28 è un DS18B20 (notare la S e B)
if (address[0] == 0x10 || address[0] == 0x28)
{
if(CheckSensor(address)==1) //crc ok
{
Serial.println("");
if (address[0] == 0x10) Serial.print("Found DS18S20 : "); // notare che la S invece che la B
else if (address[0] == 0x28) Serial.print("Found DS18B20 : ");
PrintAddress(address);
for(int aa=0;aa<8;aa++) G_addr[G_Devices][aa]=address[aa]; // copia l'indirizzo
G_Devices++; // incrementa il numero di devices memorizzati
}
}
 
}//end while
Serial.println("");
Serial.println("--Ricerca terminata--");
}

void loop(void){
  val = analogRead(sensore);
  val2 = analogRead(sensore2);
  val3 = analogRead(sensore3);
  //Serial.print("Valore non convertito: ");
  //Serial.println(val);
  delay(500);
  temp = ((val*0.00488)-0.5)/0.01;
  temp2 = ((val2*0.00488)-0.5)/0.01;
  temp3 = ((val3*0.00488)-0.5)/0.01;
  //Serial.print("Valore temperatura: ");
  //Serial.print(temp);
  //Serial.println(" gradi");
  //delay(100);
  
  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.print("   gradi C");
  lcd.setCursor(0, 1);
  lcd.print(temp2);
  lcd.setCursor(10,1);
  lcd.print(temp3);
  delay(500);
  //lcd.clear();
float temperatura; // uso questa variabile per tenere la lettura della temperatura
for(int num=0;num<G_Devices;num++) // vado a leggere tutti i sensori registrati
{
temperatura=GetTemp(&G_addr[num][0]); // lego la temperatura
PrintAddress(G_addr[num]);
Serial.print(" -> ");
Serial.println(temperatura);
}
delay(5000); // aspetto 5 secondi prima di fare una nuova misurazione
}
 
float GetTemp(byte * addr)
{
byte present = 0;
byte data[12];
int i;
byte address[8];
for(i=0;i<8;i++) address[i]=*(addr+i); //copia l'indirizzo nella stringa locale
ow.reset();
ow.select(addr);
ow.write(0x44,1);         // start conversion, with parasite power on at the end
delay(1000);     // maybe 750ms is enough, maybe not
// we might do a ds.depower() here, but the reset will take care of it.
 
present = ow.reset();
 
ow.select(addr);
ow.write(0xBE);         // Read Scratchpad
 
for ( i = 0; i < 9; i++) data[i] = ow.read();// we need 9 bytes //Serial.print(data[i], HEX);
 
int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;
 
double result;
 
LowByte = data[0];
HighByte = data[1];
 
TReading = (HighByte << 8) + LowByte;
SignBit = TReading & 0x8000;  // test most sig bit
 
if (SignBit) TReading = (TReading ^ 0xffff) + 1; // 2's comp // negative
 
Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25
 
Whole = Tc_100 / 100;  // separate off the whole and fractional portions
Fract = Tc_100 % 100;
 
result = Whole;
result += ((double)Fract/100);
 
if(SignBit) result *= -1;
 
return result;
 
}
 
void PrintAddress(byte * address)
{
int i;
for (i=0;i<8;i++)
{
if (address[i] < 9) Serial.print("0");
Serial.print(address[i],HEX);
if (i<7) Serial.print("-");
}
}
 
int CheckSensor(byte * address)
{
if (OneWire::crc8(address, 7) != *(address+7)) return(-1);// faccio il controllo del CRC8, se fallito ritorno -1
else return(1); // cr8 OK, ritorno 1
}

// Fonte http://www.mcmajan.com/mcmajanwpr/blog/2012/10/07/arduino-e-sensore-1wire-ds18b20/

*/











/*

// sonda DS18B20 con possibilità di lettura su display Keypad LCD

#include <OneWire.h>
//#include <LiquidCrystal.h>
//#define BUTTON A0
int DS18B20_Pin = 2;
OneWire ds(DS18B20_Pin);
//LiquidCrystal lcd(8,9,4,5,6,7);
 
void setup(void) {
  Serial.begin(9600);
  //lcd.begin(16, 2);
  //lcd.setCursor(0,0);
  //lcd.print("  DS18B20 LCD  ");
  //lcd.setCursor(0,1);
  //lcd.print("temperatura");
  //delay( 3000 );
}
 
void loop(void) {
  float temperature = getTemp();
  Serial.println(temperature);
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("Temperatura:   ");
  //lcd.setCursor(0,1);
  //lcd.print(temperature);
  delay(1000); 
}
 
float getTemp(){
  // returns the temperature from one DS18B20 in DEG Celsius
  byte data[12];
  byte addr[8];
  if ( !ds.search(addr)) {
      // no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC non valido!");
      return -1000;
  }
  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device non riconosciuto");
      return -1000;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
  byte present = ds.reset();
  ds.select(addr);   
  ds.write(0xBE); // Read Scratchpad
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  ds.reset_search();
  byte MSB = data[1];
  byte LSB = data[0];
  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  return TemperatureSum;
}
// Fonte Mauro Alfieri: http://www.mauroalfieri.it/elettronica/ds18b20-temperatura-lcd.html

 */
 
 
 
 
 
 
 
 
 
 
 
/* 
 
// termometri 1 bmp, 2 mpu6050
// con display OLED

// librerie
#include <SPI.h>  
#include <Wire.h>  
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// OLED
#define OLED_MOSI   11  
#define OLED_CLK   12  
#define OLED_DC    9  
#define OLED_CS    8  
#define OLED_RESET 10  
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);  
#if (SSD1306_LCDHEIGHT != 64)  
#error ("Non corretto! Correggi Adafruit_SSD1306.h!");  
#endif  
      
// sensore 1 bmp i2c
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10
Adafruit_BMP280 bmp; 

// sensore 2 mpu6050
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


void setup() {
  Serial.begin(9600);
  
  // OLED
  display.begin(SSD1306_SWITCHCAPVCC);  // 3.3 V
  display.clearDisplay();  
  display.setTextColor(WHITE);  
  display.setTextSize(1);  
  display.setCursor(32,32);  
  display.println("Preparazione termometri gradi Celsius");  
  display.display();  
  
  // sensore 1 bmp
  //Serial.println(F("Preparazione termometri gradi Celsius"));
  if(!bmp.begin(0x76)) {  
    Serial.println(F("Non trovo il BMP!"));
    while (1);
  }
  
  // sensore 2 mpu6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

}
 
void loop() {
    // sensore 1 bmp T1
    Serial.print(F("T1="));
    Serial.print(bmp.readTemperature());
    Serial.print("_");
    //Serial.println(" *C");
    //Serial.print(F("Pressure = "));
    //Serial.print(bmp.readPressure());
    //Serial.println(" Pa");
    //Serial.print(F("Approx altitude = "));
    //Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
    //Serial.println(" m");
    //Serial.println();
    
    // sensore 2 mpu6050
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
    //AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
    //AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    //AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    //GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    //GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    //GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    //Serial.print("Accelerometer: ");
    //Serial.print("X = "); Serial.print(AcX);
    //Serial.print(" | Y = "); Serial.print(AcY);
    //Serial.print(" | Z = "); Serial.println(AcZ);
    //equation for temperature in degrees C from datasheet
    Serial.print("T2="); Serial.print(Tmp/340.00+36.53); Serial.println("_"); 
    //Serial.print("Gyroscope: ");
    //Serial.print("X = "); Serial.print(GyX);
    //Serial.print(" | Y = "); Serial.print(GyY);
    //Serial.print(" | Z = "); Serial.println(GyZ);
    //Serial.println(" ");
    
    delay(2000);
}

// Fonti varie:
// http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// https://www.arduinoecia.com.br/2017/04/bmp280-pressao-temperatura-altitude.html
// https://github.com/adafruit/Adafruit_BMP280_Library
// https://github.com/adafruit/Adafruit_BME280_Library/issues/15
// https://forum.arduino.cc/index.php?topic=514961.0
// https://forum.arduino.cc/index.php?topic=428212.0
// http://www.giuseppecaccavale.it/arduino/mpu-6050-gy-521-arduino-tutorial/


*/
















// DHT11 termometro e igrometro funziona con NANO e su create editor
// con entrambi i due DHT che ho
// se non va provare con Old Bootloader

// con NANO #1 non va


#include <SimpleDHT.h>

SimpleDHT11 dht11;


void setup(){
  Serial.begin(9600);
}
 
void loop(){
  byte t = 0;
  byte u = 0;
  
  int err = SimpleDHTErrSuccess;
  if((err = dht11.read(2, &t, &u, NULL)) != SimpleDHTErrSuccess){
    Serial.println("errore lettura");
    delay(1000);
    return;
  }
  
  Serial.print("t: ");
  Serial.print((int)t);
  Serial.print(" °C ___ u: ");
  Serial.print((int)u);
  Serial.println(" % ");
  
  delay(1500);
}


// Fonte corso Aliverti















/*

// DISPLAY LCD 1602 I2C 

// ok con NANO e create editor

// DHT11 termoigrometro funziona con NANO e su create editor
// con entrambi i due DHT che ho
 
#include <SimpleDHT.h>
SimpleDHT11 dht11;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

 
void setup(){
  Serial.begin(9600);
  lcd.init();   // initialize the lcd 
}

 
void loop(){
  byte t = 0;
  byte u = 0;
  
  int err = SimpleDHTErrSuccess;
  if((err = dht11.read(2, &t, &u, NULL)) != SimpleDHTErrSuccess){
    Serial.println("errore lettura");
    delay(1000);
    return;
  }

  // Print a message to the LCD.
  lcd.backlight();
  //lcd.print("Ciao mondo!");
  //lcd.setCursor(0,1);
  //lcd.print("Oi mundo!");
  lcd.setCursor(0,0);
  lcd.print("t = ");
  lcd.print((int)t);
  lcd.print(" gradi C");
  lcd.setCursor(0,1);
  lcd.print("u = ");
  lcd.print((int)u);
  lcd.print(" % ");
  
  //Serial.print("t: ");
  //Serial.print((int)t);
  //Serial.print(" °C ___ u: ");
  //Serial.print((int)u);
  //Serial.println(" % ");
  
  delay(1500);
  lcd.clear();
}


// Fonte http://www.mauroalfieri.it/elettronica/display-lcd-1602-i2c-pcf8574t.html
// Fonte corso Aliverti per DHT11

*/

















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


