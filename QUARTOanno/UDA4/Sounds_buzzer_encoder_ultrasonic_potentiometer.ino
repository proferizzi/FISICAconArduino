// ESPERIMENTI CON ATMEGA 328p SU BREADBOARD
// con encoder rotativo su breakout, buzzer, sensore a ultrasuoni
// e utilizzo di una macchina a stati nel software


// #4 Quattro esperimenti in uno:
//    - stato 0: Pitch NOT QUANTIZED with encoder
//    - stato 1: Pitch QUANTIZED with encoder
//    - stato 2: Very bad theremin not QUANTIZED with ultrasonic sensor
//    - stato 3: Very bad theremin QUANTIZED with ultrasonic sensor 

// Creiamo i parametri e li assegniamo a determinati pin 
#define pin_switch 9      // physical 15
#define pin_encoder_A 6   
#define pin_encoder_B 7   
#define pin_tone 8
#define trigPin 11  
#define echoPin 12  
#define led 13

int stato = 0;  // Variabile che definisce in ogni istante lo stato in cui
                // la macchina a stati si trova.

int valore = 0;    // Utili per stato 0 e 1
int valore2 = 0;
int letturaPrecedente = LOW;
int m = 0;
int f1 = 0;

// Utili per stato 2
long duration = 0;  // Creiamo variabile intera e le diamo un certo valore (in millisecondi)
float distance = 0; // Creiamo variabile a virgola mobile e le diamo un certo valore (in cm)
// IMPOSTAZIONI INIZIALI DEI PARAMETRI PER IL FILTRO di KALMAN
float x_est = 0;  // stima iniziale, dipende dal fenomeno studiato
float P = 1;   // incertezza stima, dipende dal fenomeno studiato
float Q = 0.75;  // basso se il dato cambia poco, 
                 // se cambia molto si aumenta fino a 1
float R = 4; // vicino a 1 se è poco rumoroso il sensore, altrimenti verso il 10



void setup(){   // Queste istruzioni verranno eseguite solo una volta.
  Serial.begin(9600);  // inizializzamo la comunicazione seriale a 9600 bit/secondo
  pinMode(pin_tone, OUTPUT);
  
  pinMode(pin_switch, INPUT_PULLUP);
  pinMode(pin_encoder_A, INPUT_PULLUP);
  pinMode(pin_encoder_B, INPUT_PULLUP);
  
  pinMode(trigPin, OUTPUT);  // pin per HCSR04
  pinMode(echoPin, INPUT);
  
  pinMode(led,OUTPUT);    
  digitalWrite(led,LOW);
  
  pinMode(A1,OUTPUT); // Utile per potenziometro
  digitalWrite(A1,HIGH);
  pinMode(A3,OUTPUT);
  digitalWrite(A3,LOW);
}


void loop(){   
  switch(stato){   // Controlla valore dello stato e fa saltare la macchina
                   // nel loop numerato da tale stato.
    case 0: 
      loop0();
    break;

    case 1: 
      loop1();
    break;
    
    case 2: 
      loop2();
    break;

    case 3:
      loop3();
    break;
  }
}


void loop0(){   // Pitch with encoder - not QUANTIZED 
  // STATO
  Serial.println(stato);
  int m = digitalRead(pin_encoder_A);  // stato presente
  if(m != letturaPrecedente){
    if(digitalRead(pin_encoder_B) != m){
      digitalWrite(led,HIGH);
      delay(1);
      digitalWrite(led,LOW);
      valore ++;
    }else{
      //Serial.print(valore);
      digitalWrite(led,HIGH);
      delay(1);
      digitalWrite(led,LOW);
      valore --;
    }
    Serial.println(valore);
  }
  letturaPrecedente = m;

  tone(pin_tone, valore*2 + analogRead(A2)+ 55);

  //Serial.println(stato);
  
  // TRANSIZIONE
  if(!digitalRead(pin_switch)){
    noTone(pin_tone);
    delay(250);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    stato = 1;
  }
}

  
void loop1(){    // Pitch with encoder - QUANTIZED - chromatic scale
  // STATO
  Serial.println(stato);
  int m = digitalRead(pin_encoder_A);  // stato presente
  if(m != letturaPrecedente){
    if(digitalRead(pin_encoder_B) != m){
      valore2 ++;
      digitalWrite(led,HIGH);
      delay(1);
      digitalWrite(led,LOW);
    }else{
      //Serial.print(valore);
      valore2 --;
      digitalWrite(led,HIGH);
      delay(1);
      digitalWrite(led,LOW);
    }
    Serial.println(valore2);
  }
  letturaPrecedente = m;
 
  if(analogRead(A2) < 300){
    f1 = 110;
  }else if(analogRead(A2) < 600){
    f1 = 220;
  }else{
    f1 = 440;
  }
  float frequency =  f1 * pow(2, (valore2 / 12.0));
  tone(pin_tone, frequency);
  Serial.println(f1);
  
  // TRANSIZIONE
  if(!digitalRead(pin_switch)){
    noTone(pin_tone);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    delay(90);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    stato = 2;
  }
}


void loop2(){    // Bad Theremin QUANTIZED - chromatic scale
  // STATO
  Serial.println(stato);
  int frequency =  110 * pow(2, (int(kalman(distance)+analogRead(A2)/10) / 12.0));
  tone(pin_tone, frequency);
  Serial.println(frequency);

  
  digitalWrite(trigPin, LOW);   // procedura di misura del sensore a ultrasuoni
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);   // cosa viene misurato?

  distance = duration/2.0 * 0.0343;  // cosa viene calcolato?

  if((distance<100) && (distance>2)){    // per un buon grafico sul serial plotter
    float kout = kalman(distance);
    //Serial.println(distance);  // stampiamolo
    //Serial.print(",");
    //Serial.println(kout);
    //Serial.println(",0,100");
    if(distance > 20){  // creiamo una soglia adeguata 
      //digitalWrite(led,HIGH);  // accendiamo il LED
    }else{  // altrimenti
      //digitalWrite(led,LOW);  // si spegne il LED
    }
  }else{
    //Serial.println("0,0,0,200");
  }
  delay(50);
  
  // TRANSIZIONE
  if(!digitalRead(pin_switch)){
    noTone(pin_tone);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    delay(90);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    delay(90);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    stato = 3;
  }
}


void loop3(){    // Bad Theremin not QUANTIZED
  // STATO
  Serial.println(stato);
  int frequenza =  880 + 1*analogRead(A2)/(kalman(distance));
  tone(pin_tone, frequenza);
  Serial.println(frequenza);

  
  digitalWrite(trigPin, LOW);   // procedura di misura del sensore a ultrasuoni
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);   // cosa viene misurato?

  distance = duration/2.0 * 0.0343;  // cosa viene calcolato?

  if((distance<100) && (distance>2)){    // per un buon grafico sul serial plotter
    float kout = kalman(distance);
    //Serial.println(distance);  // stampiamolo
    //Serial.print(",");
    //Serial.println(kout);
    //Serial.println(",0,100");
    if(distance > 20){  // creiamo una soglia adeguata 
      //digitalWrite(led,HIGH);  // accendiamo il LED
    }else{  // altrimenti
      //digitalWrite(led,LOW);  // si spegne il LED
    }
  }else{
    //Serial.println("0,0,0,200");
  }
  delay(50);
  
  // TRANSIZIONE
  if(!digitalRead(pin_switch)){
    noTone(pin_tone);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    delay(90);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    delay(90);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    delay(90);
    digitalWrite(led,HIGH);
    delay(90);
    digitalWrite(led,LOW);
    stato = 0;
  }
}


// FUNZIONE DI CALCOLO DEL DATO FILTRATO - per loop2 e loop3
float kalman(float misura){
  float x_pred = x_est;   // posizione stimata, predetta
  float P_pred = P + Q;  // dovrebbe ridursi man mano si procede coi calcoli
  float K = P_pred / (P_pred + R);  // guadagno di Kalman, il suo valore tra 0 e 1
                                    // esprime bontà del sensore vista dal filtro
  x_est = x_pred + K * (misura - x_pred);
  P = (1 - K) * P_pred;
  return(x_est);
}



// Fonte encoder: Aliverti https://www.youtube.com/watch?v=yVd80UIR6OM
// Fonte filtro:  Aliverti https://www.youtube.com/watch?v=5R-zjgHR0OU #958

// Fonti MACCHINA A STATI Aliverti #207 https://www.youtube.com/watch?v=bj2cdgKhCDg
//                #208 https://www.youtube.com/watch?v=TAOMpDNvBaY
// ULTERIORI FONTI DA VEDERE #223 https://www.youtube.com/watch?v=5WCrWb4Kh74
// #663 https://www.youtube.com/watch?v=WnGSuXFJ_TM
// #345 https://www.youtube.com/watch?v=Rs-NIc3hHRg
// #364 https://www.youtube.com/watch?v=M-nnwQr4wu4
// #45 https://www.youtube.com/watch?v=nZvzIkbw_78&t=667s
// #222 https://www.youtube.com/watch?v=en9APNfGm0E
// #652 https://www.youtube.com/watch?v=SxgZTvkb_V0
// #281 https://www.youtube.com/watch?v=0c4Vjjv7h8A&t=203s poi #282
// #731 https://www.youtube.com/watch?v=QMjrIjtx3PU&t=112s
// #498 https://www.youtube.com/watch?v=JBO0sLzumk8
// #365 https://www.youtube.com/watch?v=OLoULIlc5eM
// #205 https://www.youtube.com/watch?v=XHnnL0I0lDc&t=1s
// #618 https://www.youtube.com/watch?v=1SjG1hSOHVs&t=56s
// #486 https://www.youtube.com/watch?v=Xct-JE_csJE
// #366 https://www.youtube.com/watch?v=ZgDFejvOb98
// #297 https://www.youtube.com/watch?v=PImo3s9JzM4 e poi #298
// #262 https://www.youtube.com/watch?v=I4IXILk33Rk







/*

// #3 Tre esperimenti in uno:
//    - stato 0: Buzzer in parallel with LED 
//    - stato 1: Pitch with encoder 
//    - stato 2: Very bad theremin with ultrasonic sensor 

#define pin_switch 9    // physical 15 
#define pin_encoder_A 6
#define pin_encoder_B 7
#define pin_tone 8

int stato = 0;  // Variabile che definisce in ogni istante lo stato in cui
                // la macchina a stati si trova.

// Utili per stato 0
int t = 0;
int n = 0;
int x = 0;

// Utili per stato 1
int valore = 0;
int letturaPrecedente;
int m;

// Utili per stato 2
#define trigPin 11  // creiamo un parametro e lo colleghiamo ad un certo pin
#define echoPin 12  // creiamo un parametro e lo colleghiamo ad un certo pin
int led = 13;  // creiamo una variabile intera e le diamo un certo valore
long duration = 0;  // creiamo variabile intera e le diamo un certo valore (in millisecondi)
float distance = 0; // creiamo variabile a virgola mobile e le diamo un certo valore (in cm)
// IMPOSTAZIONI INIZIALI DEI PARAMETRI PER IL FILTRO di KALMAN
float x_est = 0;  // stima iniziale, dipende dal fenomeno studiato
float P = 1;   // incertezza stima, dipende dal fenomeno studiato
float Q = 0.75;  // basso se il dato cambia poco, 
                 // se cambia molto si aumenta fino a 1
float R = 4; // vicino a 1 se è poco rumoroso il sensore, altrimenti verso il 10



void setup(){   // Queste istruzioni verranno eseguite solo una volta.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);  // inizializzamo la comunicazione seriale a 9600 bit/secondo
  pinMode(pin_tone, OUTPUT);
  pinMode(pin_switch, INPUT_PULLUP);
  pinMode(pin_encoder_A, INPUT_PULLUP);
  pinMode(pin_encoder_B, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);  // pin per HCSR04
  pinMode(echoPin, INPUT);
  pinMode(led,OUTPUT);    // un LED per rilevare superamento di soglia
  digitalWrite(led,LOW);
  letturaPrecedente = digitalRead(pin_encoder_A);  // misura lo stato presente
}


void loop(){   
  switch(stato){   // Controlla valore dello stato e fa saltare la macchina
                   // nel loop numerato da tale stato.
    case 0: 
      loop0();
    break;

    case 1: 
      loop1();
    break;
    
    case 2: 
      loop2();
    break;
  }
}


void loop0(){
  // STATO
  digitalWrite(LED_BUILTIN, HIGH);digitalWrite(pin_tone, HIGH);   
  delayMicroseconds(t);              
  digitalWrite(LED_BUILTIN, LOW);digitalWrite(pin_tone, LOW);   
  delayMicroseconds(t+n);
  
  if(t < x){
    t = t + n;
  }else{
    t = t - x;
    x = x + 1; 
    if(x > 40){
      x = 0;
      t = 0;
      n = 0;
    }
  }
  n = 1;//n = n + 1;
  
  Serial.print(stato);
  Serial.print(" ");Serial.print(t);
  Serial.print(" ");Serial.println(x);
  
  // TRANSIZIONE
  if(!digitalRead(pin_switch)) {
    delay(500);
    stato = 1;
    noTone(pin_tone);
  }
}

  
void loop1(){
  // STATO
  int m = digitalRead(pin_encoder_A);  // stato presente
  if(m != letturaPrecedente){
    if(digitalRead(pin_encoder_B) != m){
      valore ++;
    }else{
      //Serial.print(valore);
      valore --;
    }
    Serial.println(valore);
  }
  letturaPrecedente = m;

  tone(pin_tone, valore*100 + 440);

  //Serial.println(stato);
  
  // TRANSIZIONE
  if(!digitalRead(pin_switch)){
    delay(500);
    stato = 2;
    noTone(pin_tone);
  }
}


void loop2(){
  // STATO
  Serial.println(stato);
  tone(pin_tone, 55 + 10000/kalman(distance));
  
  digitalWrite(trigPin, LOW);   // procedura di misura del sensore a ultrasuoni
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);   // cosa viene misurato?

  distance = duration/2.0 * 0.0343;  // cosa viene calcolato?

  if((distance<100) && (distance>2)){    // per un buon grafico sul serial plotter
    float kout = kalman(distance);
    //Serial.println(distance);  // stampiamolo
    //Serial.print(",");
    //Serial.println(kout);
    //Serial.println(",0,100");
    if(distance > 20){  // creiamo una soglia adeguata 
      //digitalWrite(led,HIGH);  // accendiamo il LED
    }else{  // altrimenti
      //digitalWrite(led,LOW);  // si spegne il LED
    }
  }else{
    //Serial.println("0,0,0,200");
  }
  delay(50);
  
  // TRANSIZIONE
  if(!digitalRead(pin_switch)){
    delay(500);
    stato = 0;
    noTone(pin_tone);
  }
}


// FUNZIONE DI CALCOLO DEL DATO FILTRATO
float kalman(float misura){
  float x_pred = x_est;   // posizione stimata, predetta
  float P_pred = P + Q;  // dovrebbe ridursi man mano si procede coi calcoli
  float K = P_pred / (P_pred + R);  // guadagno di Kalman, il suo valore tra 0 e 1
                                    // esprime bontà del sensore vista dal filtro
  x_est = x_pred + K * (misura - x_pred);
  P = (1 - K) * P_pred;
  return(x_est);
}


// Fonte encoder: Aliverti https://www.youtube.com/watch?v=yVd80UIR6OM
// Fonte filtro:  Aliverti https://www.youtube.com/watch?v=5R-zjgHR0OU #958

// Fonti MACCHINA A STATI Aliverti #207 https://www.youtube.com/watch?v=bj2cdgKhCDg
//                #208 https://www.youtube.com/watch?v=TAOMpDNvBaY
// ULTERIORI FONTI DA VEDERE #223 https://www.youtube.com/watch?v=5WCrWb4Kh74
// #663 https://www.youtube.com/watch?v=WnGSuXFJ_TM
// #345 https://www.youtube.com/watch?v=Rs-NIc3hHRg
// #364 https://www.youtube.com/watch?v=M-nnwQr4wu4
// #45 https://www.youtube.com/watch?v=nZvzIkbw_78&t=667s
// #222 https://www.youtube.com/watch?v=en9APNfGm0E
// #652 https://www.youtube.com/watch?v=SxgZTvkb_V0
// #281 https://www.youtube.com/watch?v=0c4Vjjv7h8A&t=203s poi #282
// #731 https://www.youtube.com/watch?v=QMjrIjtx3PU&t=112s
// #498 https://www.youtube.com/watch?v=JBO0sLzumk8
// #365 https://www.youtube.com/watch?v=OLoULIlc5eM
// #205 https://www.youtube.com/watch?v=XHnnL0I0lDc&t=1s
// #618 https://www.youtube.com/watch?v=1SjG1hSOHVs&t=56s
// #486 https://www.youtube.com/watch?v=Xct-JE_csJE
// #366 https://www.youtube.com/watch?v=ZgDFejvOb98
// #297 https://www.youtube.com/watch?v=PImo3s9JzM4 e poi #298
// #262 https://www.youtube.com/watch?v=I4IXILk33Rk

*/















/*

// #1 Buzzer in parallel with LED on pin 13

int t = 0;
int n = 0;
int x = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  delayMicroseconds(t);              
  digitalWrite(LED_BUILTIN, LOW);    
  delayMicroseconds(t + n);
  
  if(t < x){
    t = t + n;
  }else{
    t = t - x;
    x = x + 1; Serial.println(x);
    if(x > 100){
      x = 0;
      t = 0;
      n = 0;
    }
  }
  n = 1;//n = n + 1;
}

*/





















/*
// #2 PITCH WITH ENCODER ON PIN 8
// ONDA QUADRA CON "tone" CONTROLLABILE DA UN ENCODER ROTATIVO
// PIN 8 PER OUT CASSA AUDIO - PIN 3 E 4 PER IN DA ENCODER

int valore = 0;
int letturaPrecedente = HIGH;

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {
  int n = digitalRead(3);
  if((letturaPrecedente == HIGH)&&(n == LOW)){
    if(digitalRead(4)){
      valore--;
    }else{
      valore++;
    }
    Serial.println(valore);
  }
  letturaPrecedente = n;

  tone(13, valore*100 + 440);
}
// Fonte: Aliverti https://www.youtube.com/watch?v=yVd80UIR6OM

*/
