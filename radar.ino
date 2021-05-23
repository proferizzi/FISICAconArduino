// GIORNATA DELL'ARTE GIUGNO 2021 - LICEO GARDONE VT

// RADAR CON SERVO, SENSORE A ULTRASUONI, CICALINO E LED

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
  //Serial.println("Distanza:");
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
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
}

// Fonte: https://www.youtube.com/watch?v=xbvMzptK8H8
