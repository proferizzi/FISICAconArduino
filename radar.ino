// GIORNATA DELL'ARTE GIUGNO 2021 - LICEO 

// RADAR CON SERVO, SENSORE A ULTRASUONI, CICALINO E LED  

#define ECHO 8      // Pin per ricezione del segnale al sensore a ultrasuoni
#define TRIG 9      // Pin per trasmissione del segnale dal sensore a ultrasuoni
#define LED 13      // Pin per LED
#define CIC 4       // Pin per cicalino
#define SERVO 3     // Pin del servomotore
#include <Servo.h>  // Libreria per gestire il servomotore
Servo myservo;      // Creazione oggetto "myservo" per controllare il servomotore


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
  myservo.attach(SERVO);    // Collego l'oggetto "myservo" al pin del servomotore 
}


void loop() {
  for (int i = 45; i < 135; i = i + 5) {
    myservo.write(i);
    int d = readDistanza(); 
    Serial.println(d);  
    if((d <= 200) && (d >= 2)){
      int j = d*20;
      digitalWrite(LED,HIGH);
      tone(CIC,100);  
      delay(j);
      digitalWrite(LED,LOW);
      tone(CIC,1000);
      delay(j);
    }
    while(d < 5){
      int r = random(100,1000);
      tone(CIC,r);
      d = readDistanza(); 
    }
  }
}


int readDistanza() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);   
  float d = pulseIn(Echo, HIGH);  
  d = d / 58.0;       
  return (int)d;
}  



// Fonti:  https://www.youtube.com/watch?v=QEpUTYRSftY
//         https://www.youtube.com/watch?v=xbvMzptK8H8
