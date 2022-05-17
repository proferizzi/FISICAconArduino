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
// Esperimento 1: Sequenza di Snake: d-c-g-f-a-b-g-e-d (4-3-7-6-1-2-7-5-4)
// Macchina a stati che tenga conto anche dello stato precedente
// Display a sette segmenti tipicamente indicizzato come segue,
// con accanto l'indicizzazione per questo sketch
// (l'ordine alfabetico come ordine crescente):
//
//           a 1
//		      -
//		f 6 |   | b 2
//            -
//           g 7
//      e 5 |   | c 3
//            -
//           d 4

/* Globals  */

volatile byte currentState = 0;
volatile byte previousState = 0;
volatile unsigned long elapsedTime = 0;
int initialState;
unsigned long globalTime, delayTime;
bool startFlag = true;


/* Configurations */

enum PINS_OUTPUT_CONFIGURATION {
    SEGMENT_PIN_A = 6,  // Un pin per ogni segmento,
    SEGMENT_PIN_B = 7,  // non confondere con numero dello currentState.
    SEGMENT_PIN_C = 8,  // I pin 2 SEGMENT_PIN_E 3 servono per le Interrupt
    SEGMENT_PIN_D = 9,
    SEGMENT_PIN_E = 10,
    SEGMENT_PIN_F = 5,
    SEGMENT_PIN_G = 4
};

enum PINS_INPUT_CONFIGURATION {
    BUTTON_PIN_START = 3,
    BUTTON_PIN_STOP = 2
};

enum SERIAL_CONFIGURATION {
    BOUNDS = 9600
};


enum STATES {
    WAIT_BUTTON_START = 0,
    SWITCHED_ON_SEGMENT_A = 1,
    SWITCHED_ON_SEGMENT_B = 2,
    SWITCHED_ON_SEGMENT_C = 3,
    SWITCHED_ON_SEGMENT_D = 4,
    SWITCHED_ON_SEGMENT_E = 5,
    SWITCHED_ON_SEGMENT_F = 6,
    SWITCHED_ON_SEGMENT_G = 7,
    END_GAME = 99
};

enum DELAY  {
    WAIT_HALF_SECOND = 500,
    WAIT_3_SECONDS = 3000,
    WAIT_300_MILLISECONDS = 300
};


void setupSerialConfiguration()  {
    Serial.begin(BOUNDS);
}

void setupSegmentPinConfiguration() {
    pinMode(SEGMENT_PIN_A, OUTPUT);
    pinMode(SEGMENT_PIN_B, OUTPUT);
    pinMode(SEGMENT_PIN_C, OUTPUT);
    pinMode(SEGMENT_PIN_D, OUTPUT);
    pinMode(SEGMENT_PIN_E, OUTPUT);
    pinMode(SEGMENT_PIN_F, OUTPUT);
    pinMode(SEGMENT_PIN_G, OUTPUT);
}

void setupButtonPinConfiguration() {
    pinMode(BUTTON_PIN_STOP, INPUT);
    pinMode(BUTTON_PIN_START, INPUT);
}

// Funzione ausiliaria chiamata dall'Interrupt presente nel setup iniziale
void terminateLoop() {
    if ((currentState != WAIT_BUTTON_START) && (currentState != END_GAME)) {
        previousState = currentState;
        elapsedTime = delayTime;
        currentState = END_GAME;
    }
}

void setupDigitalPinToInterrutp(){
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_STOP), terminateLoop, RISING);
}

/* SETUP */

void setup() {

    initialState = SWITCHED_ON_SEGMENT_C;

    setupSegmentPinConfiguration();
    setupButtonPinConfiguration();
    setupDigitalPinToInterrutp();
    setupSerialConfiguration();

    Serial.println("Pronto!");
}

/* Functions */

bool checkDelayTimePassed(int delay) {
    unsigned long delayTime = millis() - globalTime;
    if (delayTime > delay) {
        return true;
    }
    return false;
}

void changeInitialState(int newInitialState) {
    if (newInitialState != -1) {
        initialState = newInitialState;
    }
}

void changeState(int segment, int nextState, int delay, int newInitialState = -1) {
    digitalWrite(segment, HIGH);
    if (checkDelayTimePassed(delay)) {
        digitalWrite(segment, LOW);
        Serial.print("dal " + String(currentState));
        Serial.println(" verso il " + String(nextState));
        currentState = nextState;
        globalTime = millis();
        changeInitialState(newInitialState);
    }
}

// Funzioni ausiliarie chiamate dal loop principale

void waitForButtonStartClick() {
    if (digitalRead(BUTTON_PIN_START)) {
        Serial.println("Inizio Gioco");
        currentState = SWITCHED_ON_SEGMENT_D;
        delay(WAIT_300_MILLISECONDS);
        globalTime = millis();
    }
}

void endGame() {
    if (startFlag) {
        Serial.println("STOP!");
        Serial.println("arriva da: ");
        Serial.println(previousState);
        startFlag = false;
        delay(WAIT_300_MILLISECONDS);
    }

    if (digitalRead(BUTTON_PIN_STOP)) {
        currentState = previousState;
        globalTime = millis() - elapsedTime;
        startFlag = true;
        Serial.println("Torno 1:");
        Serial.println(previousState);
        delay(WAIT_300_MILLISECONDS);
    }
}

void changeStateFromAtoB() {
    changeState(SEGMENT_PIN_A, SWITCHED_ON_SEGMENT_B, WAIT_HALF_SECOND);
}

void changeStateFromBToG() {
    changeState(SEGMENT_PIN_B, SWITCHED_ON_SEGMENT_G, WAIT_HALF_SECOND);
}

void changeStateFromCToG() {
    changeState(SEGMENT_PIN_C, SWITCHED_ON_SEGMENT_G, WAIT_HALF_SECOND);
}

void changeStateFromDToC() {
    if (currentState == SWITCHED_ON_SEGMENT_E) {
        changeState(SEGMENT_PIN_D,WAIT_BUTTON_START,WAIT_3_SECONDS);
    }
    if (currentState == SWITCHED_ON_SEGMENT_D) {
        changeState(SEGMENT_PIN_D, SWITCHED_ON_SEGMENT_C, WAIT_HALF_SECOND);
    }
};

void changeStateFromEToD () {
    changeState(SEGMENT_PIN_E, SWITCHED_ON_SEGMENT_D, WAIT_HALF_SECOND);
}

void changeStateFromFToA () {
    changeState(SEGMENT_PIN_F, SWITCHED_ON_SEGMENT_A, WAIT_HALF_SECOND);
}

void changeDirectionAndStateFromCToFOrE() {
    if (initialState == SWITCHED_ON_SEGMENT_C) {
        changeState(SEGMENT_PIN_G, SWITCHED_ON_SEGMENT_F, WAIT_HALF_SECOND, SWITCHED_ON_SEGMENT_B);
    }
    if ((currentState != SWITCHED_ON_SEGMENT_F) && (initialState == SWITCHED_ON_SEGMENT_B)) {
        changeState(SEGMENT_PIN_G, SWITCHED_ON_SEGMENT_E, WAIT_HALF_SECOND, SWITCHED_ON_SEGMENT_C);
    }
}

/* LOOP */

void loop() {
    switch (currentState) {
        case WAIT_BUTTON_START:  // Attende l'avvio
            waitForButtonStartClick();
            break;
        case SWITCHED_ON_SEGMENT_A:
            changeStateFromAtoB();
            break;
        case SWITCHED_ON_SEGMENT_B:
            changeStateFromBToG();
            break;
        case SWITCHED_ON_SEGMENT_C:
            changeStateFromCToG();
            break;
        case SWITCHED_ON_SEGMENT_D:
            changeStateFromDToC();
            break;
        case SWITCHED_ON_SEGMENT_E:
            changeStateFromEToD();
            break;
        case SWITCHED_ON_SEGMENT_F:
            changeStateFromFToA();
            break;
        case SWITCHED_ON_SEGMENT_G:
            changeDirectionAndStateFromCToFOrE();
            break;
        case END_GAME:
            endGame();  // Stop premuto
            break;
    }
}

// Fonte Aliverti https://www.youtube.com/watch?v=bj2cdgKhCDg
// Fonte Aliverti https://github.com/zmaker/arduino_cookbook/blob/master/345-stati_con_interrupt/stati_con_interrupt/stati_con_interrupt.ino


// Fonte Aliverti https://www.youtube.com/watch?v=bj2cdgKhCDg
// Fonte Aliverti https://github.com/zmaker/arduino_cookbook/blob/master/345-stati_con_interrupt/stati_con_interrupt/stati_con_interrupt.ino
