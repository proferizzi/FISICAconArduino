// Servomotore controllato senza usare la libreria


// °°°°°°°°°° IMPOSTAZONI INIZIALI
#define PINSERVO 6

void setup() {
  pinMode(PINSERVO, OUTPUT);
}



// °°°°°°°°°°° PARTE ESECUTIVA PRINCIPALE
void loop() {
  for(char i=0; i<100; i++){
    servo0gradi();
  }
  for(char i=0; i<100; i++){
    servo90gradi();
  }
  //for(char i=0; i<100; i++){
    //servo180gradi();
  //}
  //for(char i=0; i<100; i++){
    //servo90gradi();
  //}
}



// °°°°°°°°°°° FUNZIONI AUSILIARIE
void servo0gradi(){
  digitalWrite(PINSERVO, HIGH);
  delayMicroseconds(600);
  digitalWrite(PINSERVO, LOW);
  for(int i=0; i<32; i++){
    delayMicroseconds(600);
  }
}
void servo90gradi(){
  digitalWrite(PINSERVO, HIGH);
  delayMicroseconds(1500);
  digitalWrite(PINSERVO, LOW);
  for(int i=0; i<12; i++){
    delayMicroseconds(1500);
  }
}
void servo180gradi(){
  digitalWrite(PINSERVO, HIGH);
  delayMicroseconds(2400);
  digitalWrite(PINSERVO, LOW);
  for(int i=7; i<32; i++){
    delayMicroseconds(2400);
  }
}


// Fonte WRKits https://www.youtube.com/watch?v=AEOb-EDVkdM
// testato a giugno 2021, ok
