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




// #3 Tre esperimenti in uno:
//    - Buzzer in parallel with LED on pin 13 (physical 19)
//    - Pitch with encoder on pin 9 (physical 15)
//    - Very bad theremin with ultrasonic sensor on pin 7 (physical 13)

int t = 0;
int n = 0;
int x = 0;

int valore = 0;
int letturaPrecedente = HIGH;

//#define vccPin 8   // creiamo un parametro e lo colleghiamo ad un certo pin
#define trigPin 11  // creiamo un parametro e lo colleghiamo ad un certo pin
#define echoPin 12  // creiamo un parametro e lo colleghiamo ad un certo pin
//#define gndPin 11  // creiamo un parametro e lo colleghiamo ad un certo pin
int led = 13;  // creiamo una variabile intera e le diamo un certo valore
long duration = 0;  // creiamo variabile intera e le diamo un certo valore (in millisecondi)
float distance = 0; // creiamo variabile a virgola mobile e le diamo un certo valore (in cm)
// IMPOSTAZIONI INIZIALI DEI PARAMETRI PER IL FILTRO
float x_est = 0;  // stima iniziale, dipende dal fenomeno studiato
float P = 1;   // incertezza stima, dipende dal fenomeno studiato
float Q = 0.75;  // basso se il dato cambia poco, 
                 // se cambia molto si aumenta fino a 1
float R = 4; // vicino a 1 se è poco rumoroso il sensore, altrimenti verso il 10


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);  // inizializzamo la comunicazione seriale a 9600 bit/secondo

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  //pinMode(vccPin, OUTPUT);  // alimentazione sul pin vccPin
  //digitalWrite(vccPin, HIGH);
  pinMode(trigPin, OUTPUT);  // pin per HCSR04
  pinMode(echoPin, INPUT);
  //pinMode(gndPin, OUTPUT);    // messa a Terra sul pin gndPin
  //digitalWrite(gndPin, LOW);
  pinMode(led,OUTPUT);    // un LED per rilevare superamento di soglia
  digitalWrite(led,LOW);
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
    x = x + 1; //Serial.println(x);
    if(x > 40){
      x = 0;
      t = 0;
      n = 0;
    }
  }
  n = 1;//n = n + 1;

 int m = digitalRead(3);
  if((letturaPrecedente == HIGH)&&(m == LOW)){
    if(digitalRead(4)){
      valore--;
    }else{
      valore++;
    }
    //Serial.println(valore);
  }
  letturaPrecedente = m;

  tone(9, 55 + 10000/kalman(distance));//tone(9, valore*100 + 440);

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
