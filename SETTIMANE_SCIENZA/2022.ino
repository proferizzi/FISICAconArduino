
// ESPERIMENTO DI CINEMATICA: 
// LEGGE ORARIA DI UN CORPO IN MOTO, in tempo reale
//
// Materiale: microcontrollore con cavo USB, 
//            due sensori a ultrasuoni
//            breadboard 
//            cicalino
//            LED
//            PC per Serial Plotter

#define vccPin 3
#define trigPin 4
#define echoPin 5
#define gndPin 6

#define vccPinTRIS 14
#define trigPinTRIS 15
#define echoPinTRIS 16
#define gndPinTRIS 17

#define vccPinBIS 9
#define cicalino 10   // PWM
#define gndPinBIS 11


long duration = 0;  // duration in microsecondi 
float distance = 0; // distance in cm
long durationTRIS = 0;  // duration in microsecondi 
float distanceTRIS = 0; // distance in cm


int const fsize = 3;
int fil [fsize];
int i=0;
float avg = 0.0;
int const fsizeTRIS = 3;
int filTRIS [fsizeTRIS];
int j=0;
float avgTRIS = 0.0;

int frequenza = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(vccPin, OUTPUT);
  digitalWrite(vccPin, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);

  pinMode(vccPinTRIS, OUTPUT);
  digitalWrite(vccPinTRIS, HIGH);
  pinMode(trigPinTRIS, OUTPUT);
  pinMode(echoPinTRIS, INPUT);
  pinMode(gndPinTRIS, OUTPUT);
  digitalWrite(gndPinTRIS, LOW);

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
  for(int h=0; h<fsize; h++){
    avg += (float)fil[h];
  }
  avg = avg / (float)(fsize);
  
  distance = avg/2.0 * 0.0343; // calcolo con velocità del suono

  digitalWrite(trigPinTRIS, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinTRIS, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinTRIS, LOW);
  durationTRIS = pulseIn(echoPinTRIS, HIGH,20000);
  //if(durationBis == 0){ 
    //pinMode(echoPinBis, OUTPUT); 
    //digitalWrite(echoPinBis, LOW);
    //delayMicroseconds(200);
    //pinMode(echoPinBis, INPUT); 
  //}

  filTRIS[j] = durationTRIS;
  if(j < (fsizeTRIS-1)) j++;
  else j = 0;
  avgTRIS = 0;
  for(int h=0; h<fsizeTRIS; h++){
    avgTRIS += (float)filTRIS[h];
  }
  avgTRIS = avgTRIS / (float)(fsizeTRIS);
  
  distanceTRIS = avgTRIS/2.0 * 0.0343; // calcolo con velocità del suono
  //distanceTRIS = durationTRIS/2.0 * 0.0343; // calcolo con velocità del suono
  
  if((distance <= 80)&&(distance > 0)&&(distanceTRIS <= 80)&&(distanceTRIS > 0)){
    Serial.print(distance);
    Serial.print(" ");
    Serial.println(distanceTRIS);
  }
  delay(distance*10);
  digitalWrite(cicalino, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(distance*10); 
  digitalWrite(cicalino, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  //delay(10);
}


// Fonte per filtro Aliverti https://www.youtube.com/watch?v=cnQSCPUgiA4
// Fonte per cicalino https://www.progettiarduino.com/arduino-sensore-parcheggio-con-hc-sr04.html#google_vignette
// Fonte https://www.moreware.org/wp/blog/2020/04/22/arduino-utilizzare-i-pin-analogici-come-pin-digitali/




/*
int frequenza = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void loop() {
  

  // change the brightness for next time through the loop:
  frequenza = frequenza + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (frequenza <= 0 || frequenza >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
// Fonte esempio Fade.ino
*/






/*



// ESPERIMENTO DI CINEMATICA: 
// LEGGE ORARIA DI DUE CORPI IN MOTO, in tempo reale
//
// Materiale: microcontrollore con cavo USB, 
//            PC o altro con serial plotter
//            2 sensori a ultrasuoni
//            breadboard e cavetti


#define vccPin 3
#define trigPin 4
#define echoPin 5
#define gndPin 6

#define vccPinBis 8
#define trigPinBis 9
#define echoPinBis 10
#define gndPinBis 11

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


// Fonte per filtro Aliverti https://www.youtube.com/watch?v=cnQSCPUgiA4

*/








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
  
  if((distance <= 400)&&(distance > 0)){
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





