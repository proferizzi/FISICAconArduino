

// AD9850 generatore di funzioni a frequenza variabile
// novembre 2020: inseriti due encoder rotativi e usato il pulsante di uno di essi
// -------------- spostato su breadboard il microcontrollore e cambiati i cavetti  


// =============================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Wire.h>   // DISPLAY LCD 1602 I2C
#include <LiquidCrystal_I2C.h>  // ancora LCD
#include <Rotary.h>               //encoder rotativo


// =============================================================================================================
// --- Mapeamento de Hardware ---
#define     W_CLK      8          //Pino WCLK do módulo AD9850
#define     FQ_UD      9          //Pino FQUP do módulo AD9850
#define     DATA      10          //Pino data do módulo AD9850
#define     RESET     11          //Pinoreset do módulo AD9850 
#define     stepPin1  A0                  // Set 'Step' rotary encoder pins
#define     stepPin2  A1

 
// =============================================================================================================
// --- Constantes Auxiliares ---
#define  AD9850_CLOCK  125000000  //Frequência do cristal do módulo


// =============================================================================================================
// --- Macros Auxiliares ---
#define pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); }

    
// =============================================================================================================
// --- Declaração de Objetos ---
Rotary i = Rotary(stepPin1, stepPin2); // Rotart encoder for setting increment.
Rotary r = Rotary(2, 3);               // Rotary encoder for frequency connects to interrupt pins


// =============================================================================================================
// --- Hardware do LCD ---
LiquidCrystal_I2C lcd(0x3F,16,2);


// =============================================================================================================
// --- Protótipo das Funções ---
//==========================================
void tfr_byte(byte data);                   //transfere um byte de forma serial, pelo pino DATA
void sendFrequency(double frequency);       //envia a frequência configurada pelo usuário
void getStep();                             //seleciona o passo de cada incremento


// =============================================================================================================
// --- Variáveis Globais --- 
int forceHzStep = A2;                  // 'Step' rotary encoder's push button - Set 1 Hz steps.
int forcekHz = A3;                     // Interrupt-driven encoder's push button - force 1kHz freq.


long unsigned int freq = 1000;         // Set initial frequency.
long unsigned int freqOld = freq;

long int timer;


char* stepText[11] = {"  1 Hz ", " 10 Hz", " 50 Hz", "100 Hz", "500 Hz", "  1 kHz", "2.5 kHz",
                     "  5 kHz", " 10 kHz", "100 kHz", "500 kHz"};

int stepPointer = 0; 
unsigned long  incr = 0;
String units = stepText[stepPointer];


// =============================================================================================================
// --- Configurações Iniciais --- 
void setup() 
{
  pinMode(12,OUTPUT);  // Alimentazione dell'encoder
  digitalWrite(12,HIGH);
  pinMode(5,OUTPUT);  // Terra per l'encoder
  digitalWrite(5,LOW);
  
  pinMode(4,OUTPUT);  // Terra per il pulsante
  digitalWrite(4,LOW);
  
  pinMode(2, INPUT_PULLUP);            //Entrada Encoder
  pinMode(3, INPUT_PULLUP);
  pinMode(forceHzStep, INPUT_PULLUP);  //Entrada botão 
  pinMode(forcekHz, INPUT_PULLUP);     //Entrada botão
  
  pinMode(FQ_UD, OUTPUT);              //Configura pinos como saída
  pinMode(W_CLK, OUTPUT);
  pinMode(DATA,  OUTPUT);
  pinMode(RESET, OUTPUT);

  pinMode(7,OUTPUT);   // Alimento il display
  digitalWrite(7,HIGH);
  pinMode(6,OUTPUT);   // Terra per il display
  digitalWrite(6,LOW);
  
  lcd.begin();           //inicia LCD 16x2
  
  
  //Configura interrução para o Encoder Rotativo
  // r.begin();  // FORSE NON SERVE
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  sei();

  
  // Initialise the AD9850 module. 
  pulseHigh(RESET);
  pulseHigh(W_CLK);
  pulseHigh(FQ_UD);    //Este pulso habilita o AD9850 para funcionar no modo serial (ver datasheet pag 12, figura 10)


  updateDisplay();
  
   
} //end setup


// =============================================================================================================
// --- Loop Infinito --- 
void loop() 
{
  // Check 'Step' rotary encoder.
  unsigned char result = i.process();
  if (result) {
    if (result == DIR_CW)  {if (stepPointer < 10) stepPointer++;}
    if (result == DIR_CCW) {if (stepPointer > 0) stepPointer--;} 
    updateDisplay();
  }
  
  if (digitalRead(forceHzStep) == LOW) {
    stepPointer = 0;
    updateDisplay();
    delay(50);
  }
  
  if (digitalRead(forcekHz) == LOW) {
    freq = 1000;
    sendFrequency(freq);
    updateDisplay();
    delay(350);
  }
  if (freqOld != freq) {
    sendFrequency(freq);
    updateDisplay();
    freqOld = freq;
  }
  
} //end loop


ISR(PCINT2_vect) {
  unsigned char result = r.process();
  if (result) {
    if (result == DIR_CW) {
      if ((freq + incr) <= 10000000) freq += incr;
    } else {
      if ((freq - incr) >= 10) freq -= incr;
    }
    if (freq <= 10)  freq = 10;
    if (freq >=10000000) freq = 10000000;
  }
}






// =============================================================================================================
// --- Desenvolvimento das Funções ---


// =============================================================================================================
void tfr_byte(byte data) 
{
  for (int i = 0; i < 8; i++, data >>= 1) 
  {
      digitalWrite(DATA, data & 0x01);
      pulseHigh(W_CLK);        //gera um pulso no W_CLK a cada bit transferido
      
  } //end for
  
} //end tfr_byte


// =============================================================================================================
void sendFrequency(double frequency) 
{
  int32_t freq1 = frequency * 4294967295/AD9850_CLOCK;  //calcula frequência
  
  for (int b = 0; b < 4; b++, freq1 >>= 8) tfr_byte(freq1 & 0xFF); 
    
  tfr_byte(0x000);                     //Final, reinicia o valor do byte
  pulseHigh(FQ_UD);                    //Pronto!
  
} //end sendFrequency


// =============================================================================================================
void getStep() 
{
  
  switch(stepPointer) 
  {
    case 0:  incr = 1; break;
    case 1:  incr = 10; break;
    case 2:  incr = 50; break;
    case 3:  incr = 100; break;
    case 4:  incr = 500; break;
    case 5:  incr = 1000; break;
    case 6:  incr = 2500; break;
    case 7:  incr = 5000; break;
    case 8:  incr = 10000; break;
    case 9:  incr = 100000; break;
    case 10: incr = 500000; break;
  } 
  
} //end getStep




void updateDisplay() {
  getStep();                          // 
  units = stepText[stepPointer];
  
   
  lcd.setCursor(0, 0);
  lcd.print("Step: ");
  lcd.setCursor(8, 0);
  lcd.print(units);
  
   
  if (freq < 1000) 
  {
    lcd.setCursor(0, 1);
    if (freq < 1000) lcd.print(" ");
    if (freq <  100) lcd.print(" ");
    lcd.print(freq); 
    lcd.setCursor(12, 1);
    lcd.print("  Hz");
  } 
  else
  if (freq < 1000000) {
   lcd.setCursor(0, 1);
   if (freq < 10000) lcd.print(" ");
   lcd.print((float)freq/1000, 3); 
   lcd.setCursor(12, 1);
   lcd.print(" kHz");
  }  else {
   format(freq);
   lcd.setCursor(12, 1);
   lcd.print(" MHz");
  }
}

void format(long value) {
  int M = (value/1000000);
  int T100 = ((value/100000)%10);
  int T10 = ((value/10000)%10);
  int T1 = ((value/1000)%10);
  int U100 = ((value/100)%10);
  int U10 = ((value/10)%10);
  int U1 = ((value/1)%10);
  lcd.setCursor(4, 1);
  lcd.print(M);lcd.print(".");lcd.print(T100);lcd.print(T10);lcd.print(T1);
  lcd.print(",");lcd.print(U100);lcd.print(U10);lcd.print(U1);
} 

// Fonte wrkits https://www.youtube.com/watch?v=Zw4dzSuapsY
















/*


// Generatore di onde sinusoidali (e quadre) con frequenza selezionabile
// da zero a 40 MHz usando un encoder rotativo, un pulsante e un display I2C LCD1206


// °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° IMPOSTAZIONI INIZIALI
byte stato = 0;            // macchina a stati
boolean FIRST = true;
byte modo = 0;

unsigned long t1, t2, dt;  // timer non bloccanti

#define encoderPinA  2   // encoder
#define encoderPinB  3
volatile long pos = 0;

#include <AD9850.h>         // DAC
const int W_CLK_PIN = 6;
const int FQ_UD_PIN = 7;
const int DATA_PIN = 8;
const int RESET_PIN = 9;
double freq = 1000;
double step = 1;
double trimFreq = 124999500;
int phase = 0;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup(){
  //Serial.begin(9600);    // seriale per debug
  
  pinMode(encoderPinA, INPUT_PULLUP);  // encoder
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);

  DDS.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);  // DAC
  DDS.calibrate(trimFreq);
  DDS.down();
  pinMode(12, OUTPUT);    
  digitalWrite(12, HIGH);    

  lcd.begin();           //display 
  lcd.backlight();
  lcd.home();
  //lcd.print("Hello world");   // per debug, se non va provare I2C scanner
  //delay(3000);   
  lcd.clear(); 
  pinMode(16, OUTPUT);    // analogico 2
  digitalWrite(16, HIGH);                   
}


// °°°°°°°°°°°°°°°°°°°°°°°°°°°°°° PARTE ESECUTIVA PRINCIPALE
void loop(){
  switch(stato){
    case 0:
      sceglimodo();
      break;  
    case 1:
      setFreq();
      break;  
    case 2:
      setStep();
      break;
    case 3:
      setRun();
      break;    
  }
  if ((millis()-t2) > 200) {
    lcd.begin();           //display 
    lcd.backlight();
    lcd.clear();
    t2 = millis();
  }
}


// °°°°°°°°°°°°°°°°°°°°°°°°°° FUNZIONI AUSILIARIE
void sceglimodo(){
  if (FIRST) {
    FIRST = false;  
    t1 = millis();
  }
  dt = millis() -t1;
  if (dt > 200) {
    if (pos > 0) {
      modo++;
      if (modo >= 2) modo = 2;  
    }
    if (pos < 0) {
      modo--;  
      if (modo < 0) modo = 0;
    }
    pos = 0;

    if (modo == 0) {
      lcd.home();
      lcd.print("Imposta freq.");
    } else if (modo == 1) {
      lcd.print("Imposta passo");
    } else if (modo == 2) {
      lcd.print("Inizio?");
    } 

    t1 = millis();
  }

  if (!digitalRead(4)) {
    go(modo+1);
    delay(300);
  }
}

void go(int st){
  stato = st;
  FIRST = true;  
}


//char str[11];

void setFreq(){
  if (FIRST) {
    FIRST = false;  
    lcd.clear(); 
    t1 = millis();
  }

  dt = millis() - t1;
  if (dt > 200) {
      if (pos > 0) {
        freq += step;     
      }
      if (pos < 0) {
        freq -= step;
        if (freq <= 1) freq = 1;
      }
      pos = 0;

      lcd.home();
      lcd.print("f = ");
      lcd.print(freq);
      
      t1 = millis();
  }

  if (!digitalRead(4)) {
    go(0);
    lcd.clear();
    delay(300);
  }
}

void setStep(){
  if (FIRST) {
    FIRST = false;
    lcd.clear(); 
    t1 = millis();
  }
  dt = millis() - t1;
  if (dt > 200) {    
    if (pos > 0) {
      if (step == 1) step = 10.0;
      else step = step*10.0;     
    }
    if ((pos < 0) && (step > 1.0)) {
      step = step / 10.0;      
    }
    pos = 0;
       
    lcd.home();
    lcd.print("passo = ");
    lcd.print(step);
    
    t1 = millis();
  }

  if (!digitalRead(4)) {
    go(0);
    lcd.clear();
    delay(300);
  }
}

void setRun(){
  if (FIRST) {
    FIRST = false;  
    lcd.clear();
    lcd.home();
    lcd.print("Attivo con");
    lcd.setCursor(1,0);
    lcd.print("f = ");
    lcd.print(freq);
    
    DDS.up();
    DDS.setfreq(freq, phase);
    t1 = millis();
  }
  dt = millis() - t1;
  if (dt > 200) {   
    if (pos > 0) {
      freq += step; 
      DDS.setfreq(freq, phase);          
    }
    if (pos < 0) {
      freq -= step;
      if (freq <= 1) freq = 1;
      DDS.setfreq(freq, phase);      
    }
    pos = 0;

    lcd.home();
    lcd.print("f = ");
    lcd.print(freq);
    
    t1 = millis();
  }

  if (!digitalRead(4)) {
    go(0);
    DDS.down();
    lcd.clear();
    delay(300);
  }
}

void inc() {
  pos++;
}
void dec() {
  pos--;
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoderPinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == LOW) {
      //pos = pos + 1;         // CW
      inc();
    } else {
      dec();
      //pos = pos - 1;         // CCW
    }
  } else {// look for a high-to-low on channel A
    if (digitalRead(encoderPinB) == HIGH) {// check channel B to see which way encoder is turning
      inc(); 
      //pos = pos + 1;          // CW
    } else {
      //pos = pos - 1;          // CCW
      dec();
    }
  }  
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoderPinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoderPinA) == HIGH) {
      //pos = pos + 1;         // CW
      inc();
    } else {
      dec();
      //pos = pos - 1;         // CCW
    }
  } else { // Look for a high-to-low on channel B
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinA) == LOW) {
      inc();
      //pos = pos + 1;          // CW
    } else {
      dec();
      //pos = pos - 1;          // CCW
    }
  }
}


// Fonte Aliverti https://www.youtube.com/watch?v=aQ8mca-piR4
// Fonte encoder rotativo https://playground.arduino.cc/Main/RotaryEncoders/#Waveform
// Fonte per libreria del DAC https://github.com/F4GOJ/AD9850
// Fonte Aliverti per LCD commento in corso Aliverti 219, diverso dallo sketch
// ecco qui http://scienceclub.org.au/download/1602-lcd-display-serial-connection-arduino-library/
// Inoltre: modifica mia per VCC e GND su pin analogici, non dimenticare i2cscanner.ino

*/



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































/*

// GENERARE ONDE SINUSOIDALI SENZA DAC

// Usiamo una rete di filtri passa basso RC e per lo sketch basta il blink con 20 ms di periodo


void setup() {                
  pinMode(10, OUTPUT);     
}


void loop() {
  digitalWrite(10, HIGH);  
  delay(10);               
  digitalWrite(10, LOW);   
  delay(10);               
}

// Fonte Aliverti #168 del corso

*/























/*


// solo ad9850, testato a giu 2020 OK
 
#include <AD9850.h>
//#include <Wire.h> 
 
const int W_CLK_PIN = 8;
const int FQ_UD_PIN = 9;
const int DATA_PIN = 10;
const int RESET_PIN = 11;
 
long Freq = 100;
double trimFreq = 125000000;
 
int phase = 0;
 
void setup() {
  Serial.begin(9600);
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);
  DDS.calibrate(trimFreq);
}


void loop() {
  DDS.setfreq(Freq, phase);
  delay(2000);
  DDS.down();
  delay(100);
  DDS.up();
  delay(100);
  Serial.println(Freq);
  Freq = Freq + 10;
  if(Freq == 300) Freq = 100;  
}
 
// Fonte https://km4nmp.com/2019/08/24/vfo-for-the-pixie-wiring-and-sketch-for-ad9850/
//       e esempio nella libreria https://github.com/F4GOJ/AD9850



*/












/*

// originale
 
#include <AD9850.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>
 
const int RotaryButtonPin = A1;
const int PTTPin = A0;
const int W_CLK_PIN = 8;
const int FQ_UD_PIN = 9;
const int DATA_PIN = 10;
const int RESET_PIN = 11;
 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
Rotary r = Rotary(2, 3);
int RotaryButtonState = 0;
int PTTPinState = 0;
long TurnNum = 100;
long Freq = 7000000;
double OldFreq = 7000000;
double trimFreq = 125000000;
 
int phase = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(RotaryButtonPin, INPUT);
  pinMode(PTTPin, INPUT);
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);
  DDS.calibrate(trimFreq);
  lcd.begin(16,2);
  r.begin();
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  sei();
 
  lcd.setCursor( 3, 0 );                   
  lcd.print("KM4NMP.com");  
  DDS.setfreq(Freq, phase);
  delay(2000);
    
}


void loop() {
  PTTPinState = digitalRead(PTTPin);
   
  RotaryButtonState = digitalRead(RotaryButtonPin);
  if (RotaryButtonState == LOW) {
     TurnNum = TurnNum * 10;
     }
  if (TurnNum > 10000) {
    TurnNum = 1;   
  }
  if (TurnNum < 1) {
    TurnNum = 10000;
  }
  if (OldFreq != Freq) {
     DDS.setfreq(Freq, phase);
     Serial.println( Freq );
  }  
  lcd.setCursor( 4, 1 );                   
  lcd.print( Freq ); 
  OldFreq = Freq;
  delay(200);
}
 
ISR(PCINT2_vect) {
  unsigned char result = r.process();
  if (result == DIR_NONE) {
    // do nothing
  }
  else if (result == DIR_CW) {
    Serial.println("ClockWise");
    Freq = Freq - TurnNum;
    if (Freq < 7000000){
      Freq = 7000000;
    }
    if (Freq > 7300000){
      Freq = 7300000;  
    }
    
  }
  else if (result == DIR_CCW) {
    Serial.println("CounterClockWise");
    Freq = Freq + TurnNum;
    if (Freq > 7300000){
      Freq = 7300000;
    }
    if (Freq < 7000000){
      Freq = 7000000;  
    }
  }
}

// Fonte https://km4nmp.com/2019/08/24/vfo-for-the-pixie-wiring-and-sketch-for-ad9850/
//       https://github.com/mathertel/RotaryEncoder   
//       https://github.com/F4GOJ/AD9850
//       http://www.ardumotive.com/i2clcden.html 


*/
