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



// ESPERIMENTO #1
// Testato giugno 2020 ok con oscilloscopio in accoppiamento AC esce onda a 12,89 Hz e 4,80 Vpp
// Salvati screenshot su pendrive, numeri files 17 e 18
// usato modulo blu ma penso sia lo stesso per gli altri


//Programa: Onda Senoidal MCP4725 usata per far lampeggiare un LED

//Alteracoes e adaptacoes: Arduino e Cia
//Baseado no programa de exemplo Sineware - Adafruit

#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

//Define a resolucao
#define DAC_RESOLUTION    (9)

const PROGMEM uint16_t DACLookup_FullSine_9Bit[512] =
{
  2048, 2073, 2098, 2123, 2148, 2174, 2199, 2224,
  2249, 2274, 2299, 2324, 2349, 2373, 2398, 2423,
  2448, 2472, 2497, 2521, 2546, 2570, 2594, 2618,
  2643, 2667, 2690, 2714, 2738, 2762, 2785, 2808,
  2832, 2855, 2878, 2901, 2924, 2946, 2969, 2991,
  3013, 3036, 3057, 3079, 3101, 3122, 3144, 3165,
  3186, 3207, 3227, 3248, 3268, 3288, 3308, 3328,
  3347, 3367, 3386, 3405, 3423, 3442, 3460, 3478,
  3496, 3514, 3531, 3548, 3565, 3582, 3599, 3615,
  3631, 3647, 3663, 3678, 3693, 3708, 3722, 3737,
  3751, 3765, 3778, 3792, 3805, 3817, 3830, 3842,
  3854, 3866, 3877, 3888, 3899, 3910, 3920, 3930,
  3940, 3950, 3959, 3968, 3976, 3985, 3993, 4000,
  4008, 4015, 4022, 4028, 4035, 4041, 4046, 4052,
  4057, 4061, 4066, 4070, 4074, 4077, 4081, 4084,
  4086, 4088, 4090, 4092, 4094, 4095, 4095, 4095,
  4095, 4095, 4095, 4095, 4094, 4092, 4090, 4088,
  4086, 4084, 4081, 4077, 4074, 4070, 4066, 4061,
  4057, 4052, 4046, 4041, 4035, 4028, 4022, 4015,
  4008, 4000, 3993, 3985, 3976, 3968, 3959, 3950,
  3940, 3930, 3920, 3910, 3899, 3888, 3877, 3866,
  3854, 3842, 3830, 3817, 3805, 3792, 3778, 3765,
  3751, 3737, 3722, 3708, 3693, 3678, 3663, 3647,
  3631, 3615, 3599, 3582, 3565, 3548, 3531, 3514,
  3496, 3478, 3460, 3442, 3423, 3405, 3386, 3367,
  3347, 3328, 3308, 3288, 3268, 3248, 3227, 3207,
  3186, 3165, 3144, 3122, 3101, 3079, 3057, 3036,
  3013, 2991, 2969, 2946, 2924, 2901, 2878, 2855,
  2832, 2808, 2785, 2762, 2738, 2714, 2690, 2667,
  2643, 2618, 2594, 2570, 2546, 2521, 2497, 2472,
  2448, 2423, 2398, 2373, 2349, 2324, 2299, 2274,
  2249, 2224, 2199, 2174, 2148, 2123, 2098, 2073,
  2048, 2023, 1998, 1973, 1948, 1922, 1897, 1872,
  1847, 1822, 1797, 1772, 1747, 1723, 1698, 1673,
  1648, 1624, 1599, 1575, 1550, 1526, 1502, 1478,
  1453, 1429, 1406, 1382, 1358, 1334, 1311, 1288,
  1264, 1241, 1218, 1195, 1172, 1150, 1127, 1105,
  1083, 1060, 1039, 1017,  995,  974,  952,  931,
  910,  889,  869,  848,  828,  808,  788,  768,
  749,  729,  710,  691,  673,  654,  636,  618,
  600,  582,  565,  548,  531,  514,  497,  481,
  465,  449,  433,  418,  403,  388,  374,  359,
  345,  331,  318,  304,  291,  279,  266,  254,
  242,  230,  219,  208,  197,  186,  176,  166,
  156,  146,  137,  128,  120,  111,  103,   96,
  88,   81,   74,   68,   61,   55,   50,   44,
  39,   35,   30,   26,   22,   19,   15,   12,
  10,    8,    6,    4,    2,    1,    1,    0,
  0,    0,    1,    1,    2,    4,    6,    8,
  10,   12,   15,   19,   22,   26,   30,   35,
  39,   44,   50,   55,   61,   68,   74,   81,
  88,   96,  103,  111,  120,  128,  137,  146,
  156,  166,  176,  186,  197,  208,  219,  230,
  242,  254,  266,  279,  291,  304,  318,  331,
  345,  359,  374,  388,  403,  418,  433,  449,
  465,  481,  497,  514,  531,  548,  565,  582,
  600,  618,  636,  654,  673,  691,  710,  729,
  749,  768,  788,  808,  828,  848,  869,  889,
  910,  931,  952,  974,  995, 1017, 1039, 1060,
  1083, 1105, 1127, 1150, 1172, 1195, 1218, 1241,
  1264, 1288, 1311, 1334, 1358, 1382, 1406, 1429,
  1453, 1478, 1502, 1526, 1550, 1575, 1599, 1624,
  1648, 1673, 1698, 1723, 1747, 1772, 1797, 1822,
  1847, 1872, 1897, 1922, 1948, 1973, 1998, 2023
};

void setup(void)
{
  Serial.begin(9600);
  //Serial.println("Ola !");
  //Inicializa o MCP4725 no endereco 0x60 (oppure 61 quello col bordo blu)
  dac.begin(0x61);
  //Serial.println("Gerando onda senoidal");
}

void loop()
{
  uint16_t i;
  for (i = 0; i < 512; i++)
  {
    dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_9Bit[i])), false);
    //delay(7);
    //Serial.println(DACLookup_FullSine_9Bit[i]);  // NON VA, per serial plotter
  }
}

// Fonte https://www.arduinoecia.com.br/processing-conversor-digital-analogico-dac-mcp4725/






*/















// ESPERIMENTO #2
// Testato giugno 2020, ok con oscilloscopio in accoppiamento AC oppure DC 
// per 9 bit esce onda a 12,89 Hz e 4,80 Vpp come nell'esperimento 1
// per 8 bit esce onda a 25,79 Hz e 4,80 Vpp, file 20
// per 7 bit esce onda a 51,57 Hz e 4,80 Vpp, file 21
// per 6 bit esce onda a 103,1 Hz e idem, file 22
// per 5 bit esce onda a 206,3 Hz e 4,92 Vpp, file 23 e 24 con i gradini
// usato modulo blu ma penso sia lo stesso per gli altri



/**************************************************************************/
/*!
    @file     sinewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a sine wave with the MCP4725 DAC.

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/

/*

#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (5)

// Note: If flash space is tight a quarter sine wave is enough
//   to generate full sine and cos waves, but some additional
//   calculation will be required at each step after the first
//   quarter wave.                                              

const PROGMEM uint16_t DACLookup_FullSine_9Bit[512] =
{
  2048, 2073, 2098, 2123, 2148, 2174, 2199, 2224,
  2249, 2274, 2299, 2324, 2349, 2373, 2398, 2423,
  2448, 2472, 2497, 2521, 2546, 2570, 2594, 2618,
  2643, 2667, 2690, 2714, 2738, 2762, 2785, 2808,
  2832, 2855, 2878, 2901, 2924, 2946, 2969, 2991,
  3013, 3036, 3057, 3079, 3101, 3122, 3144, 3165,
  3186, 3207, 3227, 3248, 3268, 3288, 3308, 3328,
  3347, 3367, 3386, 3405, 3423, 3442, 3460, 3478,
  3496, 3514, 3531, 3548, 3565, 3582, 3599, 3615,
  3631, 3647, 3663, 3678, 3693, 3708, 3722, 3737,
  3751, 3765, 3778, 3792, 3805, 3817, 3830, 3842,
  3854, 3866, 3877, 3888, 3899, 3910, 3920, 3930,
  3940, 3950, 3959, 3968, 3976, 3985, 3993, 4000,
  4008, 4015, 4022, 4028, 4035, 4041, 4046, 4052,
  4057, 4061, 4066, 4070, 4074, 4077, 4081, 4084,
  4086, 4088, 4090, 4092, 4094, 4095, 4095, 4095,
  4095, 4095, 4095, 4095, 4094, 4092, 4090, 4088,
  4086, 4084, 4081, 4077, 4074, 4070, 4066, 4061,
  4057, 4052, 4046, 4041, 4035, 4028, 4022, 4015,
  4008, 4000, 3993, 3985, 3976, 3968, 3959, 3950,
  3940, 3930, 3920, 3910, 3899, 3888, 3877, 3866,
  3854, 3842, 3830, 3817, 3805, 3792, 3778, 3765,
  3751, 3737, 3722, 3708, 3693, 3678, 3663, 3647,
  3631, 3615, 3599, 3582, 3565, 3548, 3531, 3514,
  3496, 3478, 3460, 3442, 3423, 3405, 3386, 3367,
  3347, 3328, 3308, 3288, 3268, 3248, 3227, 3207,
  3186, 3165, 3144, 3122, 3101, 3079, 3057, 3036,
  3013, 2991, 2969, 2946, 2924, 2901, 2878, 2855,
  2832, 2808, 2785, 2762, 2738, 2714, 2690, 2667,
  2643, 2618, 2594, 2570, 2546, 2521, 2497, 2472,
  2448, 2423, 2398, 2373, 2349, 2324, 2299, 2274,
  2249, 2224, 2199, 2174, 2148, 2123, 2098, 2073,
  2048, 2023, 1998, 1973, 1948, 1922, 1897, 1872,
  1847, 1822, 1797, 1772, 1747, 1723, 1698, 1673,
  1648, 1624, 1599, 1575, 1550, 1526, 1502, 1478,
  1453, 1429, 1406, 1382, 1358, 1334, 1311, 1288,
  1264, 1241, 1218, 1195, 1172, 1150, 1127, 1105,
  1083, 1060, 1039, 1017,  995,  974,  952,  931,
   910,  889,  869,  848,  828,  808,  788,  768,
   749,  729,  710,  691,  673,  654,  636,  618,
   600,  582,  565,  548,  531,  514,  497,  481,
   465,  449,  433,  418,  403,  388,  374,  359,
   345,  331,  318,  304,  291,  279,  266,  254,
   242,  230,  219,  208,  197,  186,  176,  166,
   156,  146,  137,  128,  120,  111,  103,   96,
    88,   81,   74,   68,   61,   55,   50,   44,
    39,   35,   30,   26,   22,   19,   15,   12,
    10,    8,    6,    4,    2,    1,    1,    0,
     0,    0,    1,    1,    2,    4,    6,    8,
    10,   12,   15,   19,   22,   26,   30,   35,
    39,   44,   50,   55,   61,   68,   74,   81,
    88,   96,  103,  111,  120,  128,  137,  146,
   156,  166,  176,  186,  197,  208,  219,  230,
   242,  254,  266,  279,  291,  304,  318,  331,
   345,  359,  374,  388,  403,  418,  433,  449,
   465,  481,  497,  514,  531,  548,  565,  582,
   600,  618,  636,  654,  673,  691,  710,  729,
   749,  768,  788,  808,  828,  848,  869,  889,
   910,  931,  952,  974,  995, 1017, 1039, 1060,
  1083, 1105, 1127, 1150, 1172, 1195, 1218, 1241,
  1264, 1288, 1311, 1334, 1358, 1382, 1406, 1429,
  1453, 1478, 1502, 1526, 1550, 1575, 1599, 1624,
  1648, 1673, 1698, 1723, 1747, 1772, 1797, 1822,
  1847, 1872, 1897, 1922, 1948, 1973, 1998, 2023
};

const PROGMEM uint16_t DACLookup_FullSine_8Bit[256] =
{
  2048, 2098, 2148, 2198, 2248, 2298, 2348, 2398,
  2447, 2496, 2545, 2594, 2642, 2690, 2737, 2784,
  2831, 2877, 2923, 2968, 3013, 3057, 3100, 3143,
  3185, 3226, 3267, 3307, 3346, 3385, 3423, 3459,
  3495, 3530, 3565, 3598, 3630, 3662, 3692, 3722,
  3750, 3777, 3804, 3829, 3853, 3876, 3898, 3919,
  3939, 3958, 3975, 3992, 4007, 4021, 4034, 4045,
  4056, 4065, 4073, 4080, 4085, 4089, 4093, 4094,
  4095, 4094, 4093, 4089, 4085, 4080, 4073, 4065,
  4056, 4045, 4034, 4021, 4007, 3992, 3975, 3958,
  3939, 3919, 3898, 3876, 3853, 3829, 3804, 3777,
  3750, 3722, 3692, 3662, 3630, 3598, 3565, 3530,
  3495, 3459, 3423, 3385, 3346, 3307, 3267, 3226,
  3185, 3143, 3100, 3057, 3013, 2968, 2923, 2877,
  2831, 2784, 2737, 2690, 2642, 2594, 2545, 2496,
  2447, 2398, 2348, 2298, 2248, 2198, 2148, 2098,
  2048, 1997, 1947, 1897, 1847, 1797, 1747, 1697,
  1648, 1599, 1550, 1501, 1453, 1405, 1358, 1311,
  1264, 1218, 1172, 1127, 1082, 1038,  995,  952,
   910,  869,  828,  788,  749,  710,  672,  636,
   600,  565,  530,  497,  465,  433,  403,  373,
   345,  318,  291,  266,  242,  219,  197,  176,
   156,  137,  120,  103,   88,   74,   61,   50,
    39,   30,   22,   15,   10,    6,    2,    1,
     0,    1,    2,    6,   10,   15,   22,   30,
    39,   50,   61,   74,   88,  103,  120,  137,
   156,  176,  197,  219,  242,  266,  291,  318,
   345,  373,  403,  433,  465,  497,  530,  565,
   600,  636,  672,  710,  749,  788,  828,  869,
   910,  952,  995, 1038, 1082, 1127, 1172, 1218,
  1264, 1311, 1358, 1405, 1453, 1501, 1550, 1599,
  1648, 1697, 1747, 1797, 1847, 1897, 1947, 1997
};

const PROGMEM uint16_t DACLookup_FullSine_7Bit[128] =
{
  2048, 2148, 2248, 2348, 2447, 2545, 2642, 2737,
  2831, 2923, 3013, 3100, 3185, 3267, 3346, 3423,
  3495, 3565, 3630, 3692, 3750, 3804, 3853, 3898,
  3939, 3975, 4007, 4034, 4056, 4073, 4085, 4093,
  4095, 4093, 4085, 4073, 4056, 4034, 4007, 3975,
  3939, 3898, 3853, 3804, 3750, 3692, 3630, 3565,
  3495, 3423, 3346, 3267, 3185, 3100, 3013, 2923,
  2831, 2737, 2642, 2545, 2447, 2348, 2248, 2148,
  2048, 1947, 1847, 1747, 1648, 1550, 1453, 1358,
  1264, 1172, 1082,  995,  910,  828,  749,  672,
   600,  530,  465,  403,  345,  291,  242,  197,
   156,  120,   88,   61,   39,   22,   10,    2,
     0,    2,   10,   22,   39,   61,   88,  120,
   156,  197,  242,  291,  345,  403,  465,  530,
   600,  672,  749,  828,  910,  995, 1082, 1172,
  1264, 1358, 1453, 1550, 1648, 1747, 1847, 1947
};

const PROGMEM uint16_t DACLookup_FullSine_6Bit[64] =
{
  2048, 2248, 2447, 2642, 2831, 3013, 3185, 3346,
  3495, 3630, 3750, 3853, 3939, 4007, 4056, 4085,
  4095, 4085, 4056, 4007, 3939, 3853, 3750, 3630,
  3495, 3346, 3185, 3013, 2831, 2642, 2447, 2248,
  2048, 1847, 1648, 1453, 1264, 1082,  910,  749,
   600,  465,  345,  242,  156,   88,   39,   10,
     0,   10,   39,   88,  156,  242,  345,  465,
   600,  749,  910, 1082, 1264, 1453, 1648, 1847
};

const PROGMEM uint16_t DACLookup_FullSine_5Bit[32] =
{
  2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056,
  4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
  2048, 1648, 1264,  910,  600,  345,  156,   39,
     0,   39,  156,  345,  600,  910, 1264, 1648
};

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61 ecco sono questi quelli che ho io
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x61);  // 61 per il modulo a bordo blu, 60 per gli altri 

  Serial.println("Generating a sine wave");
}

void loop(void) {
    uint16_t i;

    // Push out the right lookup table, depending on the selected resolution
    #if DAC_RESOLUTION == 5
      for (i = 0; i < 32; i++)
      {
        dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_5Bit[i])), false);
        //Serial.println(pgm_read_word(&(DACLookup_FullSine_5Bit[i])));
        //Serial.println(analogRead(A0));
      }
    #elif DAC_RESOLUTION == 6
      for (i = 0; i < 64; i++)
      {
        dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_6Bit[i])), false);
        //Serial.println(pgm_read_word(&(DACLookup_FullSine_6Bit[i])));
        //Serial.println(analogRead(A0));
      }
    #elif DAC_RESOLUTION == 7
      for (i = 0; i < 128; i++)
      {
        dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_7Bit[i])), false);
        //Serial.println(pgm_read_word(&(DACLookup_FullSine_7Bit[i])));
        //Serial.println(analogRead(A0));
      }
    #elif DAC_RESOLUTION == 9
      for (i = 0; i < 512; i++)
      {
        dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_9Bit[i])), false);
        //Serial.println(pgm_read_word(&(DACLookup_FullSine_9Bit[i])));
        //Serial.println(analogRead(A0));
      }
    #else    // Use 8-bit data if nothing else is specified
      for (i = 0; i < 256; i++)
      {
        dac.setVoltage(pgm_read_word(&(DACLookup_FullSine_8Bit[i])), false);
        //Serial.println(pgm_read_word(&(DACLookup_FullSine_8Bit[i])));
        //Serial.println(analogRead(A0));
      }
    #endif
}

// Fonte esempio libreria Adafruit, usato anche da WRkits


*/















// ESPERIMENTO #3
// Testato giugno 2020, ok con oscilloscopio in accoppiamento AC oppure DC 
// esce onda con bassa frequenza 798 mHz e 4,84 Vpp
// usato modulo blu ma penso sia lo stesso per gli altri



/**************************************************************************/
/*! 
    @file     trianglewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a triangle wave with the MCP4725 DAC.   

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935
 
    Adafruit invests time and resources providing this open source code, 
    please support Adafruit and open-source hardware by purchasing 
    products from Adafruit!
*/
/**************************************************************************/

/*

#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x61);  // 61 per il modulo a bordo blu, 60 per gli altri
    
  Serial.println("Generating a triangle wave");
}

void loop(void) {
    uint32_t counter;
    // Run through the full 12-bit scale for a triangle wave
    for (counter = 0; counter < 4095; counter++)
    {
      dac.setVoltage(counter, false);
      //Serial.println(analogRead(A0));
    }
    for (counter = 4095; counter > 0; counter--)
    {
      dac.setVoltage(counter, false);
      //Serial.println(analogRead(A0));
    }
}

// Fonte esempio da libreria Adafruit, usato anche da Aliverti

*/
















/*

// FATTO ESPERIMENTO MA SENZA POTENZIOMETRO IN A0 QUINDI SOLO RUMORE...


// Analog to analog

#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (9)

void setup(void) {
  Serial.begin(9600);  
  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  // per le schede cinesi è 0x60
  dac.begin(0x61);   // quella blu 61 le altre 60  
}

void loop(void) {
  int val = analogRead(A0);
  val = map(val, 0, 1023, 0, 4095);
  // Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
  dac.setVoltage(val, false);  
  Serial.println(val);
  delay(50);
}

// Fonte Aliverti

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

// GENERATORE DI ONDA TRIANGOLARE

// Modulo con chip PCF8591 - Convertitore analogico digitale DAC (Vcc = +5V) 

// Per vedere l'onda su PC con Plotter Seriale il terminale OUT del modulo va sul pin analogico A0 
// Altrimenti usare oscilloscopio? Ma col dso138 non esce l'onda triangolare 


#include "Wire.h"
#define PCF8591 (0x48 >> 1) // I2C bus address


void setup(){
  Serial.begin(9600);
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
    Serial.println(x);
  }

  for (int i=199; i>=0; --i){
    Wire.beginTransmission(PCF8591); // wake up PCF8591
    Wire.write(0x40); // control byte - turn on DAC (binary 1000000)
    Wire.write(100*i); // value to send to DAC
    Wire.endTransmission(); // end tranmission
    x = analogRead(0);
    Serial.println(x);
  }
}


// Fonte https://tronixstuff.com/2013/06/17/tutorial-arduino-and-pcf8591-adc-dac-ic/


*/


















/*

// ESPERIMENTO #4
// Testato giugno 2020, ok con oscilloscopio in accoppiamento AC oppure DC 
// esce onda con bassa frequenza 1,60 Hz e 0,430 Vpp se manteniamo serial print
// senza serial print esce a 24 Hz e 0,412 Vpp però ho messo limite banda 20 MHz per togliere rumore, file 25


// GENERATORE DI ONDA SINUSOIDALE

// Modulo con chip PCF8591 - Convertitore analogico digitale DAC (Vcc = +5V) 

// Per vedere l'onda su PC con Plotter Seriale il terminale OUT del modulo va sul pin analogico A0 
// Altrimenti usare oscilloscopio. Col dso138 si vede direi bene!


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
    //    https://www.gammon.com.au/forum/?id=10896
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
     
     
    void setup()
    {
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




