// Movimento graduale di servomotore - rotazione costante oraria/antioraria
// con potenziometro per controllare la velocità di rotazione ad ogni mezzo giro
// e possibilità nello sketch di modificare valori max e min di angoli e velocità



// °°°°°°°°°° IMPOSTAZIONI INIZIALI
#include <Servo.h>

#define PINSERVO 6
#define PINPOTENZIOMETRO A1
#define VELMAX 100
#define VELMIN 1
#define ANGMIN 60
#define ANGMAX 120

Servo mio_servo;

void setup() {
  pinMode(PINSERVO, OUTPUT);
  mio_servo.attach(PINSERVO);
  mio_servo.write(90);
  
  //Serial.begin(9600);  // per debug
  pinMode(5, OUTPUT);  // per alimentare il potenziometro
  digitalWrite(5, HIGH);
}



// °°°°°°°°°°°° ESECUZIONE PRINCIPALE 
void loop() {
  int x = map(analogRead(PINPOTENZIOMETRO),0,1023,VELMIN,VELMAX); 
  //Serial.println(x);
  servo_graduale(x, ANGMIN, ANGMAX);
  delay(100);
  x = map(analogRead(PINPOTENZIOMETRO),0,1023,VELMIN,VELMAX); 
  servo_graduale(x, ANGMAX, ANGMIN);
  delay(100);
}



// °°°°°°°°°°° FUNZIONI AUSILIARIE
void servo_graduale(const int tempo, int inizio, int fine){
  bool option = 0;
  if(fine > inizio){
    option = 0;  // variabile per stato angolo iniziale minore di quello finale
  }
 else{
  option = 1;  
 }
 if(!option){
   for(int i=inizio; i<fine; i++){
     mio_servo.write(i);
     delay(tempo);  
   }
 }else{
   for(int j=inizio; j>fine; j--){
     mio_servo.write(j);
     delay(tempo);  
   }
 }
}


// Fonte di partenza WRKits https://www.youtube.com/watch?v=F0IfgFjVNnc
// testato a giugno 2021, ok
