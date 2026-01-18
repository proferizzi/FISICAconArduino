/* LE LEGGI DELLA FISICA CON ARDUINO! PROVA... IMPARA... DISCUTI...
 * A cura di Marco Rizzinelli - progetto EEE a.s. 2025/26
 * Benvenuti/e! In questo corso cerchiamo di vivere le fasi del metodo scientifico:
 * osservazione, ipotesi, esperimento (materiale, procedura, dati, analisi), riflessioni. 
 * Io girerò tra i gruppi e così lavoreremo un po' insieme! 
 * 
 * BREVISSIMA INTRODUZIONE AD ARDUINO
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




/* NOTA BENE! OGNI SKETCH VA COPIATO E INCOLLATO IN UN NUOVO FILE, PER POTER FUNZIONARE */




/* ESPERIMENTO 1. ARDUINO LAMPEGGIA - "Blink.ino" 
 * Accendiamo e spegniamo ripetutamente una luce LED a intervalli di un secondo.
 * Un LED è un DIODO A EMISSIONE di LUCE ed è una sorgente di FOTONI/ONDE ELETTROMAGNETICHE.
 * Questo significa che il materiale (semiconduttore) con cui è costruito
 * il diodo, alimentato con un certo voltaggio, emette luce spontaneamente e a determinati colori.
 *
 * Circuito facile: Scheda Arduino + cavo USB + PC
 * Usiamo il LED integrato nella scheda Arduino.
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
 * esperimentI: proviamo con 500, 250, 200 e ogni volta contiamo quante volte il LED
 *              si accende nell'arco di dieci secondi (usare un cronometro),
 *              oppure diminuiamo il valore finché l'occhio umano non riesce più
 *              distinguere il lampeggiamento, quale è il valore minimo? 
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


















