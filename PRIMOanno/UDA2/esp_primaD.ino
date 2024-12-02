

// VERSIONE VECCHIA con solo un sensore a ultrasuoni e senza Seriale

// ESPERIMENTO DI CINEMATICA: 
// LEGGE ORARIA DI UN CORPO IN MOTO, in tempo reale
//
// Materiale: microcontrollore con cavo USB, 
//            un sensore a ultrasuoni
//            breadboard 
//            cicalino
//            LED

#define vccPin 3
#define trigPin 4
#define echoPin 5
#define gndPin 6

#define vccPinBIS 9
#define cicalino 10   // PWM
#define gndPinBIS 11


long duration = 0;  // duration in microsecondi 
float distance = 0; // distance in cm

int const fsize = 3;
int fil [fsize];
int i=0;
float avg = 0.0;

int frequenza = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(vccPin, OUTPUT);
  digitalWrite(vccPin, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);

  pinMode(vccPinBIS, OUTPUT);
  digitalWrite(vccPinBIS, HIGH);
  pinMode(gndPinBIS, OUTPUT);
  digitalWrite(gndPinBIS, LOW);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(cicalino, OUTPUT);
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
  
  if((distance <= 1000)&&(distance > 0)){
    //Serial.println(distance);
    delay(distance*10);
    digitalWrite(cicalino, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(distance*10); 
  }
  digitalWrite(cicalino, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
}


// Fonte per filtro Aliverti https://www.youtube.com/watch?v=cnQSCPUgiA4
// Fonte per cicalino https://www.progettiarduino.com/arduino-sensore-parcheggio-con-hc-sr04.html#google_vignette
