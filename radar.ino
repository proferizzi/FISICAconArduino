// GIORNATA DELL'ARTE GIUGNO 2021 - LICEO 

// RADAR CON SERVO, SENSORE A ULTRASUONI, CICALINO E LED  

#include <Servo.h>  // Libreria per gestire il servomotore
Servo myservo;      // Creazione oggetto per controllare il servomotore

#DEFINE ECHO 8      // Pin per ricezione del segnale al sensore a ultrasuoni
#define TRIG 9      // Pin per trasmissione del segnale dal sensore a ultrasuoni
#define LED 13      // Pin per LED
#define CIC 4       // Pin per cicalino
#define SERVO 3     // Pin del servomotore

float durata;    // Variabile per salvare il dato proveniente da ECHO
float distanza;  // Variabile per salvare il risultato del calcolo della distanza


void setup() {
  Serial.begin(9600);       // Inizializzo la seriale
  
  pinMode(TRIG,OUTPUT);     // Inizializzo il pin di trasmissione come uscita 
  digitalWrite(TRIG,LOW);   // Lo pongo a zero Volt
  delayMicroseconds(2);     // Attendo 2 microsecondi
  pinMode(ECHO,INPUT);      // Inizializzo il pin di ricezione come ingresso
  delayMicroseconds(2);     // Attendo 2 microsecondi
  pinMode(CIC,OUTPUT);      // Inizializzo il pin del cicalino come uscita
  digitalWrite(CIC,LOW);    // Lo pongo a zero Volt
  pinMode(LED,OUTPUT);      // Inizializzo il pin del LED come uscita
  digitalWrite(LED,LOW);    // Lo pongo a zero Volt
  myservo.attach(SERVO);        // Collego l'oggetto "myservo" al pin del servomotore 
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
