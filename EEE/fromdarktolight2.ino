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







// #2 ESPERIMENTO CON SERVOMOTORE CONTROLLATO TRAMITE POTENZIOMETRO 



 *
 * Circuito: 
 * * Attacchiamo il pin centrale del potenziometro al pin A0 
 * e i pin esterni uno al +5V e l'altro a Terra.
 * 
 * Alimentiamo il servomotore a +5V e a Terra, poi inseriamo al pin 9 il terzo cavo rimanente.
 *
 * This example code is in the public domain (by Rinott, Fitzgerald).
 * http://www.arduino.cc/en/Tutorial/Knob                              */

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



/* ... E LE LEGGI DELLA FISICA
 * osservazione: l'uso dei servomotori mi permette di controllare la posizione angolare. 
 * ipotesi: posso realizzare un braccio robotico (con 2 servo), un radar (anche con sensore a ultrasuoni)
 *          oppure uno strumento che mi smisuri l'altezza di un oggetto (anche con sensore a ultrausoni).
 * esperimento: realizziamo uno di questi progetti. 
 * riflessioni: come usare quanto realizzato per esperimenti di fisica? ... */





// Se manca libreria "Servo.h" bisogna inserirla nella cartella "Libraries" dell'IDE









// ATTENZIONE QUESTA DI SEGUITO È LA LIBRERIA "Servo.h" DA COPIARE E INCOLLARE IN UN FILE OMONIMO

// inizio copia



/*
  Servo.h - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
  Copyright (c) 2009 Michael Margolis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/* 
  A servo is activated by creating an instance of the Servo class passing 
  the desired pin to the attach() method.
  The servos are pulsed in the background using the value most recently 
  written using the write() method.

  Note that analogWrite of PWM on pins associated with the timer are 
  disabled when the first servo is attached.
  Timers are seized as needed in groups of 12 servos - 24 servos use two 
  timers, 48 servos will use four.
  The sequence used to sieze timers is defined in timers.h

  The methods are:

    Servo - Class for manipulating servo motors connected to Arduino pins.

    attach(pin )  - Attaches a servo motor to an i/o pin.
    attach(pin, min, max  ) - Attaches to a pin setting min and max values in microseconds
    default min is 544, max is 2400  
 
    write()     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
    writeMicroseconds() - Sets the servo pulse width in microseconds 
    read()      - Gets the last written servo pulse width as an angle between 0 and 180. 
    readMicroseconds()   - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
    attached()  - Returns true if there is a servo attached. 
    detach()    - Stops an attached servos from pulsing its i/o pin. 
 */

#ifndef Servo_h
#define Servo_h

#include <inttypes.h>

/* 
 * Defines for 16 bit timers used with  Servo library 
 *
 * If _useTimerX is defined then TimerX is a 16 bit timer on the current board
 * timer16_Sequence_t enumerates the sequence that the timers should be allocated
 * _Nbr_16timers indicates how many 16 bit timers are available.
 */

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


































/* 8. ARDUINO... "braccio.ino" 
* Si usano due servomotori, magari con matite da attaccare al braccio per mostrare
* il moto circolare uniforme e la velocità angolare costante anche per traiettorie 
* con raggi differenti (cioè il problema della giostra...).
* Se non ci sono abbastanza potenziometri si potrebbe usare un joystick 
* o un giroscopio/accelerometro MPU6050 xxx...         
*
* Circuito: combinare quanto imparato negli esperimenti precedenti */



#include <Servo.h>

Servo myservo1;  // rotazione sul piano di base, (orizzontale)
Servo myservo2;  // rotazione sul piano dell'altezza angolare, (verticale)

int potpin1 = 0;  // analog pin used to connect the potentiometer
int potpin2 = 1;
int val1;    // variable to read the value from the analog pin
int val2;


void setup() {
  Serial.begin(9600);
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
}

void loop() {
  val1 = analogRead(potpin1);     // reads the value of the potentiometer (value between 0 and 1023)
  //Serial.println(val1);
  val1 = map(val1,0,1023, 0, 180);
  myservo1.write(val1);
  
  val2 = analogRead(potpin2);
  val2 = map(val2, 0, 1023, 70, 130);     // valori limite trovati empiricamente
  myservo2.write(val2);
  delay(15);  // waits for the servo to get there
  
  Serial.print(val1);
  Serial.print(" ");
  Serial.println(val2); // è utile per usare serial plotter
}



















/* 9. ARDUINO ... "altezza.ino" ---> ANCORA DA TESTARE PER VEDERE SE FUNZIONA xxx
 * Abbiamo un sensore a ultrasuoni posto ad altezza costante "k" dal tavolo,
 * che ruota su un piano verticale controllato da un potenziometro,
 * grazie a un servomotore. Per calibrare a 90° circa l'orizzontale di tale sensore
 * utilizziamo il potenziometro e il servomotore staccato dal sostegno, cerchiamo
 * sul monitor il valore di 90° e fissiamo poi il servomotore al sostegno stesso,
 * in modo che sia circa orizzontale (è possibile rifinire poi col potenziometro).
 *
 * Appoggiamo un oggetto sul tavolo posto a distanza "d" dal sensore a ultrasuoni.
 * Misuriamo tale distanza "d" e l'angolo zenitale "alfa" del punto più alto dell'oggetto.
 * TALE ANGOLO NON PUÒ ESSERE TROPPO ELEVATO PERCHÉ IL SENSORE A ULTRASUONI RICEVE I DATI
 * OTTIMAMENTE CON SUPERFICI PERPENDICOLARI ALLA DIREZIONE DELL'ONDA SONORA CHE INVIA. 
 * La differenza tra "alfa" e 90° (circa) produce un angolo che, con la trigonometria, 
 * ci permette di trovare una lunghezza che sommata a "k" ci fornisce l'altezza "h" dell'oggetto. 
 * In formula:        h = k + d tan(alfa - 90°)
 *
 * Circuito: combinare quanto imparato negli esperimenti precedenti      */
 
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

const int trigPin = 10;
const int echoPin = 11;
float duration, cm;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.println("Sensibilità 0,25 cm circa");
  delay(1000);
}


void loop() {
   
  val = analogRead(potpin);     // reads the value of the potentiometer (value between 0 and 1023)
  //Serial.println(val);
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);
  delay(15);                           // waits for the servo to get there
  Serial.print(val); 
  Serial.print(" gradi; ");
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  if(cm>0 && cm<150){
    Serial.print(cm);
    Serial.print(" cm"); 
    Serial.println();
  }
  else{
    Serial.println("fuori portata")
  }
  delay(100);
}

float microsecondsToCentimeters(float microseconds){
  return microseconds * 0.034 / 2;
}


 
 
 
 
 
 
 
 
 
 
 
 
 
 




/* 10. ARDUINO... "radar.ino"
* Si utilizza un servomotore e un sensore a ultrasuoni. Serve anche il software PROCESSING.
*
* Il servomotore ruoterà sul piano orizzontale, individuando ostacoli e mostrando
* l'utilità della grandezza fisica "vettore posizione".
* ATTNZIONE: SICCOME IL SENSORE A ULTRASUONI RICEVE I DATI OTTIMAMENTE CON SUPERFICI 
* PERPENDICOLARI ALLA DIREZIONE DELL'ONDA SONORA CHE INVIA, GLI OSTACOLI NON POSSONO ESSERE
* ECCESSIVAMENTE INCLINATI E LE MISURE DI DISTANZE DALL'ORIGINE ANDREBBERO TESTATE CON UN METRO xxx
*  
* Circuito: combinare quanto imparato negli esperimenti precedenti  
*
* Fonte: https://howtomechatronics.com/projects/arduino-radar-project/        */

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






/*

// FILE DI PROCESSING

// Arduino Radar Project   Updated version. Fits any screen resolution!
// Just change the values in the size() function, with your screen resolution.
// by Dejan Nedelkovski, www.HowToMechatronics.com

import processing.serial.*; // imports library for serial communication
import java.awt.event.KeyEvent; // imports library for reading the data from the serial port
import java.io.IOException;

Serial myPort; // defines Object Serial
// defubes variables
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;
PFont orcFont;

void setup() {
  
 size (1600, 800); // ***CHANGE THIS TO YOUR SCREEN RESOLUTION***
 smooth();
 myPort = new Serial(this,"/dev/ttyACM1", 9600); // starts the serial communication
 myPort.bufferUntil('.'); // reads the data from the serial port up to the character '.'. So actually it reads this: angle,distance.
 orcFont = loadFont("LucidaSans-48.vlw");
}

void draw() {
  
  fill(98,245,31);
  textFont(orcFont);
  // simulating motion blur and slow fade of the moving line
  noStroke();
  fill(0,4); 
  rect(0, 0, width, height-height*0.065); 
  
  fill(98,245,31); // green color
  // calls the functions for drawing the radar
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

void serialEvent (Serial myPort) { // starts reading data from the Serial Port
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('.');
  data = data.substring(0,data.length()-1);
  
  index1 = data.indexOf(","); // find the character ',' and puts it into the variable "index1"
  angle= data.substring(0, index1); // read the data from position "0" to position of the variable index1 or thats the value of the angle the Arduino Board sent into the Serial Port
  distance= data.substring(index1+1, data.length()); // read the data from position "index1" to the end of the data pr thats the value of the distance
  
  // converts the String variables into Integer
  iAngle = int(angle);
  iDistance = int(distance);
}

void drawRadar() {
  pushMatrix();
  translate(width/2,height-height*0.074); // moves the starting coordinats to new location
  noFill();
  strokeWeight(2);
  stroke(98,245,31);
  // draws the arc lines
  arc(0,0,(width-width*0.0625),(width-width*0.0625),PI,TWO_PI);
  arc(0,0,(width-width*0.27),(width-width*0.27),PI,TWO_PI);
  arc(0,0,(width-width*0.479),(width-width*0.479),PI,TWO_PI);
  arc(0,0,(width-width*0.687),(width-width*0.687),PI,TWO_PI);
  // draws the angle lines
  line(-width/2,0,width/2,0);
  line(0,0,(-width/2)*cos(radians(30)),(-width/2)*sin(radians(30)));
  line(0,0,(-width/2)*cos(radians(60)),(-width/2)*sin(radians(60)));
  line(0,0,(-width/2)*cos(radians(90)),(-width/2)*sin(radians(90)));
  line(0,0,(-width/2)*cos(radians(120)),(-width/2)*sin(radians(120)));
  line(0,0,(-width/2)*cos(radians(150)),(-width/2)*sin(radians(150)));
  line((-width/2)*cos(radians(30)),0,width/2,0);
  popMatrix();
}

void drawObject() {
  pushMatrix();
  translate(width/2,height-height*0.074); // moves the starting coordinats to new location
  strokeWeight(9);
  stroke(255,10,10); // red color
  pixsDistance = iDistance*((height-height*0.1666)*0.025); // covers the distance from the sensor from cm to pixels
  // limiting the range to 40 cms
  if(iDistance<40){
    // draws the object according to the angle and the distance
  line(pixsDistance*cos(radians(iAngle)),-pixsDistance*sin(radians(iAngle)),(width-width*0.505)*cos(radians(iAngle)),-(width-width*0.505)*sin(radians(iAngle)));
  }
  popMatrix();
}

void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30,250,60);
  translate(width/2,height-height*0.074); // moves the starting coordinats to new location
  line(0,0,(height-height*0.12)*cos(radians(iAngle)),-(height-height*0.12)*sin(radians(iAngle))); // draws the line according to the angle
  popMatrix();
}

void drawText() { // draws the texts on the screen
  
  pushMatrix();
  if(iDistance>40) {
  noObject = "Out of Range";
  }
  else {
  noObject = "In Range";
  }
  fill(0,0,0);
  noStroke();
  rect(0, height-height*0.0648, width, height);
  fill(98,245,31);
  textSize(25);
  
  text("10cm",width-width*0.3854,height-height*0.0833);
  text("20cm",width-width*0.281,height-height*0.0833);
  text("30cm",width-width*0.177,height-height*0.0833);
  text("40cm",width-width*0.0729,height-height*0.0833);
  textSize(40);
  text("Object: " + noObject, width-width*0.875, height-height*0.0277);
  text("Angle: " + iAngle +" °", width-width*0.48, height-height*0.0277);
  text("Distance: ", width-width*0.26, height-height*0.0277);
  if(iDistance<40) {
  text("        " + iDistance +" cm", width-width*0.225, height-height*0.0277);
  }
  textSize(25);
  fill(98,245,60);
  translate((width-width*0.4994)+width/2*cos(radians(30)),(height-height*0.0907)-width/2*sin(radians(30)));
  rotate(-radians(-60));
  text("30°",0,0);
  resetMatrix();
  translate((width-width*0.503)+width/2*cos(radians(60)),(height-height*0.0888)-width/2*sin(radians(60)));
  rotate(-radians(-30));
  text("60°",0,0);
  resetMatrix();
  translate((width-width*0.507)+width/2*cos(radians(90)),(height-height*0.0833)-width/2*sin(radians(90)));
  rotate(radians(0));
  text("90°",0,0);
  resetMatrix();
  translate(width-width*0.513+width/2*cos(radians(120)),(height-height*0.07129)-width/2*sin(radians(120)));
  rotate(radians(-30));
  text("120°",0,0);
  resetMatrix();
  translate((width-width*0.5104)+width/2*cos(radians(150)),(height-height*0.0574)-width/2*sin(radians(150)));
  rotate(radians(-60));
  text("150°",0,0);
  popMatrix(); 
}

*/














/* 11. ARDUINO... BILANCIERE AUTOMATICO (ROTAIA CON PALLINA) - 
 *                CON PID, HCSR04 E SERVOMOTORE
 *
 *     Già assemblato.       
 *
 *     Per una dimostrazione vedere     https://www.youtube.com/watch?v=M9wMnrUXKdo     */


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
















/* 12. ARDUINO... "RCTiming_capacitance_meter.ino"
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

  /* dicharge the capacitor  */
  digitalWrite(chargePin, LOW);             // set charge pin to  LOW 
  pinMode(dischargePin, OUTPUT);            // set discharge pin to output 
  digitalWrite(dischargePin, LOW);          // set discharge pin LOW 
  while(analogRead(analogPin) > 0){         // wait until capacitor is completely discharged
  }

  pinMode(dischargePin, INPUT);            // set discharge pin back to input
}

/* ... E LE LEGGI DELLA FISICA
 * osservazione: abbiamo un po' di condensatori e questo apparato complesso. 
 * ipotesi: se operiamo con precisione possiamo misurare la capacità di alcuni condensatori.  
 * esperimento: proviamoci!  
 * riflessioni: i risultati ottenuti sono in linea con quelli degli altri gruppi?  */















// E tanti altri esperimenti si possono fare! Grazie per la partecipazione.




