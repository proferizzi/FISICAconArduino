// ESPERIMENTO DI CINEMATICA: 
// LEGGE ORARIA DEL MOTO ARMONICO DELLA PROIEZIONE 
// SUL DIAMETRO DI UN PUNTO CHE SI MUOVE DI MCU
//
// Materiale: asciugainsalata, microcontrollore con cavo USB, 
//            PC o altro con serial plotter
//            1 sensori a ultrasuoni, una parete verticale di riferimento
//            breadboard e elastici per attaccare il tutto al polso


#define vccPin 8
#define trigPin 9
#define echoPin 10
#define gndPin 11

#define vccPinBis 3
#define trigPinBis 4
#define echoPinBis 5
#define gndPinBis 6

long duration = 0;  // duration in microsecondi 
float distance = 0; // distance in cm

long durationBis = 0;
float distanceBis = 0;

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

  pinMode(vccPinBis, OUTPUT);
  digitalWrite(vccPinBis, HIGH);
  pinMode(trigPinBis, OUTPUT);
  pinMode(echoPinBis, INPUT);
  pinMode(gndPinBis, OUTPUT);
  digitalWrite(gndPinBis, LOW);

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
  
  digitalWrite(trigPinBis, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinBis, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinBis, LOW);
  durationBis = pulseIn(echoPinBis, HIGH,20000);
  //if(durationBis == 0){ 
    //pinMode(echoPinBis, OUTPUT); 
    //digitalWrite(echoPinBis, LOW);
    //delayMicroseconds(200);
    //pinMode(echoPinBis, INPUT); 
  //}
  
  distanceBis = durationBis/2.0 * 0.0343; // calcolo con velocità del suono

  if((distance <= 40)&&(distanceBis <= 40)&&(distance > 0)){
    Serial.print(distance);
    Serial.print(" ");
    Serial.println(distanceBis);
    delay(60);  
  }
}
