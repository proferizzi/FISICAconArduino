// ESPERIMENTO DI INTRODUZIONE AL SENSORE A ULTRASUONI HC-SR04 o HY-SRF05
// OBIETTIVO: confrontare due misure della stessa grandezza fisica, eseguite con uno strumento digitale e uno analogico
// PROCEDURA: L'allievo/a legge sul display la misura e la confronta con la misura analogica fatta col righello.


#define TRIGGER 7   // Dichiarazione dei pin digitali di comunicazione tra sensore e Arduino
#define ECHO  6


void setup(){   // Struttura dello sketch, viene eseguita una sola volta all'avvio e poi dopo ogni reset
  pinMode(TRIGGER, OUTPUT);   // Il sensore riceve dati da Arduino tramite il TRIGGER
  pinMode(ECHO, INPUT);   // Il sensore invia dati ad Arduino tramite l'ECHO
  Serial.begin(9600);    // La porta seriale riceve/invia dati alla velocità di 9600 bit/s (effettivi 7680)
}


void loop(){     //Struttura dello sketch, viene eseguita ripetutamente
  digitalWrite(TRIGGER, LOW);      // Arduino invia un impulso di 10 microsecondi al sensore,
  delayMicroseconds(2);            // il quale invia un treno di otto onde sonore a 40 kHz verso l'ostacolo.
  digitalWrite(TRIGGER, HIGH);   
  delayMicroseconds(10);         
  digitalWrite(TRIGGER, LOW);
  
  long durata = pulseIn(ECHO, HIGH);     // Il sensore riceve il treno di onde e invia ad Arduino 
                                         // l'intervallo di tempo tra invio e arrivo 
  
  // Calcoliamo la distanza tra sensore e oggetto usando il valore, in condizioni standard,
  // della velocità del suono in aria secca. [Considerare sensibilità 3 mm per SR04 e 2 mm per SRF05]
  long distanza = 10 * 0.034 * durata / 2 ;   // fattore 10 per i millimetri  
  
  // Stampa su monitor/plotter seriale la distanza in centimetri.
  if(distanza<500 && distanza>20){   // Struttura di controllo per vedere meglio i dati sul plotter 
  
    Serial.println(distanza);   
  }
  delay(500);   // Il minimo pare sia 30 ms.
}

// Fonti: corso Aliverti oppure Howtomechatronics, commenti miei





















/*

// ESPERIMENTO DI INTRODUZIONE AL SENSORE A ULTRASUONI HC-SR04 o HY-SRF05

#define TRIGGER 7   // Dichiarazione dei pin digitali di comunicazione tra sensore e Arduino
#define ECHO  6


void setup(){   // Struttura dello sketch, viene eseguita una sola volta all'avvio e poi dopo ogni reset
  pinMode(TRIGGER, OUTPUT);   // Il sensore riceve dati da Arduino tramite il TRIGGER
  pinMode(ECHO, INPUT);   // Il sensore invia dati ad Arduino tramite l'ECHO
  Serial.begin(9600);    // La porta seriale riceve/invia dati alla velocità di 9600 bit/s (effettivi 7680)
}


void loop(){     //Struttura dello sketch, viene eseguita ripetutamente
  digitalWrite(TRIGGER, LOW);      // Arduino invia un impulso di 10 microsecondi al sensore,
  delayMicroseconds(2);            // il quale invia un treno di otto onde sonore a 40 kHz verso l'ostacolo.
  digitalWrite(TRIGGER, HIGH);   
  delayMicroseconds(10);         
  digitalWrite(TRIGGER, LOW);
  
  long durata = pulseIn(ECHO, HIGH);     // Il sensore riceve il treno di onde e invia ad Arduino 
                                         // l'intervallo di tempo tra invio e arrivo 
  
  // Calcoliamo la distanza tra sensore e oggetto usando il valore, in condizioni standard,
  // della velocità del suono in aria secca. [Considerare sensibilità 3 mm per SR04 e 2 mm per SRF05]
  long distanza = 10 * 0.034 * durata / 2 ;   // fattore 10 per i millimetri  
  
  // Stampa su monitor/plotter seriale la distanza in centimetri.
  if(distanza<500 && distanza>20){   // Struttura di controllo per vedere meglio i dati sul plotter 
  
    Serial.println(distanza);   
  }
  delay(500);   // Il minimo pare sia 30 ms.
}

// Fonti: corso Aliverti oppure Howtomechatronics, commenti miei

*/













/*

// MODIFICATO PER ESPERIMENTO MOTO ARMONICO CON NANO, BREADBOARD, ELASTICO, PARETE E LAVAINSALATA

// ESPERIMENTO DI INTRODUZIONE AL SENSORE A ULTRASUONI SR04 o SRF05

// Dichiarazione dei pin digitali di comunicazione tra sensore e Arduino
#define VCC 4
#define TRIGGER 5 
#define ECHO  6
#define GND 7


// Struttura dello sketch, viene eseguita una sola volta all'avvio e poi dopo ogni reset
void setup(){
  pinMode(TRIGGER, OUTPUT);   // Il sensore riceve dati da Arduino tramite il TRIGGER
  pinMode(ECHO, INPUT);   // Il sensore invia dati ad Arduino tramite l'ECHO
  Serial.begin(9600);    // La porta seriale riceve/invia dati alla velocità di 9600 bit/s (effettivi 7680)
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);
}


//Struttura dello sketch, viene eseguita ripetutamente
void loop(){
  
  // Arduino invia un impulso di 10 microsecondi al sensore,
  // il quale invia un treno di otto onde sonore a 40 kHz verso l'ostacolo.
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);   
  delayMicroseconds(10);         
  digitalWrite(TRIGGER, LOW);
  
  // Il sensore riceve il treno di onde e invia ad Arduino l'intervallo di tempo tra invio e arrivo 
  long durata = pulseIn(ECHO, HIGH);   
  
  // Calcoliamo la distanza tra sensore e oggetto usando il valore, in condizioni standard,
  // della velocità del suono in aria secca. [Considerare sensibilità 3 mm per SR04 e 2 mm per SRF05]
  long distanza = 10 * 0.034 * durata / 2 ;   // fattore 10 per i millimetri  
  
  // Stampa su monitor/plotter seriale la distanza in centimetri.
  if(distanza<500 && distanza>20){   // Struttura di controllo per vedere meglio i dati sul plotter 
  
    Serial.println(distanza);   
  }
  delay(50);   // Il minimo pare sia 30 ms.
}

// Fonti: corso Aliverti oppure Howtomechatronics, commenti miei

*/



