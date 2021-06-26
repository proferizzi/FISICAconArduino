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

// Fonte wrkits






































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









// AD9850 generatore di funzioni a frequenza variabile 


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
  digitalWrite(5,LOW);
  
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




