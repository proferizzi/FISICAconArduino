// ESPERIMENTO DI MRU CON SINGOLO LED IN MOTO
// TEST ok solo con due segnali in moto a velocità opposte controllate dal potenziometro
// Bisognerebbe gestire i tempi senza usare lo stesso delay 
// ma ho problemi con annidamento in ciclo for

#include <LedControl.h>

LedControl lc=LedControl(12, 10, 11, 4);     // DIN, CLK, CS, numero matrici


//unsigned long istante = 0;
//unsigned long istanteBIS = 0;

int pot = 0;
int deltat = 0;
//long deltatBIS = 0;           


void setup() { 
  for(int a=0 ; a<4 ; a++){
    lc.shutdown(a,false);    // equivale a "Write_Max7219(0x0c, 0x01);"
    lc.setIntensity(a,15);     // luminosità 1...15 
    lc.setScanLimit(a,7);    // limite scan, gestisco tutte le 8 righe
    lc.clearDisplay(a);  
  }
  pinMode(4, OUTPUT);     // settaggio vcc e gnd per potenziometro, se serve
  digitalWrite(4, HIGH);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);  
  Serial.begin(9600);
  //randomSeed(analogRead(2));
  //deltatBIS = random(20,500);
} 


void loop() { 
  for (int r=0 ; r<8 ; r++){
    for (int a=0 ; a<4 ; a++){
      for (int c=0; c<8 ; c++){ 
        lc.setLed(a,r,c,true);        // Accendo il singolo LED
        lc.setLed(3-a,7-r,7-c,true);
        lc.setLed(3-a,7-r,6-c,true);
        //lc.setLed(a,r,7-c,true);    // SOLO PER MATRICE STORTA
        //lc.setLed(3-a,7-r,c,true);  // SOLO PER MATRICE STORTA
        //lc.setLed(3-a,7-r,c-1,true); // SOLO PER MATRICE STORTA
        pot = analogRead(A0);
        deltat = map(pot,0,1023,500,20);
        //Serial.println(c);
        //deltat = 100;
        delay(deltat);
        //unsigned long istante_attuale = millis();
        //if((istante_attuale - istante) >= deltat){
        //istante = istante_attuale;
        lc.setLed(a,r,c,false);   // Spengo il singolo LED
        //lc.setLed(a,r,7-c,false); // SOLO PER MATRICE STORTA
        //}
        //unsigned long istante_attualeBIS = millis();
        //if((istante_attualeBIS-istanteBIS) >= deltatBIS){
        //istanteBIS = istante_attualeBIS; 
        lc.setLed(3-a,7-r,7-c,false); 
        lc.setLed(3-a,7-r,6-c,false); 
        //lc.setLed(3-a,7-r,c,false);  // SOLO PER MATRICE STORTA
        //lc.setLed(3-a,7-r,c-1,false);  // SOLO PER MATRICE STORTA
        //}
      }
    }
  }
}


// Fonte: http://www.brescianet.com/ e
//        https://www.arduino.cc/en/tutorial/BlinkWithoutDelay,
//        poi modificato da me al bisogno






// PROPOSTA DI MARIA
// cont ++;
// if cont % analogread primo pot
       //refresh
//  altro if con altro analogread pot 2
     //refresh
     delay(tempo base)
       




/*


// ESPERIMENTO DI CINEMATICA UNIDIMENSIONALE SUL MOTO RETTILINEO UNIFORME
// Materiale: Scheda con microcontrollore, Matrice di LED MAX7219, potenziometro, cavetti,
//            cronometro, righello, cellulare con app "YouCut" installata
//
// Obiettivo: Osservare una riga che viaggia a velocità costante scelta dal potenziometro;
//            Misurare gli istanti di partenza e arrivo col cronometro e lo spazio percorso col righello;
//            Fare un video col cellulare e con l'app individuare l'intervallo di tempo e lo spazio percorso;
//            Calcolare per ogni situazione la velocità media in n°LED/s e cm/s;


//#define Next_POINT_DELAY  4    // INTERVALLO DI TEMPO ---> VELOCITÀ
// lento < v < veloce ---> da 400 a 4
int Next_POINT_DELAY = 4;

#define pinPot 0   // pin del potenziometro per scegliere la velocità

#include <MD_MAX72xx.h>
#include <SPI.h>
#include <MD_UISwitch.h>

// MD_MAX72xx definizioni hardware e oggetto: quanti device e l'interfaccia 
// NOTE: adattare i numeri pin al proprio hardware
//#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  // funziona! non va più al contrario (col vecchio)
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW  // funziona con quelli nuovi
// alternative con //ICSTATION_HW  //GENERIC_HW
#define MAX_DEVICES 4
#define CLK_PIN   11  // o SCK
#define DATA_PIN  12  // o MOSI
#define CS_PIN    10  // o SS

//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);  // interfaccia SPI
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);  // pin arbitrari

// Parametri e oggetto della modalità keyswitch
#define MODE_SWITCH 411 // Digital Pin
MD_UISwitch_Digital  ks = MD_UISwitch_Digital(MODE_SWITCH, LOW);

// Variabile
uint32_t prevTime = 0;    // Usata per ricordare il valore millis()


void setup(){
  Serial.begin(9600);
  mx.begin();
  ks.begin();
  //#if DEBUG
  //Serial.begin(57600);
  //#endif
  //PRINTS("\n[MD_MAX72XX Scroll Chart]");
   pinMode(13,OUTPUT);      // per avere i 5V sul pin del potenziometro
  digitalWrite(13,HIGH);
  pinMode(3,OUTPUT);      // per avere il GND sul pin del potenziometro
  digitalWrite(3,LOW);
}


void loop(){
  // Per calibrare i tempi
  int pot = analogRead(pinPot);
  int Next_POINT_DELAY = map(pot, 0, 1023, 4, 400);

  if (Next_POINT_DELAY > 200) {
    for (int i = 0 ; i < 130 ; i++) {
      runAnimation();
      delay(100);
    }
    resetDisplay();

  } else {
    for (int i = 0 ; i < 165 ; i++) {
      runAnimation();
      delay(40);
    }
    resetDisplay();
  }

}


// Funzione che riordina le animazioni, 
// spostandosi sulla successiva quando si preme la modalità switch
void runAnimation(void) {
  static  uint8_t state = 0;
  static  bool    bRestart = true;

  // guarda se switch è premuto 
  if (ks.read() == MD_UISwitch::KEY_PRESS) {
    state = (state + 1) % 3;
    bRestart = true;
  };  //???
  // ora compie le azioni nello stato corrente
  bRestart = graphDisplay(bRestart, state);
}


// Funzione grafica
bool graphDisplay(bool bInit, uint8_t nType){
  static int8_t  curPoint = 0;
  uint8_t curCol = 0;

  int pot = analogRead(pinPot);
  int Next_POINT_DELAY = map(pot, 0, 1023, 4, 400);
  Serial.print(pot);
  Serial.print(" ");
  Serial.println(Next_POINT_DELAY);

  // si chiede se stiamo facendo inizializzazione
  if (bInit) {
    resetDisplay();
    curPoint = 4;
    bInit = false;
  }
  else if (millis() - prevTime >= Next_POINT_DELAY) {
    Serial.print(millis());
    Serial.print(" ");
    Serial.println(Next_POINT_DELAY);
    prevTime = millis();    // salva il dato per il prossimo ciclo

    // tira fuori il nuovo valore di altezza dipendendo dal tipo di grafico
    switch (nType) {
      // NOI PER QUESTO ESPERIMENTO SIAMO IN QUESTO CASO
      case 0:  // visualizzazione continua del punto successivo: +/-1 or 0
        //curPoint += random(3) - 1;  // movimento casuale verticale
        curPoint = 0;
        if (curPoint < 0) curPoint = 0;
        if (curPoint > 7) curPoint = 7;
        break;

      case 1:  // altezza casuale
      case 2:
        //curPoint = random(8);  // movimento casuale verticale?
        curPoint = 1;
        break;
    }

    // ora tira fuori il nuovo valore di colonna
    switch (nType) {
      case 2:   // solo un punto
      case 1:
        curCol = (1 << curPoint);
        break;
      // SIAMO IN QUESTO CASO
      case 0:   // grafico a barre
        for (uint8_t i = 0; i < 8; i++)
          curCol |= (i < curPoint ? 0 : 1) << i;
        break;
    }

    // Si sposta avanti e inserisce la nuova colonna
    mx.transform(MD_MAX72XX::TSL);
    mx.setColumn(0, curCol);
  }
  return (bInit);
}


// Funzione di controllo
void resetDisplay(void){
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  prevTime = 0;
}

#define DEBUG 0   // Attiva (1) o disattiva (0) l'output di debug
#if DEBUG
#define PRINT(s, v)   { Serial.print(F(s)); Serial.print(v); }       // Stampa una stringa seguita da un valore (decimale)
#define PRINTX(s, v)  { Serial.print(F(s)); Serial.print(v, HEX); }  // idem (esadecimale)
#define PRINTB(s, v)  { Serial.print(F(s)); Serial.print(v, BIN); }  // idem (binario)
#define PRINTC(s, v)  { Serial.print(F(s)); Serial.print((char)v); } // idem (carattere)
#define PRINTS(s)     { Serial.print(F(s)); }                        // idem 
#else
#define PRINT(s, v)   // idem come sopra, stessa sequenza
#define PRINTX(s, v)  
#define PRINTB(s, v)  
#define PRINTC(s, v)  
#define PRINTS(s)     
#endif



// Test: ok con NANO (OldBootloader)
//
// Fonte : Colli (MajicDesigns on github) esempio "MD_MAX72XX_ScrollChart" poi modificato da me al bisogno


*/
