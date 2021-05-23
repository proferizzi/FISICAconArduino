// GIORNATA DELL'ARTE GIUGNO 2021 - LICEO GARDONE VT

// RADAR CON SERVO, SENSORE A ULTRASUONI, CICALINO E LED

#include <Servo.h>  

Servo myservo;      
int Echo = A4;  
int Trig = A5; 
int ledPin = 13;
int trig = 9;
int echo = 8;
int cicalino = 4;
float durata;
float distanza;


void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  pinMode(echo,INPUT);
  delay(2000);
  pinMode(cicalino,OUTPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  myservo.attach(3);   
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);   
  Serial.println("Ok");
}


void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  durata = pulseIn(echo,HIGH);
  distanza = durata/58.0;
  //Serial.println(distanza);
  //Serial.print("cm");
  //Serial.print("\n");
  int i = 20;
  if(distanza<=200 && distanza>=2){
    i=distanza*i;
    digitalWrite(ledPin,HIGH);
    tone(cicalino,100);  
    delay(i);
    digitalWrite(ledPin,LOW);
    tone(cicalino,1000);
    delay(i);
  }
  delay(60);
  
    Serial.println("Scan");
  myservo.write(90);
  for (int i = 45; i < 135; i = i + 5) {
    myservo.write(i);
    int d = readDistanza();
    delay(100);
    Serial.println(d);
  }
  myservo.write(90);
  delay(500);

}


int readDistanza() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float d = pulseIn(Echo, HIGH);  
  d = d / 58;       
  return (int)d;
}  



// Fonti:  https://www.youtube.com/watch?v=QEpUTYRSftY
//         https://www.youtube.com/watch?v=xbvMzptK8H8
