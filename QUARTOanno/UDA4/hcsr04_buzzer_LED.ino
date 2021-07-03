// hcsr04, buzzer e led

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
// Fonte: da "5volt solution" su youtube











/*
// sensore a ultrasuoni con buzzer attivo

int triggerPort = 7;
int echoPort = 8;
int cicalino = 9;
unsigned long time;
unsigned long lampeggio_time;
unsigned long pausa_time;
void setup() {
pinMode( triggerPort, OUTPUT );
pinMode( echoPort, INPUT );
pinMode( cicalino, OUTPUT );
Serial.begin( 9600 );
Serial.println( "Sensore ultrasuoni: ");
}
void loop() {
//porta bassa l'uscita del trigger
digitalWrite( triggerPort, LOW );
//invia un impulso di 10microsec su trigger
digitalWrite( triggerPort, HIGH );
delayMicroseconds( 10 );
digitalWrite( triggerPort, LOW );
long duration = pulseIn( echoPort, HIGH );
long r = 0.034 * duration / 2;
Serial.print( "durata: " );
Serial.print( duration );
Serial.print( " , " );
Serial.print( "distanza: " );
if( duration > 38000 ) Serial.println( "fuori portata");
else { Serial.print( r ); Serial.println( "cm" );}
if( r > 3 && r <= 200){
delay(r*10);
digitalWrite(cicalino, HIGH);
delay(r*10); }
if( r <= 3){
digitalWrite(cicalino, HIGH);
delay(1000);}
digitalWrite(cicalino, LOW);
delay(10);
}
// fonte https://www.progettiarduino.com/arduino-sensore-parcheggio-con-hc-sr04.html
// occhio al circuito con transistor https://startingelectronics.org/pinout/geekcreit-active-buzzer-module-pinout/
*/




