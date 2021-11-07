
/*


//  PRIMA LEGGE DI OHM con Monitor Seriale e Arduino come voltmetro
//
//  Materiale occorrente: 
//    - Hardware: arduino UNO r3, un resistore ohmico con valore di resistenza noto,
//                un potenziometro, breadboard, cavetti, PC;
//    - multimetro (usato come amperometro).
//
//  Per approfondire visita come ospite: https://rizzinelli.moodlecloud.com/course/view.php?id=6


const int pin_V1 = 0;   // pin di comunicazione tra Arduino e un capo della resistenza
const int pin_V2 = 1;   // pin di comunicazione tra Arduino e l'altro capo della resistenza

// definisco le variabili di tensione
float V1;
float V2;
float deltaV;

void setup() {
  Serial.begin(9600);  
  Serial.println("deltaV");
}

void loop() {
  V1 = analogRead(pin_V1);  
  V2 = analogRead(pin_V2);
  deltaV = abs(V2 - V1)*(5.0 / 1023.0);
  //Serial.print(V1);
  //Serial.print(" ");
  //Serial.print(V2);
  //Serial.print(" ");
  
  Serial.println(deltaV);
  delay(1000);
}

*/





/*



//  PRIMA LEGGE DI OHM con Monitor Seriale e Arduino come voltmetro e amperometro
//
//  Materiale occorrente: 
//    - Hardware: arduino UNO r3, un resistore ohmico con valore di resistenza noto,
//                un potenziometro, breadboard, cavetti, PC; xxx
//
//  Per approfondire visita come ospite: https://rizzinelli.moodlecloud.com/course/view.php?id=6


const int pin_V1 = 0;   // pin di comunicazione tra Arduino e un capo della resistenza
const int pin_V2 = 5;   // pin di comunicazione tra Arduino e l'altro capo della resistenza

// definisco le variabili di tensione
float V1;
float V2;
float deltaV;

void setup() {
  Serial.begin(9600);  
  Serial.println("deltaV");
}

void loop() {
  V1 = analogRead(pin_V1);  
  V2 = analogRead(pin_V2);
  deltaV = abs(V2 - V1);
  //Serial.print(V1);
  //Serial.print(" ");
  //Serial.print(V2);
  //Serial.print(" ");
  Serial.println(deltaV);
  delay(1000);
}

// Fonte: xxx
// Fonte: https://www.engineersgarage.com/contribution/arduino-based-ammeter




*/




/*



//  PRIMA LEGGE DI OHM con display LCD e interfaccia I2C
//  
//  Materiale occorrente: 
//    - Hardware: arduino UNO r3, un resistore ohmico con valore di resistenza noto,
//                un potenziometro, breadboard, cavetti, display LCD con interfaccia I2C;
//    - multimetro (usato come amperometro).
//
//  Per approfondire visita come ospite: https://rizzinelli.moodlecloud.com/course/view.php?id=6

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD I2C address
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // oppure 27

const int pin_V1 = 0;   // pin di comunicazione tra Arduino e un capo della resistenza
const int pin_V2 = 1;   // pin di comunicazione tra Arduino e l'altro capo della resistenza

// definisco le variabili di tensione
float V1;
float V2;
float deltaV;

void setup() {
  lcd.begin(16, 2);  // initialize the lcd
  lcd.clear();
  //Serial.begin(9600);  
  //Serial.println("deltaV");
}

void loop() {
  V1 = analogRead(pin_V1);  
  V2 = analogRead(pin_V2);
  deltaV = abs(V2 - V1)*(5.0 / 1023.0);
  //Serial.print(V1);
  //Serial.print(" ");
  //Serial.print(V2);
  //Serial.print(" ");
  //Serial.println(deltaV);
  //delay(1000);
  
  //int val = (analogRead(A0)); //read analog pin A0
  lcd.setCursor(5, 0);
  lcd.print("VOLTAGGIO = ");
  lcd.setCursor(6, 1);
  lcd.print(deltaV);
  delay(500);
  lcd.clear();
}

// Fonte: https://zhutarduino.wordpress.com/arduino-projects/how-to-set-up-and-use-a-1602-i2c-serial-lcd-with-your-arduino/
*/

/*

// I2C SCANNER PER SAPERE L'INDIRIZZO DEL DISPLAY

#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}

void loop(){
  byte error, address;
  int nDevices;
  Serial.println("Scanning…");
  nDevices = 0;
  for(address = 1; address < 127; address++ ){
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
      Serial.print("I2C device found at address 0x");
      if (address<16)
      Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");
      nDevices++;
    }
    else if (error==4){
      Serial.print("Unknow error at address 0x");
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

*/








/*


//  PRIMA LEGGE DI OHM con display OLED
//  
//  Materiale occorrente: 
//    - Hardware: arduino UNO r3, un resistore ohmico con valore di resistenza noto,
//                un potenziometro, breadboard, cavetti, display LCD con interfaccia I2C;
//    - multimetro (usato come amperometro).
//
//  Per approfondire visita come ospite: https://rizzinelli.moodlecloud.com/course/view.php?id=6
//

xxx

// Fonte: https://www.instructables.com/id/An-Adruino-OLED-Voltmeter/







*/





/*


//  PRIMA LEGGE DI OHM con display OLED
//  
//  Materiale occorrente: 
//    - Hardware: arduino UNO r3, un resistore ohmico con valore di resistenza noto,
//                un potenziometro, breadboard, cavetti, display LCD con interfaccia I2C;
//    - multimetro (usato come amperometro).
//
//  Per approfondire visita come ospite: https://rizzinelli.moodlecloud.com/course/view.php?id=6
//

/*
// DISPLAY LCD 1602 I2C
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
*/




// OLED

    #include <SPI.h>  
    #include <Wire.h>  
    #include <Adafruit_GFX.h>  
    #include <Adafruit_SSD1306.h>  
      
    // visualizzazione di un testo su display OLED  
    // Prof. Michele Maffucci  
    // 02.10.15  
      
    // utilizzo di dispositivo SPI  
    // dispositivo -> Arduino  
      
    #define OLED_MOSI   11  
    #define OLED_CLK   12  
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
      
      // posizioniamo il cursore nella posizione x: 35; y: 32  
      display.setCursor(32,32);  
      
      // stampiamo su display il messaggio  
      display.println("Bom dia mundo");  
      display.println("Vai criatura, bora nascer ;o)  beijao");  
      
      // abilitiamo il display alla visualizzazione  
      display.display();  
    }  
      
      
    void loop() {  
    // loop vuoto  
    }  
// Fonte: http://www.maffucci.it/2015/10/03/esercizio-arduino-in-60-minuti-usare-un-display-oled/
// Fonte: https://www.instructables.com/id/An-Adruino-OLED-Voltmeter/












