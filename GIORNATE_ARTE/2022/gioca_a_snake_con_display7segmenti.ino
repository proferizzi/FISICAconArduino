// Esperimento 1: Sequenza di Snake: d-c-g-f-a-b-g-e-d (4-3-7-6-1-2-7-5-4)
// Macchina a stati che tenga conto anche dello stato precedente
// Display a sette segmenti tipicamente indicizzato come segue,
// con accanto l'indicizzazione per questo sketch
// (l'ordine alfabetico come ordine crescente):
//
//         a 1
//          -
//    f 6 |   | b 2
//          -
//         g 7
//    e 5 |   | c 3
//          -
//         d 4


const int a = 6;  // Un pin per ogni segmento, 
const int b = 7;  // non confondere con numero dello stato.
const int c = 8;  // I pin 2 e 3 servono per le Interrupt
const int d = 9;
const int e = 10;
const int f = 5;
const int g = 4;

const byte stopPin = 2;
const byte startPin = 3;

volatile byte stato = 0;
volatile byte stato_di_provenienza = 0;
volatile unsigned long tempo_trascorso = 0;
int prevstato = 3 ;

unsigned long t1, dt;


void setup(){
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
  Serial.begin(9600);
  pinMode(stopPin, INPUT);
  pinMode(startPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(stopPin), stopCiclo, RISING);

  Serial.println("Pronto!");
}


void loop(){
  switch(stato){
    case 0:  // Attende l'avvio
      attende();
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
    case 4:
      loop4();
      break;
    case 5:
      loop5();
      break;
    case 6:
      loop6();
      break;
    case 7:
      loop7();
      break;
    case 99:
      stopfase();  // Stop premuto
      break;
  }
}  // Fine loop principale



// Funzioni ausiliarie chiamate dal loop principale

void attende() {
  if (digitalRead(startPin)){
    Serial.println("Inizio Gioco");
    stato = 4;
    delay(300);
    t1 = millis();
  }  
}

void loop1() {
  digitalWrite(a, HIGH);
  dt = millis() - t1; 
  if (dt > 500) {
    digitalWrite(a, LOW);
    stato = 2;  
    Serial.println("dal 1 verso il 2");
    t1 = millis();
  } 
}

void loop2() {
  digitalWrite(b, HIGH);
  dt = millis() - t1; 
  if (dt > 500) {
    digitalWrite(b, LOW);
    stato = 7;  
    Serial.println("dal 2 verso il 7");
    t1 = millis();
  } 
}

void loop3() {
  digitalWrite(c, HIGH);
  dt = millis() - t1; 
  if (dt > 500) {
    digitalWrite(c, LOW);
    stato = 7;  
    Serial.println("dal 3 verso il 7");
    t1 = millis();
  } 
}

void loop4() {
  digitalWrite(d, HIGH);
  dt = millis() - t1; 

  if ((stato == 5) && (dt > 3000)) {
    digitalWrite(d, LOW);
    stato = 0;  
    Serial.println("dal 5, FINE GIOCO");
    t1 = millis();
  } 
  if ((stato == 4) && (dt > 500)) {
    digitalWrite(d, LOW);
    stato = 3;  
    Serial.println("da 4 verso il 3");
    t1 = millis();
  } 
}

void loop5() {
  digitalWrite(e, HIGH);
  dt = millis() - t1; 
  if (dt > 500) {
    digitalWrite(e, LOW);
    stato = 4;  
    Serial.println("dal 5 verso il 4");
    t1 = millis();
  } 
}

void loop6() {
  digitalWrite(f, HIGH); 
  dt = millis() - t1; 
  if (dt > 500) {
    digitalWrite(f, LOW);
    stato = 1;  
    Serial.println("dal 6 verso il 1");
    t1 = millis();
  } 
}

void loop7() {
  digitalWrite(g, HIGH);
  dt = millis() - t1; 
  if ((prevstato == 3) && (dt > 500)) {
    digitalWrite(g, LOW);
    stato = 6;  
    prevstato = 2;
    Serial.println("dal 7 verso il 6");
    t1 = millis();
  }
  if ((stato != 6) && (prevstato == 2) && (dt > 500)) {
    digitalWrite(g, LOW);
    stato = 5;  
    prevstato = 3;
    Serial.println("dal 7 verso il 5");
    t1 = millis();
  } 
}

bool primo_ingresso = true;

void stopfase(){
  if (primo_ingresso) {
    Serial.println("STOP!");
    Serial.print("arriva da: ");
    Serial.println(stato_di_provenienza);    
    primo_ingresso = false;  
    delay(300);
  }

  if (digitalRead(stopPin)){
    stato = stato_di_provenienza;
    t1 = millis() - tempo_trascorso;  
    primo_ingresso = true;
    Serial.print("Torno a:");
    Serial.println(stato_di_provenienza);
    delay(300);
  }
}


// Funzione ausiliaria chiamata dall'Interrupt presente nel setup iniziale 
void stopCiclo() {
  if ((stato != 0) && (stato != 99)){
    stato_di_provenienza = stato;
    tempo_trascorso = dt;
    stato = 99;
  }
}


// Fonte Aliverti https://www.youtube.com/watch?v=bj2cdgKhCDg
// Fonte Aliverti https://github.com/zmaker/arduino_cookbook/blob/master/345-stati_con_interrupt/stati_con_interrupt/stati_con_interrupt.ino
