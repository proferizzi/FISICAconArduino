// BILANCIERE AUTOMATICO (ROTAIA CON PALLINA) - 
// CON PID, HCSR04 E SERVO A QUATTRO BRACCIA

// NB:  angolo del servo tale per cui si ha rotaia orizzontale: 120 gradi
//      distanza della pallina all'equilibrio: 10 cm
//      distanza massima della pallina dal sensore a ultrasuoni: 20 cm

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
// Fonte http://mechatronicstutorials.blogspot.com/2014/07/balancing-of-ball-on-beam-using-arduino.html

