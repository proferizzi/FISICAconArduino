// Esperimento 1: Sequenza di Snake: d-c-g-f-a-b-g-e-d (4-3-7-6-1-2-7-5-4)
// Macchina a stati che tenga conto anche dello stato precedente
// Display a sette segmenti tipicamente indicizzato come segue,
// con accanto l'indicizzazione per questo sketch
// (l'ordine alfabetico come ordine crescente):
//
//           a 1
//		-
//		f 6 |   | b 2
//            -
//           g 7
//      e 5 |   | c 3
//            -
//           d 4


// Variabili globali


volatile byte currentState = 0;
volatile byte previousState = 0;
volatile unsigned long elapsedTime = 0;
int initialState;
unsigned long globalTime, delayTime;
bool startFlag = true;


// CONFIGURAZIONI 

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
        changeState(SEGMENT_PIN_G, SWITCHED_ON_SEGMENT_F, 
                    WAIT_HALF_SECOND, SWITCHED_ON_SEGMENT_B);
    }
    if ((currentState != SWITCHED_ON_SEGMENT_F) && (initialState == SWITCHED_ON_SEGMENT_B)) {
        changeState(SEGMENT_PIN_G, SWITCHED_ON_SEGMENT_E, 
                    WAIT_HALF_SECOND, SWITCHED_ON_SEGMENT_C);
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
// Fonte Aliverti https://github.com/zmaker/arduino_cookbook/blob/
//       master/345-stati_con_interrupt/stati_con_interrupt/stati_con_interrupt.ino
// Codice pulito da Luca del BIBLIOLAB, che ringrazio






