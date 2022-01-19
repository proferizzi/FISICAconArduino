// #1 ESPERIMENTO DI CINEMATICA: LEGGE ORARIA DI UN CORPO IN MOTO, in tempo reale
// Materiale: microcontrollore su scheda, cavo USB e PC (con IDE e Serial Plotter)
//            sensore a ultrasuoni HCSR04, breadboard e cavetti
//
// Usiamo un sensore a ultrasuoni per misurare il tempo di andata e ritorno di un'onda sonora  
// quando si riflette contro un oggetto e poi calcoliamo dunque la posizione di tale oggetto
// a intervalli di tempo regolari, visualizzandola su monitor seriale o plotter seriale.
// Questo grazie alla conoscenza della velocità del suono in aria secca, pari a 340 m/s circa.
//
// Circuito: 
// Se si ha la scheda UNO inserire il sensore nei quattro pin scritti qui sotto,
// altrimenti con altre schede come la NANO si usino cavetti e breadboard.

#define vccPin 8
#define trigPin 9
#define echoPin 10
#define gndPin 11

long duration = 0;  // duration in microsecondi 
float distance = 0; // distance in cm

int const fsize = 4;
int fil [fsize];
int i=0;
float avg = 0.0;


void setup() {
  Serial.begin (9600);
  
  pinMode(vccPin, OUTPUT);
  digitalWrite(vccPin, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
}


void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);
  //if(duration == 0){ 
    //pinMode(echoPin, OUTPUT); 
    //digitalWrite(echoPin, LOW); 
    //delayMicroseconds(200);
    //pinMode(echoPin, INPUT); 
  //}

  fil[i] = duration;
  if(i < (fsize-1)) i++;
  else i = 0;
  avg = 0;
  for(int j=0; j<fsize; j++){
    avg += (float)fil[j];
  }
  avg = avg / (float)(fsize);
  
  distance = avg/2.0 * 0.0343; // calcolo con velocità del suono

  if((distance <= 40)&&(distance > 0)){  // limite inserito per visualizzare bene il grafico
    Serial.print(distance);
    delay(60);  
  }
}

// Fonte per filtro Aliverti https://www.youtube.com/watch?v=cnQSCPUgiA4

















/*

// #2 ESPERIMENTO CON SERVOMOTORE CONTROLLATO TRAMITE POTENZIOMETRO 
//
// L'uso dei servomotori permette di controllare la posizione angolare, in vista di realizzare un radar.
//
// Circuito: 
// Attacchiamo il pin centrale del potenziometro al pin A0 e i pin esterni al +5V e a Terra.
// Alimentiamo il servomotore a +5V e a Terra, poi inseriamo al pin 9 il cavo marrone rimanente.

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin


void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


void loop() {
  val = analogRead(potpin);     // reads the value of the potentiometer (value between 0 and 1023)
  //Serial.println(val);
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  Serial.println(val); // è utile per usare serial plotter
  myservo.write(val);
  delay(15);                           // waits for the servo to get there
}

// Fonte "Knob.ino" dagli esempi dell'IDE
// Se manca libreria "Servo.h" bisogna inserirla nella cartella "Libraries" dell'IDE



*/






















/*


// #3 RADAR CON SENSORE A ULTRASUONI E SERVOMOTORE - bozza
//
// Il servomotore ruoterà sul piano orizzontale, individuando ostacoli e mostrando
// l'utilità della grandezza fisica "vettore posizione".
// ATTENZIONE: SICCOME IL SENSORE A ULTRASUONI RICEVE I DATI OTTIMAMENTE CON SUPERFICI 
// PERPENDICOLARI ALLA DIREZIONE DELL'ONDA SONORA CHE INVIA, GLI OSTACOLI NON POSSONO ESSERE
// ECCESSIVAMENTE INCLINATI E LE MISURE DI DISTANZE DALL'ORIGINE ANDREBBERO TESTATE CON UN METRO

// Circuito: combinare quanto imparato negli esperimenti precedenti  


// ANGOLI MINIMO E MASSIMO: RADAR 15° E 165°
int min = 15;
int max = 165;

// Includes the Servo library
#include <Servo.h>. 

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
// Variables for the duration and the distance
long duration;
int distance;

Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
}
void loop() {
  // rotates the servo motor from min to max degrees
  for(int i=min;i<=max;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from max to min degrees
  for(int i=max;i>min;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){   
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}


*/
  
  
  
  
  
  
  
  
  
  
  
  
  








/*

// #4 ESPERIMENTO BONUS! BILANCIERE AUTOMATICO (ROTAIA CON PALLINA) CON PID, HCSR04 E SERVOMOTORE
// Per una dimostrazione vedere     https://www.youtube.com/watch?v=M9wMnrUXKdo     

// NB:  angolo del servo tale per cui si ha rotaia orizzontale: 120 gradi
//      distanza della pallina all'equilibrio: 10 cm
//      distanza massima della pallina dal sensore a ultrasuoni: 20 cm

// Fonte http://mechatronicstutorials.blogspot.com/2014/07/balancing-of-ball-on-beam-using-arduino.html


#include<Servo.h>
#include<PID_v1.h>

const int servoPin = 5;   // pin del Servo

float Kp = 2.0;     // Guadagno iniziale della componente proporzionale
float Ki = 0.2;     // Guadagno iniziale della componente integrale
float Kd = 1.2;     // Guadagno iniziale della componente derivativa

double Setpoint, Input, Output, ServoOutput;                                       

// Inizializza l'oggetto PID, nella classe PID
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);   
  
Servo myServo;      // Inizializza il Servo

void setup() {
  Serial.begin(9600);    
  myServo.attach(servoPin);       // Attiva il Servo
  // Chiama la funzione readPosition() 
  // e fissa la posizione della pallina come input dell'algoritmo PID
  Input = leggiPosizione();         
  
  myPID.SetMode(AUTOMATIC);         // Settaggio in automatico 
                                    // dell'oggetto PID in myPID 
  myPID.SetOutputLimits(-80,80);    // Settaggio di limiti 
}

void loop(){
  Setpoint = 10;    // distanza pallina equilibrio orizzontale
  Input = leggiPosizione();                                            
 
  myPID.Compute();    // Computa l'output tra min e max angolo
  
  ServoOutput=120+Output;         // il primo addendo sono i gradi presenti 
                                  // a rotaia orizzontale 
  myServo.write(ServoOutput);     // Scrive sul servo il valore dell'output  
}
      
float leggiPosizione() {
  delay(40);                 // Non mettere troppo basso altrimenti 
                             // gli echi si sovrapporranno      
  const int pingPin = 3;
  #define echoPin 2 // Echo Pin
  long duration, cm;
  unsigned long now = millis();
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = duration/(58.2);
  if(cm > 20){     // la posizione massima per la pallina
    cm = 20;
  }
  Serial.println(cm);
  return cm;     // La funzione ritorna il valore di distanza
}

*/












// #5 ESPERIMENTO BONUS! CAPACIMETRO PER CONDENSATORI

/* ARDUINO... "RCTiming_capacitance_meter.ino"
 * Utilizziamo Arduino come capacimetro per misurare la CAPACITA' di un CONDENSATORE.
 * La formula base è associata al tempo di carica del condensatore in un circuito RC che vale
 * " T = R * C " per cui se conosciamo tale tempo e scegliamo bene la RESISTENZA del resistore
 * possiamo dividere il primo con la seconda e ottenere la capacità. Inoltre consideriamo il
 * voltaggio del condensatore in un tempo di carica pari al 63,2% del voltaggio usato per la carica.
 *
 * Circuito:
 * Scegliamo una fila della breadboard come "nodo centrale" e inseriamo il condensatore tra tale nodo
 * (polo positivo se abbiamo un condensatore elettrolitico, ATTENZIONE RISCHIO ROTTURA CONDENSATORE)
 * e la Terra. Inseriamo poi il resistore tra il nodo e il pin 13 responsabile della carica.
 * Inseriamo una resistenza di 220 Ω (Ohm) tra il pin 11 responsabile della scarica e il nodo.  
 * Infine colleghiamo il pin A0, da cui misureremo il voltaggio, ancora una volta al nodo centrale.
 *
 * This example code is in the public domain (by Badger). 
 * https://www.arduino.cc/en/Tutorial/CapacitanceMeter                         */

/*
#define analogPin      0          // analog pin for measuring capacitor voltage
#define chargePin      13         // pin to charge the capacitor 
#define dischargePin   11         // pin to discharge the capacitor

#define resistorValue  22000.0F   // CAMBIARE QUESTO VALORE IN BASE ALLA RESISTENZA DEL RESISTORE
                                  // IL SIMBOLO "F" CI DICE CHE ABBIAMO UN VALORE "FLOATING"
                                  // da non confondere con l'unità di misura "Farad" della capacità!

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                // floating point variable to preserve precision, make calculations
float nanoFarads;

void setup(){
  pinMode(chargePin, OUTPUT);     // set chargePin to output
  digitalWrite(chargePin, LOW);  

  Serial.begin(9600);             // initialize serial transmission for debugging
}

void loop(){
  digitalWrite(chargePin, HIGH);  // set chargePin HIGH and capacitor charging
  startTime = millis();

  while(analogRead(analogPin) < 648){       // 647 is 63.2% of 1023 (full scale voltage) 
  }

  elapsedTime= millis() - startTime;
 // convert milliseconds to seconds ( 10^-3 ) and Farads to microFarads ( 10^6 ),  net 10^3 (1000)  
  microFarads = ((float)elapsedTime / resistorValue) * 1000;   
  Serial.print(elapsedTime);       // print the value to serial port
  Serial.print(" ms    ");         // print units and carriage return


  if (microFarads > 1){
    Serial.print((long)microFarads);       // print the value to serial port
    Serial.println(" microFarads");         // print units and carriage return
  }
  else
  {
    // if value is smaller than one microFarad, convert to nanoFarads (10^-9 Farad). 
    // This is  a workaround because Serial.print will not print floats

    nanoFarads = microFarads * 1000.0;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)
    Serial.print((long)nanoFarads);         // print the value to serial port
    Serial.println(" nanoFarads");          // print units and carriage return
  }

  // dicharge the capacitor  
  digitalWrite(chargePin, LOW);             // set charge pin to  LOW 
  pinMode(dischargePin, OUTPUT);            // set discharge pin to output 
  digitalWrite(dischargePin, LOW);          // set discharge pin LOW 
  while(analogRead(analogPin) > 0){         // wait until capacitor is completely discharged
  }

  pinMode(dischargePin, INPUT);            // set discharge pin back to input
}



*/














/*

// ATTENZIONE QUESTA DI SEGUITO È LA LIBRERIA "Servo.h" DA COPIARE E INCOLLARE IN UN FILE OMONIMO

// inizio copia


#ifndef Servo_h
#define Servo_h

#include <inttypes.h>

// Architecture specific include
#if defined(ARDUINO_ARCH_AVR)
#include "avr/ServoTimers.h"
#elif defined(ARDUINO_ARCH_SAM)
#include "sam/ServoTimers.h"
#elif defined(ARDUINO_ARCH_SAMD)
#include "samd/ServoTimers.h"
#elif defined(ARDUINO_ARCH_STM32F4)
#include "stm32f4/ServoTimers.h"
#elif defined(ARDUINO_ARCH_NRF52)
#include "nrf52/ServoTimers.h"
#elif defined(ARDUINO_ARCH_MEGAAVR)
#include "megaavr/ServoTimers.h"
#else
#error "This library only supports boards with an AVR, SAM, SAMD, NRF52 or STM32F4 processor."
#endif

#define Servo_VERSION           2     // software version of this library

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds 

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer 
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index

#if !defined(ARDUINO_ARCH_STM32F4)

typedef struct  {
  uint8_t nbr        :6 ;             // a pin number from 0 to 63
  uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false 
} ServoPin_t   ;  

typedef struct {
  ServoPin_t Pin;
  volatile unsigned int ticks;
} servo_t;

class Servo
{
public:
  Servo();
  uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes. 
  void detach();
  void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
  void writeMicroseconds(int value); // Write pulse width in microseconds 
  int read();                        // returns current pulse width as an angle between 0 and 180 degrees
  int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
  bool attached();                   // return true if this servo is attached, otherwise false 
private:
   uint8_t servoIndex;               // index into the channel data for this servo
   int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH    
   int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH   
};

#endif
#endif


// fine copia

*/








