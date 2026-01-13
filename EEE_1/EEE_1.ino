/* LE LEGGI DELLA FISICA CON ARDUINO! PROVA... IMPARA... DISCUTI...
 *
 * A cura di Marco Rizzinelli - progetto EEE a.s. 2025/26
 *
 * Benvenuti/e! In questo corso cerchiamo di vivere le fasi del metodo scientifico:
 * osservazione, ipotesi, esperimento (materiale, procedura, dati, analisi), riflessioni. 
 * Io girerò tra i gruppi e così lavoreremo un po' insieme! 
 * 
 * BREVISSIMA INTRODUZIONE AD ARDUINO
 *
 * Il microcontrollore ATmega è il cuore della scheda Arduino (UNO, Nano, etc.);
 * con Arduino possiamo ricevere input da sensori e mandare output ad attuatori; 
 * Arduino ha pin digitali e pin analogici, può venire alimentato tramite il cavo USB collegato al PC;
 * fornisce alcuni punti di messa a Terra chiamati "GND" cioè "ground";
 * fornisce un punto di voltaggio costante a +5 V e uno a +3,3 V.
 * NOTA BENE NON COLLEGARE MAI UN PUNTO A +5V CON IL GND, POTRESTI DANNEGGIARE IL MICROCONTROLLORE!
 *
 * Tramite il programma gratuito "Arduino IDE" che si scarica da www.arduino.cc e si installa
 * sul proprio PC si può programmare Arduino scrivendo un codice di programma e caricandolo sopra.
 * Lo scheletro di tale codice presenta una parte iniziale, una parte di "setup" che viene eseguita
 * solo una volta ad ogni accensione di Arduino e infine una parte di "loop" che continua ad essere
 * eseguita ininterrottamente. Il microcontrollore si può riprogrammare un numero elevato di volte. 
 */








/* ESPERIMENTO 1. ARDUINO LAMPEGGIA - "Blink.ino" 
 * Accendiamo e spegniamo ripetutamente una luce LED a intervalli di un secondo.
 * Un LED è un DIODO A EMISSIONE di LUCE ed è una sorgente di FOTONI/ONDE ELETTROMAGNETICHE.
 * Questo significa che il materiale (semiconduttore) con cui è costruito
 * il diodo, alimentato con un certo voltaggio, emette luce spontaneamente e a determinati colori.
 *
 * Circuito facile: Scheda Arduino + cavo USB + PC
 * Usiamo il leg integrato nella scheda Arduino.
 * Circuito difficile (solo per approfondimento e se c'è il materiale):
 * Mettiamo sulla basetta (o breadboard, serve per costruire circuiti, infatti le righe con
 * lo stesso numero equivalgono ad un solo nodo) la gamba meno lunga del LED (catodo negativo)
 * collegata con un capo di una resistore di resistenza pari a 220 Ω (Ohm); l'altro capo sarà
 * collegato con un cavetto alla Terra (GND) di Arduino.
 * La gamba più lunga del LED (anodo positivo) la colleghiamo con un cavetto al pin 9.
 * NB: non collegare mai un pin con la Terra oppure rovinerai Arduino!
 */

void setup() {  // questo corpo di istruzioni si esegue una volta sola dopo ogni reset
  pinMode(LED_BUILTIN, OUTPUT);  // settiamo come uscita il pin predefinito (13 nel modello UNO)
}

void loop() {  // questo corpo di istruzioni viene ripetuto all'infinito
  digitalWrite(LED_BUILTIN, HIGH);   // accende il LED
  delay(1000);                       // aspetta un tempo in millisecondi
  digitalWrite(LED_BUILTIN, LOW);    // spegne il LED
  delay(1000);                       // aspetta un tempo in millisecondi

/* osservazione: nel codice del programma caricato su Arduino c'è il numero 1000
 * ipotesi: se lo modifichiamo possiamo...
 * esperimento: proviamo con 500, 250, 200 e ogni volta contiamo quante volte il LED
 *              si accende nell'arco di dieci secondi (usare un cronometro).
 * riflessioni: possiamo definire una relazione tra frequenza e tempo in quanto... */












/* ESPERIMENTO 2. ARDUINO, BREADBOARD E POTENZIOMETRO... "ReadAnalogVoltage.ino"
 * Leggiamo un input analogico, convertiamolo nella reale misura di VOLTAGGIO 
 * e visualizziamolo sul monitor seriale o sul plotter seriale
 *
 * Circuito:
 * Attacchiamo il pin centrale del potenziometro al pin A0 
 * e i pin esterni uno al +5V e l'altro a Terra (GND).
 * NB: non collegare mai un pin con la Terra oppure rovinereremo Arduino!
 */
 
void setup() {
  Serial.begin(9600);  // inizializzamo la comunicazione seriale a 9600 bit/secondo
}

void loop() {
  int sensorValue = analogRead(A0);  // leggiamo il valore 
  float voltage = sensorValue * (5.0 / 1023.0);  // convertiamolo
  Serial.println(voltage);  // stampiamolo
}

/* osservazione: ruotando il potenziometro possiamo cambiare il valore del voltaggio
 * ipotesi: nel potenziometro è presente un meccanismo che...
 * esperimento: invertiamo i contatti tra pin esterni del potenziometro.
 * riflessioni: confermiamo l'ipotesi in quanto...      
 */



















/* ESPERIMENTO 3. IL PRIMO SENSORE ANALOGICO - "fotoresistore.ino" 
 * Costruiamo un partitore di tensione con un fotoresistore e un resistore di guardia
 * 
 * Circuito:
 * Colleghiamo un estremo del fotoresistore con un estremo del resistore
 * e da lì partiamo con un filo da collegare ad un ingresso analogico di Arduino;
 * L'altro estremo del fotoresistore andrà a GND e l'altro estremo del resistore a +5V
 */

int x0 = 0;  // creiamo una variabile intera e le diamo un certo valore

void setup() {
  pinMode(13, OUTPUT);  // settiamo come uscita il pin 13
  Serial.begin(9600);   // inizializzamo la comunicazione seriale a 9600 bit/secondo
  x0 = analogRead(A3);   // prendiamo una misura iniziale con luce
}

void loop() {
  Serial.println(analogRead(A3));  // leggiamo i dati per capire quale soglia usare
  if(analogRead(A3)<(x0 - 100)){  // creiamo una soglia adeguata 
    digitalWrite(13,HIGH);  // accendiamo il LED
  }
  else{  // altrimenti
    digitalWrite(13,LOW);  // si spegne il LED
  }
}
/* osservazione: un partitore di tensione è uno strumento potente da usare con sensori analogici
 * (se cambiamo sensore potremmo costruire rilevatori che sfruttano differenti fenomeni fisici)
 * ipotesi: il valore di soglia adeguato dipende da certi fattori... quali?
 * esperimento: potremmo ripetere l'esperimento modificando tali fattori  
 * riflessioni: la preparazione di un sensore analogico ha bisogno di attenzione. */















/* ESPERIMENTO 4. SENSORE A ULTRASUONI - "ultrasuoni.ino" 
 * Impariamo ad usare il sensore HCSR04
 * 
 * Circuito:
 * Inseriamo direttamente nella scheda Arduino il sensore a ultrasuoni,
 * prestando attenzione a quanto scritto qui sotto nelle quattro "define";
 * poi servirà usare il plotter seriale o il monitor seriale
 */
 
#define vccPin 8   // creiamo un parametro e lo colleghiamo ad un certo pin
#define trigPin 9  // creiamo un parametro e lo colleghiamo ad un certo pin
#define echoPin 10  // creiamo un parametro e lo colleghiamo ad un certo pin
#define gndPin 11  // creiamo un parametro e lo colleghiamo ad un certo pin

int led = 13;  // creiamo una variabile intera e le diamo un certo valore
long duration = 0;  // creiamo variabile intera e le diamo un certo valore (in millisecondi)
float distance = 0; // creiamo variabile a virgola mobile e le diamo un certo valore (in cm)

void setup() {
  Serial.begin(9600);  // inizializzamo la comunicazione seriale a 9600 bit/secondo
  pinMode(vccPin, OUTPUT);  // alimentazione sul pin vccPin
  digitalWrite(vccPin, HIGH);
  pinMode(trigPin, OUTPUT);  // pin per HCSR04
  pinMode(echoPin, INPUT);
  pinMode(gndPin, OUTPUT);    // messa a Terra sul pin gndPin
  digitalWrite(gndPin, LOW);
  pinMode(led,OUTPUT);    // un LED per rilevare superamento di soglia
  digitalWrite(led,LOW);
}

void loop() {
  digitalWrite(trigPin, LOW);   // procedura di misura del sensore a ultrasuoni
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);   // cosa viene misurato?

  distance = duration/2.0 * 0.0343;  // cosa viene calcolato?

  if((distance<60) && (distance>0)){    // per un buon grafico sul serial plotter
    Serial.println(distance);  // stampiamolo
    delay(50);
  if(distance > 20){  // creiamo una soglia adeguata 
    digitalWrite(led,HIGH);  // accendiamo il LED
  }
  else{  // altrimenti
    digitalWrite(led,LOW);  // si spegne il LED
  }
  }
}
/* osservazione: che significa il valore 0.0343? E il fattore 2?
 * ipotesi: potrebbe centrare la velocità del suono in aria secca...
 * esperimento: controllare correttezza risultati con un confronto con righello
 * riflessioni: il sensore a ultrasuoni deve mandare un segnale che poi ritorna... */


























/* ESPERIMENTO 5. CONTEGGIAMO I FRONTI DI DISCESA - ANALOGIA CON ARDUSIPM - "EEE.ino" 
 * Riprendiamo l'esperimento 3 del partitore resistivo 
 * con fotoresistore come sensore analogico
 * 
 * Circuito:
 * Colleghiamo un estremo del fotoresistore con un estremo del resistore
 * e da lì partiamo con un filo da collegare ad un ingresso analogico di Arduino;
 * L'altro estremo del fotoresistore andrà a GND e l'altro estremo del resistore a +5V
 */

int x = 0;
int soglia = 0;  // variabile misurata solo all'inizio                

bool stato = false;       // stato e prev_stato falsi: sotto soglia
bool prev_stato = false;  // stato e prev_stato veri: sopra soglia
                          // fronte salita se stato vero ma prev_stato falso
                          // fronte discesa se stato falso ma prev_stato vero
                          
bool count = false;  // variabile che ci dice se stiamo conteggiando o no    
long istante = 0;    // variabile che misura l'istante a inizio conteggio,
                     // che inizierà ad ogni fronte di salita 

#define FINESTRA 10000  // durata fissa di conteggio, in millisecondi
int click = 0;          // variabile che aumenta ad ogni fronte di discesa


void setup() {
  Serial.begin(9600);   // Attiviamo la seriale fissandola a 9600 baud

  x = analogRead(A0); // misuro il valore analogico  
  delay(500);  // aspetto mezzo secondo                  
  x += analogRead(A0); // misuro di nuovo e sommo le prime due misure  
  delay(500);  // aspetto mezzo secondo                  
  x += analogRead(A0); // misuro di nuovo e sommo le prime tre misure    

  soglia = x/3 + 10;  // calcolo la media e sommo un valore adeguato
  Serial.print("soglia = "); Serial.println(soglia);  // stampo la soglia 
}


void loop(){
  x = analogRead(A0);  // misuro il valore analogico del sensore 
  
  //Serial.print(x); Serial.print(" ");  // stampo il valore analogico
  //Serial.println(soglia);  // stampo il valore della soglia e vado a capo
  delay(10);  // attendo 10 millisecondi 

    //Serial.println(stato);
  if(x > soglia){   // lo confronto con la soglia
    stato = true;
  }else{
    stato = false;
  }
  
  if(!prev_stato && stato){        
    digitalWrite(LED_BUILTIN, HIGH);    
    Serial.println("salita");
    if(!count){
      count = true;
      istante = millis();
      Serial.println("start");
      click = 0;
    }
  }
 
  if (prev_stato && !stato){                   
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("discesa");
    click++;
  }

  prev_stato = stato;

  // DI SEGUITO: la differenza (millis() - istante) è intervallo di tempo,
  // se supera la finestra finisce il conteggio, altrimenti riparte col loop         
  if(count && ( (millis()-istante) > FINESTRA) ){   
    count = false;             
    Serial.println("fine");  
    Serial.print("Numero di rilevazioni = "); Serial.println(click); Serial.println("-------");
  }
  
}


// Da Paolo Aliverti:
// Fonte https://www.youtube.com/watch?v=GOGpCERzdns 
//       (partitore resistivo e lettura dati analogici)
// Fonte https://www.youtube.com/watch?v=Utl1bhzv0dY 
//       (fronti salita e discesa)
// Fonte per sviluppo futuro https://www.youtube.com/watch?v=EDYA7WZKhn8 
//       (quanto tempo l'hai premuto)

/* osservazione: Ma se arrivano due "muoni" quasi contemporaneamente?
 * ipotesi: potremmo stimare il tempo per cui si sta sopra soglia e...
 * esperimento: provare a realizzare la situazione indesiderata, seppur rara
 * riflessioni: e per rilevare solo i "muoni" che passano lungo certe direzioni? */



















































// APPROFONDIMENTO
// ESPERIMENTO DI CINEMATICA: 
// LEGGE ORARIA DI DUE CORPI IN MOTO, in tempo reale
//
// Materiale: microcontrollore con cavo USB, 
//            PC o altro con serial plotter
//            2 sensori a ultrasuoni
//            breadboard e cavetti


#define vccPin 3  //14
#define trigPin 4  //15
#define echoPin 5  //16
#define gndPin 6  //17

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






/* APPROFONDIMENTO ARDUINO... "Button.ino" 
 * Se premiamo una volta il pulsante allora accendiamo il LED, se lo premiamo di nuovo lo spegniamo.
 * In logica, una branca della matematica, il ragionamento ipotetico-deduttivo ci permette
 * di collegare tra di loro proposizioni diverse, che in fisica sono associate ad eventi differenti.
 * Il seguente codice presenta una struttura di controllo "if" che descrive una "implicazione" logica
 * per cui ciò che accade al pin digitale 2, il passaggio o meno di corrente, viene dato come input
 * ad Arduino il quale di conseguenza produce un output sul pin digitale 9, agendo dunque sul LED.
 *
 * Circuito:
 * Mettiamo sulla basetta la gamba meno lunga del LED (catodo negativo)
 * collegata con un capo di una resistore di resistenza pari a 220 Ω (Ohm); l'altro capo sarà
 * collegato con un cavetto alla Terra (GND) di Arduino.
 * La gamba più lunga del LED (anodo positivo) la colleghiamo con un cavetto al pin 9.
 * Poi il pulsante sia connesso al pin 2 e ai +5V mentre il pin 2 sia connesso ad un RESISTORE 
 * da 10 kΩ (chilo-Ohm) e l'altro capo di tale resistore sia messo a Terra.
 * NB: non collegare mai un pin con la Terra oppure rovinerai Arduino!
 * 
 * This example code is in the public domain (by DojoDave, Igoe).
 * http://www.arduino.cc/en/Tutorial/Button                       */

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}


/* ... E LE LEGGI DELLA LOGICA (utili anche in FISICA!)
 * osservazione: nel codice del programma caricato su Arduino c'è la stuttura "if-else"
 * ipotesi: se modifichiamo a piacere i valori HIGH e/o LOW in tale struttura possiamo...
 * esperimento: invertiamo nei due digitalWrite HIGH con LOW e vediamo cosa accade, 
 *              poi mettiamo LOW sul pulsante e vediamo cosa accade, poi inviamo messaggi Morse. 
 * riflessioni: l'implicazione logica è utilizzata in molte leggi fisiche, ad esempio... */














/* APPROFONDIMENTO "AnalogInOutSerial.ino" 
 * Leggiamo un input dal potenziometro, mappiamo i valori in un intervallo tra 0 e 255,
 * grazie ad un meccanismo di proporzione, e utilizziamo questo valore per cambiare in output la
 * luminosità del LED tramite una tecnica avanzata chiamata "modulazione di larghezza di impulso"
 * (pulse width modulation PWM). Stampiamo infine i valori sul monitor seriale.
 *
 * Circuito:
 * Attacchiamo il pin centrale del potenziometro al pin A0 
 * e i pin esterni uno al +5V e l'altro a Terra. 
 * Mettiamo la gamba più lunga del LED (anodo positivo) sul pin 9 (di tipo PWM) 
 * e la gamba meno lunga (catodo negativo) al capo di un resistore da 330 Ω (Ohm);
 * mettiamo infine l'altro capo del resistore a Terra.
 *
 * This example code is in the public domain (by Igoe).
 * http://www.arduino.cc/en/Tutorial/AnalogInOutSerial                        */

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}


/* ... E LE LEGGI DELLA FISICA
 * osservazione: ruotando il potenziometro cambia la luminosità!
 * ipotesi: se facciamo una ricerca su questa "modulazione di ampiezza di impulso" allora...
 * esperimento: ognuno faccia questa ricerca e la porti come compito per la prossima volta. 
 * riflessioni: le faremo la prossima volta... */
