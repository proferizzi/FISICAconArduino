
// ESPERIMENTO DI INTRODUZIONE AL SENSORE A ULTRASUONI HC-SR04 o HY-SRF05
// OBIETTIVO: confrontare due misure della stessa grandezza fisica, eseguite con uno strumento digitale e uno analogico
// PROCEDURA: L'allievo/a legge sul display la misura e la confronta con la misura analogica fatta col righello.


// °°°°°°°°°°°°°°°°°°°°°°°°°°° IMPOSTAZIONI INIZIALI

#include <Wire.h>    // Librerie utili per display LCD1602 con interfaccia I2C
#include <LiquidCrystal_I2C.h>

#define VCC 4       // Dichiarazione dei pin digitali di comunicazione tra sensore e Arduino
#define TRIGGER 5   // e anche di alimentazione, utile per montare il sensore direttamente su scheda UNO
#define ECHO  6
#define GND 7

LiquidCrystal_I2C lcd(0x27, 16, 2);   // Imposta l'indirizzo I2C del display a 0x27 


// Struttura dello sketch, viene eseguita una sola volta all'avvio e poi dopo ogni reset
void setup(){
  pinMode(TRIGGER, OUTPUT);   // Il sensore riceve dati da Arduino tramite il TRIGGER
  pinMode(ECHO, INPUT);       // Il sensore invia dati ad Arduino tramite l'ECHO
  Serial.begin(9600);         // La porta seriale riceve/invia dati alla velocità di 9600 bit/s (effettivi 7680)
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);
    
  pinMode(16,OUTPUT);  // pin analogici A2 e A3 usati come digitali, per alimentazione al display, nel caso serva
  digitalWrite(16,LOW);
  pinMode(17,OUTPUT);  
  digitalWrite(17,HIGH);
  
	lcd.begin();          // inizializza il display, accende la retroilluminazione e invia messaggio di ok
	lcd.backlight();
	lcd.print("Pronto a misurare");
}



// °°°°°°°°°°°°°°°°°°°°°°° PARTE ESECUTIVA PRINCIPALE

void loop(){    //Struttura dello sketch, viene eseguita ripetutamente
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
    lcd.print(distanza);
  }
  delay(50);   // Il minimo pare sia 30 ms.
}


// Fonti per sensore: corso Aliverti oppure Howtomechatronics, commenti miei
// Fonte per LCD commento in corso Aliverti 219, diverso dallo sketch
// ecco qui http://scienceclub.org.au/download/1602-lcd-display-serial-connection-arduino-library/
// Inoltre: modifica mia per VCC e GND su pin analogici, se non va LCD non dimenticare i2cscanner.ino

// giugno 2021, ancora da testare



















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



