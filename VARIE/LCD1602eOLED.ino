/*


// LCD 1602 definitivo

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(16,OUTPUT);  // pin analogico A2
  digitalWrite(16,LOW);
  pinMode(17,OUTPUT);  // pin analogico 
  digitalWrite(17,HIGH);
  
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
}

void loop()
{
	// Do nothing here...
}

// Fonte commento in corso Aliverti 219, diverso dallo sketch
// ecco qui http://scienceclub.org.au/download/1602-lcd-display-serial-connection-arduino-library/
// Inoltre: modifica mia per VCC e GND su pin analogici, non dimenticare i2cscanner.ino



*/
















/*



// LCD 1602 lungo e strano

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27 
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  pinMode(16,OUTPUT);  // pin analogico A2
  digitalWrite(16,LOW);
  pinMode(17,OUTPUT);  // pin analogico 
  digitalWrite(17,HIGH);
  
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.home ();    
  lcd.print("Hello World!");    
}

int n = 0;

void loop() {  
  lcd.setCursor(0,1);
  lcd.print(n);
  lcd.print(" ");
  delay(1000);
  n++;
}


// Fonte Aliverti corso #219, modifica mia per VCC e GND su pin analogici, non dimenticare i2cscanner.ino
// Test ok con UNO



*/













/*


// ok con NANO e create editor

// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
// 
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <Wire.h>


void setup(){
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}


// Fonte https://playground.arduino.cc/Main/I2cScanner?action=sourceblock&num=1

*/














// DISPLAY LCD 1602 I2C 

// ok con NANO e create editor

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

 
void setup(){
  lcd.init();   // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Hello world!");
  lcd.setCursor(0,1);
  lcd.print("Vai creatura!");
}

 
void loop(){
}


// Fonte http://www.mauroalfieri.it/elettronica/display-lcd-1602-i2c-pcf8574t.html



























/*

// OLED // ok con proMini (e CP2102) ma non da questo editor
// visualizzazione di un testo su display OLED; utilizzo di dispositivo SPI  


#include <SPI.h>  
#include <Wire.h>  
#include <Adafruit_GFX.h>  
// Adafruit SSD1306 - Version: Latest 
#include <Adafruit_SSD1306.h>
#include <splash.h>
      
#define OLED_MOSI   11  
#define OLED_CLK   13    // con UNO il 12 // con proMini il 13 
#define OLED_DC    9  
#define OLED_CS    8  
#define OLED_RESET 10  
    
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);  
     
// viene controllato se stiamo utilizzando esattamente un display a 64 righe  
#if (SSD1306_LCDHEIGHT != 64)  
#error("Assolutamente non corretto! Per favore correggi Adafruit_SSD1306.h!");  
#endif  


void setup()   {  
  Serial.begin(9600);  
      
  // per default by default viene impostata una tensione interna di 3.3V  
  display.begin(SSD1306_SWITCHCAPVCC);  
      
  // cancelliamo lo schermo  
  display.clearDisplay();  
    
  // impostiamo il colore a bianco (in questo tipo di dsiplay possimo impostare solo bianco e nero)  
  display.setTextColor(WHITE);  
      
  // fissiamo la dimensione del testo  
  display.setTextSize(1);  
      
  // posizioniamo il cursore nella posizione x: 35; y: 32  
  display.setCursor(32,32);  
      
  // stampiamo su display il messaggio  
  display.println("Bom dia mundo");   
      
  // abilitiamo il display alla visualizzazione  
  display.display();  
}  


void loop() {  
    // loop vuoto  
}  


// Fonte: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// Datasheet OLED: https://components101.com/oled-display-ssd1306

*/
















/*




// OLED // ok con proMini (e CP2102) ma non da questo editor
// visualizzazione di un testo in movimento su display OLED


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   11
#define OLED_CLK   13    // con UNO il 12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// viene controllato se stiamo utilizzando esattamente un display a 64 righe
#if (SSD1306_LCDHEIGHT != 64)
#error("Assolutamente non corretto! Per favore correggi Adafruit_SSD1306.h!");
#endif


void setup()   {
  Serial.begin(9600);

  // per default by default viene impostata una tensione ionterna di 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);

  // cancelliamo lo schermo
  display.clearDisplay();

  // impostiamo il colore a bianco (in questo tipo di dsiplay possimo impostare solo bianco e nero)
  display.setTextColor(WHITE);

  // fissiamo la dimensione del testo
  display.setTextSize(1);
}


void loop() {
  // movimento verso il basso
  for (int i = 0; i < 56; i++) {
    // incrementiamo la coordinata i (coordinata y)
    // fino a quando i < 56
    // Viene fissata la coordinata x
    // per far scorrere il testo sulla stessa colonna
      
    display.setCursor(32, i);
    display.print("Salve mondo");
    display.display();
    display.clearDisplay();
  }
  // movimento verso l'alto
  for (int i = 56; i > 0; i--) {
    // decrementiamo la coordinata i (coordinata y)
    // fino a quando i > 0
    // Viene fissata la coordinata x
    // per far scorrere il testo sulla stessa colonna
    
    display.setCursor(32, i);
    display.print("Salve mondo");
    display.display();
    display.clearDisplay();
  }
}

    
// Fonte: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// Datasheet OLED: https://components101.com/oled-display-ssd1306


*/

















/*


// OLED // ok con proMini (e CP2102) ma non da questo editor
// visualizzazione di un bitmap su display OLED


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_MOSI   11
#define OLED_CLK   13   // con UNO il 12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10
 
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
 
// array dell'immagine convertita
const unsigned char PROGMEM faccinaUno [] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3c,0x1e,0x0,0x0,0x3c,0x1e,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x6,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x6,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x30,0x6,0x0,0x0,0x30,0x6,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1c,0x1c,0x0,0x0,0x1c,0x1c,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x38,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0x80,0x0,0x0,0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xc0,0x0,0x0,0x1,0xff,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfe,0x0,0x0,0x3f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};
 
// viene controllato se stiamo utilizzando esattamente un display a 64 righe
#if (SSD1306_LCDHEIGHT != 64)
#error("Assolutamente non corretto! Per favore correggi Adafruit_SSD1306.h!");
#endif
 
 
void setup()   {
  Serial.begin(9600);
 
  // per default by default viene impostata una tensione ionterna di 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);
}
 
 
void loop() {
  // cancelliamo lo schermo
  display.clearDisplay();
 
  // visualizziamo il bitmap di dimensione 128x64 px con nome: faccinaUno nella posizione (0,0) impostando il colore a bianco
  display.drawBitmap(0, 0, faccinaUno, 128, 64, WHITE);
 
  // attiviamo il display
  display.display();
}

    
// Fonte: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// Datasheet OLED: https://components101.com/oled-display-ssd1306


*/





















/*




// OLED // ok con proMini (e CP2102) ma non da questo editor
// visualizzazione di un bitmap su display OLED


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   11
#define OLED_CLK   13   // con UNO il 12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// array dell'immagine convertita
const unsigned char PROGMEM faccinaUno [] =
{
0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x3f,0xfc,0x0,0x0,
0x0,0x1,0xff,0xff,0x80,0x0,
0x0,0x7,0xff,0xff,0xe0,0x0,
0x0,0x1f,0xff,0xff,0xf8,0x0,
0x0,0x3f,0xff,0xff,0xfc,0x0,
0x0,0x7f,0xff,0xff,0xfe,0x0,
0x0,0xff,0xff,0xff,0xff,0x0,
0x1,0xff,0xff,0xff,0xff,0x80,
0x3,0xff,0xff,0xff,0xff,0xc0,
0x7,0xff,0x3f,0xfc,0xff,0xc0,
0x7,0xfe,0x1f,0xf8,0x7f,0xe0,
0xf,0xfc,0xf,0xf0,0x3f,0xf0,
0xf,0xfc,0xf,0xf0,0x3f,0xf0,
0x1f,0xfc,0xf,0xf0,0x3f,0xf8,
0x1f,0xfc,0xf,0xf0,0x3f,0xf8,
0x1f,0xfc,0xf,0xf0,0x3f,0xf8,
0x3f,0xfc,0xf,0xf0,0x3f,0xfc,
0x3f,0xfe,0x1f,0xf8,0x7f,0xfc,
0x3f,0xff,0x3f,0xfc,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xe7,0xff,0xff,0xe7,0xfc,
0x3f,0xcf,0xff,0xff,0xf3,0xfc,
0x3f,0x9f,0xff,0xff,0xf9,0xfc,
0x1e,0xf,0xff,0xff,0xf0,0x78,
0x1f,0xcf,0xff,0xff,0xf3,0xf8,
0x1f,0xe7,0xff,0xff,0xe7,0xf8,
0xf,0xf3,0xff,0xff,0xcf,0xf0,
0xf,0xf9,0xff,0xff,0x9f,0xf0,
0x7,0xfc,0x7f,0xfe,0x1f,0xe0,
0x3,0xfe,0x1f,0xf8,0x7f,0xc0,
0x3,0xff,0x0,0x0,0xff,0xc0,
0x1,0xff,0xc0,0x3,0xff,0x80,
0x0,0xff,0xfc,0x3f,0xff,0x0,
0x0,0x7f,0xff,0xff,0xfe,0x0,
0x0,0x3f,0xff,0xff,0xfc,0x0,
0x0,0x1f,0xff,0xff,0xf8,0x0,
0x0,0x7,0xff,0xff,0xe0,0x0,
0x0,0x1,0xff,0xff,0x80,0x0,
0x0,0x0,0x3f,0xfc,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0
};

// viene controllato se stiamo utilizzando esattamente un display a 64 righe
#if (SSD1306_LCDHEIGHT != 64)
#error("Assolutamente non corretto! Per favore correggi Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(9600);

  // per default by default viene impostata una tensione ionterna di 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);
}


void loop() {
  // cancelliamo lo schermo
  display.clearDisplay();

  // visualizziamo il bitmap di dimensione 128x64 px con nome: faccinaUno nella posizione (40,8) impostando il colore a bianco
  display.drawBitmap(40, 8, faccinaUno, 48, 48, WHITE);

  // attiviamo il display
  display.display();
}

    
// Fonte: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// Datasheet OLED: https://components101.com/oled-display-ssd1306


*/
























/*




// OLED // ok con proMini (e CP2102) ma non da questo editor
// visualizzazione tre bitmap in sequenza su display OLED


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI  11
#define OLED_CLK   13   // con UNO il 12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// array dell'immagine convertita
const unsigned char PROGMEM faccinaUno [] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3c,0x1e,0x0,0x0,0x3c,0x1e,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x6,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x6,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x30,0x6,0x0,0x0,0x30,0x6,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1c,0x1c,0x0,0x0,0x1c,0x1c,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x38,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0x80,0x0,0x0,0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xc0,0x0,0x0,0x1,0xff,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfe,0x0,0x0,0x3f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

const unsigned char PROGMEM faccinaDue [] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3c,0x1e,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1c,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3e,0x0,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3f,0xc0,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf0,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xfe,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0x0,0x30,0x6,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x80,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xe,0x0,0x0,0x1c,0x1c,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1c,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0x0,0x0,0x0,0x0,0x0,0x0,0x38,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3f,0xe0,0x0,0x0,0x1,0xff,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xfe,0x0,0x0,0x3f,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

const unsigned char PROGMEM faccinaTre [] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3c,0x1e,0x0,0x0,0x3c,0x1e,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x6,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x7,0x0,0x0,0x70,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x70,0x6,0x0,0x0,0x30,0x7,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x30,0x6,0x0,0x0,0x30,0x6,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x38,0xe,0x0,0x0,0x38,0xe,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1c,0x1c,0x0,0x0,0x1c,0x1c,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xfc,0x0,0x0,0x1f,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xf,0xf8,0x0,0x0,0xf,0xf8,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xe,0x0,0x0,0x0,0x0,0x0,0x0,0x38,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x7,0x80,0x0,0x0,0x0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x7f,0xe0,0x0,0x0,0x3,0xff,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xc0,0x1,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

// viene controllato se stiamo utilizzando esattamente un display a 64 righe
#if (SSD1306_LCDHEIGHT != 64)
#error("Assolutamente non corretto! Per favore correggi Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(9600);

  // per default by default viene impostata una tensione ionterna di 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);
}

void loop() {
  // cancelliamo lo schermo
  display.clearDisplay();

  // visualizziamo il bitmap di dimensione 128x64 px con nome: faccinaUno nella posizione (0,0) impostando il colore a bianco
  display.drawBitmap(0, 0, faccinaUno, 128, 64, WHITE);
  
  // attiviamo il display
  display.display();

  //Manteniamo persistente l'immagine per 1 secondo
  delay(1000);
  
  // cancelliamo lo schermo
  display.clearDisplay();
  
  // visualizziamo il bitmap di dimensione 128x64 px con nome: faccinaDue nella posizione (0,0) impostando il colore a bianco
  display.drawBitmap(0, 0, faccinaDue, 128, 64, WHITE);
  display.display();

  //Manteniamo persistente l'immagine per 1 secondo
  delay(1000);
  
  // cancelliamo lo schermo
  display.clearDisplay();

  // visualizziamo il bitmap di dimensione 128x64 px con nome: faccinaTre nella posizione (0,0) impostando il colore a bianco
  display.drawBitmap(0, 0, faccinaTre, 128, 64, WHITE);
  display.display();
  
  //Manteniamo persistente l'immagine per 1 secondo
  delay(1000);
}

    
// Fonte: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// Datasheet OLED: https://components101.com/oled-display-ssd1306


*/






























/*

// OLED // ok con proMini (e CP2102) ma non da questo editor
// movimento di un bitmap su display OLED


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI  11
#define OLED_CLK   13  // con UNO il 12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// array dell'immagine convertita
const unsigned char PROGMEM faccinaUno [] =
{
0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x3f,0xfc,0x0,0x0,
0x0,0x1,0xff,0xff,0x80,0x0,
0x0,0x7,0xff,0xff,0xe0,0x0,
0x0,0x1f,0xff,0xff,0xf8,0x0,
0x0,0x3f,0xff,0xff,0xfc,0x0,
0x0,0x7f,0xff,0xff,0xfe,0x0,
0x0,0xff,0xff,0xff,0xff,0x0,
0x1,0xff,0xff,0xff,0xff,0x80,
0x3,0xff,0xff,0xff,0xff,0xc0,
0x7,0xff,0x3f,0xfc,0xff,0xc0,
0x7,0xfe,0x1f,0xf8,0x7f,0xe0,
0xf,0xfc,0xf,0xf0,0x3f,0xf0,
0xf,0xfc,0xf,0xf0,0x3f,0xf0,
0x1f,0xfc,0xf,0xf0,0x3f,0xf8,
0x1f,0xfc,0xf,0xf0,0x3f,0xf8,
0x1f,0xfc,0xf,0xf0,0x3f,0xf8,
0x3f,0xfc,0xf,0xf0,0x3f,0xfc,
0x3f,0xfe,0x1f,0xf8,0x7f,0xfc,
0x3f,0xff,0x3f,0xfc,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xff,0xff,0xff,0xff,0xfc,
0x3f,0xe7,0xff,0xff,0xe7,0xfc,
0x3f,0xcf,0xff,0xff,0xf3,0xfc,
0x3f,0x9f,0xff,0xff,0xf9,0xfc,
0x1e,0xf,0xff,0xff,0xf0,0x78,
0x1f,0xcf,0xff,0xff,0xf3,0xf8,
0x1f,0xe7,0xff,0xff,0xe7,0xf8,
0xf,0xf3,0xff,0xff,0xcf,0xf0,
0xf,0xf9,0xff,0xff,0x9f,0xf0,
0x7,0xfc,0x7f,0xfe,0x1f,0xe0,
0x3,0xfe,0x1f,0xf8,0x7f,0xc0,
0x3,0xff,0x0,0x0,0xff,0xc0,
0x1,0xff,0xc0,0x3,0xff,0x80,
0x0,0xff,0xfc,0x3f,0xff,0x0,
0x0,0x7f,0xff,0xff,0xfe,0x0,
0x0,0x3f,0xff,0xff,0xfc,0x0,
0x0,0x1f,0xff,0xff,0xf8,0x0,
0x0,0x7,0xff,0xff,0xe0,0x0,
0x0,0x1,0xff,0xff,0x80,0x0,
0x0,0x0,0x3f,0xfc,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0
};

// viene controllato se stiamo utilizzando esattamente un display a 64 righe
#if (SSD1306_LCDHEIGHT != 64)
#error("Assolutamente non corretto! Per favore correggi Adafruit_SSD1306.h!");
#endif

void setup()   {
  Serial.begin(9600);

  // per default by default viene impostata una tensione ionterna di 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);
}


void loop() {
  // cancelliamo lo schermo
  display.clearDisplay();

  // partendo dalla posizione (0,8) spostiamo da sinistra verso destra
  // l'immagine di dimensione 48x48 px con nome: faccinaUno fino alla coordinata (48,8)

  // movimento da SX a DX
  for (int i = 0; i < 80; i++){
    display.drawBitmap(i, 8, faccinaUno, 48, 48, WHITE);
    // attiviamo il display
    display.display();
    // cancelliamo lo schermo
    display.clearDisplay();
  }

  // movimento da DX a SX
  for (int i = 80; i > 0 ; i--){
    display.drawBitmap(i, 8, faccinaUno, 48, 48, WHITE);
    // attiviamo il display
    display.display();
    // cancelliamo lo schermo
    display.clearDisplay();
  }
}

    
// Fonte: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// Datasheet OLED: https://components101.com/oled-display-ssd1306


*/



























/*

// ESPERIMENTO: Sensore a ultrasuoni SR04 con proMini (e CP2102), OLED (ma non da questo editor),
//              convertitore logico e alimentazione esterna a 5V per il sensore 
//              (power supply da breadboard con alimentatore da 220V a 7,5 V
//               e jack per batterie da 9V usato col nero sul cerchiolino più piccolo)
 

// Dichiarazione dei pin digitali di comunicazione tra sensore e Arduino
#define TRIGGER 2 
#define ECHO  3

#include <SPI.h>  
#include <Wire.h>  
#include <Adafruit_GFX.h>  
// Adafruit SSD1306 - Version: Latest 
#include <Adafruit_SSD1306.h>
#include <splash.h>
      
#define OLED_MOSI   11  
#define OLED_CLK   13    // con UNO il 12 // con proMini il 13 
#define OLED_DC    9  
#define OLED_CS    8  
#define OLED_RESET 10  
    
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);  
     
// viene controllato se stiamo utilizzando esattamente un display a 64 righe  
#if (SSD1306_LCDHEIGHT != 64)  
#error("Assolutamente non corretto! Per favore correggi Adafruit_SSD1306.h!");  
#endif  


void setup()   {  
  pinMode(TRIGGER, OUTPUT);   // Il sensore riceve dati da Arduino tramite il TRIGGER
  pinMode(ECHO, INPUT);   // Il sensore invia dati ad Arduino tramite l'ECHO
  Serial.begin(9600);    // La porta seriale riceve/invia dati alla velocità di 9600 bit/s (effettivi 7680)
}  


void loop() {  
  // Arduino invia un impulso di 10 microsecondi al sensore,
  // il quale invia un treno di otto onde sonore a 40 kHz verso l'ostacolo.
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);   
  delayMicroseconds(10);         
  digitalWrite(TRIGGER, LOW);
  
  // Il sensore riceve il treno di onde e invia ad Arduino l'intervallo di tempo tra invio e arrivo 
  long durata = pulseIn(ECHO, HIGH);   
  
  // Calcoliamo la distanza tra sensore e oggetto usando il valore, in condizioni standard,
  // della velocità del suono in aria secca. xxx come considerare sensibilità 0,3 cm?
  long distanza = 10 * 0.034 * durata / 2 ;   // fattore 10 per i millimetri  


  
  // Stampa su monitor/plotter seriale la distanza in centimetri.
  if(distanza<500 && distanza>20){   // Struttura di controllo per vedere meglio i dati sul plotter 

  // per default by default viene impostata una tensione interna di 3.3V  
  display.begin(SSD1306_SWITCHCAPVCC);  
      
  // cancelliamo lo schermo  
  display.clearDisplay();  
    
  // impostiamo il colore a bianco (in questo tipo di dsiplay possimo impostare solo bianco e nero)  
  display.setTextColor(WHITE);  
      
  // fissiamo la dimensione del testo  
  display.setTextSize(1);  
      
  // posizioniamo il cursore nella posizione x: 35; y: 32  
  display.setCursor(32,32);  
      
  // stampiamo su display il messaggio  
  display.println(distanza);   
      
  // abilitiamo il display alla visualizzazione  
  display.display(); 
  
    Serial.println(distanza);   
  }
  delay(500);   // Il minimo pare sia 30 ms.
  
}  


// Fonti per OLED: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
//                 e datasheet https://components101.com/oled-display-ssd1306
// Fonti per ultrasuoni: corso Aliverti oppure Howtomechatronics



*/





































