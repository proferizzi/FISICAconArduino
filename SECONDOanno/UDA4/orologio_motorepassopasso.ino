// 5 sketch










// ESPERIMENTO DI CINEMATICA ROTAZIONALE: VELOCITA' ANGOLARE
// Materiale: scheda Arduino con cavetti,
//            motore passo passo 28BYJ-48 (con driver ULN2003APG),
//            quadrante e lancetta
//            encoder rotativo che pilota una variazione di velocità, 
//            alimentazione esterna (power bank con regolatore di tensione a 5V)
//            display LCD 1602 per mostrare il numero di giri

#include "Stepper.h"  // libreria per usare il motore passo passo
#include <Wire.h>     // libreria per la comunicazione I2C 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define STEPS  32  // n° passi per una rivoluzione dell'asse interno, 2048 (?) passi per quello esterno 

volatile boolean TurnDetected;  // variabili di tipo volatile necessarie per l'interrupt 
volatile boolean rotationdirection;  

int RotaryPosition = 0;   // per salvare la posizione
int PrevPosition;    // precedente posizione per controllo accuratezza

#define PinCLK 2   // PIN ENCODER ROTATIVO, il segnale CLK genera l'Interrupt 
#define PinDT 3    // segnale di lettura 
#define PinSW 4    // legge la pressione del pulsante incorporato nell'encoder

#define RISOLUZIONE 50  // PARAMETRI DI CONTROLLO: passo minimo del motore passo passo 
int speed = 300;       // e velocità iniziale (effetto su posizione e velocità angolari) 

Stepper small_stepper(STEPS, 8, 10, 9, 11);   // PIN MOTORE PASSO PASSO In1, In2, In3, In4 in sequenza 1-3-2-4 

int x = 0;  // lettura sensore magnetico

bool tasto = false;
bool prev_tasto = false;

int n = 0;


void isr () {   // La routine Interrupt gira se CLK va da HIGH a LOW
  delay(4);     // pausa per Debouncing
  if (digitalRead(PinCLK)) rotationdirection= digitalRead(PinDT);
  else rotationdirection= !digitalRead(PinDT); TurnDetected = true; 
}


void setup () { 
  pinMode(PinCLK,INPUT); 
  pinMode(PinDT,INPUT); 
  pinMode(PinSW,INPUT); 
  digitalWrite(PinSW, HIGH); // Pulsante con resistore Pull-Up
  attachInterrupt (0,isr,FALLING);  // Interrupt 0 deve essere sempre connessa al pin 2 di Arduino UNO
  
  pinMode(16,OUTPUT);  // pin analogico A2
  digitalWrite(16,LOW);
  pinMode(17,OUTPUT);  // pin analogico 
  digitalWrite(17,HIGH);
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("numero di giri");
  //Serial.begin(9600);
} 


void loop () { 
  small_stepper.setSpeed(speed);  // Pare che il massimo sia 700 (?)
  if (!(digitalRead(PinSW))) {  // controlla se il pulsante è stato premuto
    speed=300;                  // e in tal caso resetta la velocità 
  } 
  if (TurnDetected) {  // Si attiva se viene individuata una rotazione dell'encoder
    PrevPosition = RotaryPosition; // Salva la posizione precedente 
    if (rotationdirection) { 
      RotaryPosition=RotaryPosition-1;  // diminuisce la variabile per selezionare poi il tipo di variazione 
    }                                   // di velocità che subirà il motore, se diminuzione o aumento
    else { 
      RotaryPosition=RotaryPosition+1;   // la aumenta
    } 
    TurnDetected = false; // per NON ripetere la struttura IF fino a nuova individuazione di rotazione
   
    if ((PrevPosition + 1) == RotaryPosition) { // Per aumentare la velocità del motore (antiorario encoder)
      speed += 50;
      small_stepper.setSpeed(speed);
    } 
    if ((RotaryPosition + 1) == PrevPosition) { // Per diminuire la velocità del motore (orario encoder)
      speed -= 50;
      small_stepper.setSpeed(speed);
    } 
  }
  
  small_stepper.step(RISOLUZIONE);  // muove il motore di un passo, con la velocità appena settata
  
  x = analogRead(A0);
  
  if( x > 550 ){
    tasto = true;
  }else{
    tasto = false;
  }

  if (!prev_tasto && tasto) {
    //Serial.println("inizio passaggio");
    lcd.clear();
    lcd.print(x);
    lcd.print(" ");
    lcd.print(millis());
    lcd.print(" ");
    prev_tasto = tasto;     
  }
  
  if (prev_tasto && !tasto) {
    //Serial.println("fine passaggio");
    //Serial.println(x);
    prev_tasto = tasto;
    lcd.print(n);
    lcd.print(" ");
    lcd.print(x);
    lcd.print(" ");
    lcd.print(millis());
    n++;
  } 
   
}

// Fonte MOTORE E ENCODER: https://www.brainy-bits.com/stepper-motor-rotary-encoder-p1/
// Supporto: Maria Panteghini
// Datasheet https://www.alldatasheet.com/datasheet-pdf/pdf/470261/TOSHIBA/ULN2003APG.html

// Fonte LCD commento in corso Aliverti 219, diverso dallo sketch
// ecco qui http://scienceclub.org.au/download/1602-lcd-display-serial-connection-arduino-library/
// Inoltre: modifica mia per VCC e GND su pin analogici, non dimenticare i2cscanner.ino
//          e modifica mia per conteggio giri a partire da corso Aliverti #43

// TEST CON OSCILLOSCOPIO giugno 2020: file 30 e 31 





















/*


// ESPERIMENTO DI CINEMATICA ROTAZIONALE: VELOCITA' ANGOLARE           [senza LCD]
// Materiale: scheda Arduino con cavetti,
//            motore passo passo 28BYJ-48 (con driver ULN2003APG),
//            quadrante e lancetta
//            encoder rotativo che pilota una variazione di velocità, 
//            alimentazione esterna (power bank con regolatore di tensione a 5V)

#include "Stepper.h"
#include <Wire.h> 

#define STEPS  32  // N° passi per una rivoluzione dell'asse interno, 2048 (?) passi per quello esterno 
volatile boolean TurnDetected;  // tipo volatile necessario per avere l'Interrupt 
volatile boolean rotationdirection;  // utile per rotazione oraria o antioraria dell'encoder
int RotaryPosition = 0; // per salvare la posizione
int PrevPosition; // precedente posizione per controllo accuratezza

#define PinCLK 2   // PIN ENCODER ROTATIVO, il segnale CLK genera l'Interrupt 
#define PinDT 3    // segnale di lettura 
#define PinSW 4    // legge la pressione del pulsante incorporato nell'encoder

#define RISOLUZIONE 50  // PARAMETRI DI CONTROLLO: passo minimo del motore passo passo 
#define speed 300       // e velocità iniziale (effetto su posizione e velocità angolari) 

Stepper small_stepper(STEPS, 8, 10, 9, 11);   // PIN MOTORE PASSO PASSO In1, In2, In3, In4 in sequenza 1-3-2-4 


void isr () {   // La routine Interrupt gira se CLK va da HIGH a LOW
  delay(4);     // pausa per Debouncing
  if (digitalRead(PinCLK)) rotationdirection= digitalRead(PinDT);
  else rotationdirection= !digitalRead(PinDT); TurnDetected = true; 
}


void setup () { 
  pinMode(PinCLK,INPUT); 
  pinMode(PinDT,INPUT); 
  pinMode(PinSW,INPUT); 
  digitalWrite(PinSW, HIGH); // Pulsante con resistore Pull-Up
  attachInterrupt (0,isr,FALLING);  // Interrupt 0 deve essere sempre connessa al pin 2 di Arduino UNO
} 


void loop () { 
  small_stepper.setSpeed(speed);  // Pare che il massimo sia 700 (?)
  if (!(digitalRead(PinSW))) {  // controlla se il pulsante è stato premuto
    speed=300;                  // e in tal caso resetta la velocità 
  } 
  if (TurnDetected) {  // Si attiva se viene individuata una rotazione dell'encoder
    PrevPosition = RotaryPosition; // Salva la posizione precedente 
    if (rotationdirection) { 
      RotaryPosition=RotaryPosition-1;  // diminuisce la variabile per selezionare poi il tipo di variazione 
    }                                   // di velocità che subirà il motore, se diminuzione o aumento
    else { 
      RotaryPosition=RotaryPosition+1;   // la aumenta
    } 
    TurnDetected = false; // per NON ripetere la struttura IF fino a nuova individuazione di rotazione
   
    if ((PrevPosition + 1) == RotaryPosition) { // Per aumentare la velocità del motore (antiorario encoder)
      speed += 50;
      small_stepper.setSpeed(speed);
    } 
    if ((RotaryPosition + 1) == PrevPosition) { // Per diminuire la velocità del motore (orario encoder)
      speed -= 50;
      small_stepper.setSpeed(speed);
    } 
  }
  
  small_stepper.step(RISOLUZIONE);  // muove il motore di un passo, con la velocità appena settata
  
}

// Fonte: https://www.brainy-bits.com/stepper-motor-rotary-encoder-p1/
// Supporto: Maria Panteghini
// Datasheet https://www.alldatasheet.com/datasheet-pdf/pdf/470261/TOSHIBA/ULN2003APG.html
// Test: ok con ARDUINO UNO (a) e NANO (a) e PC, ok anche alimentato con power 


*/






























/*


// ESPERIMENTO DI CINEMATICA ROTAZIONALE: POSIZIONE ANGOLARE
// materiale: motore passo passo e encoder rotativo

#include "Stepper.h"  // libreria per il motore passo passo
#include <Wire.h> // xxx? 
#define STEPS 32  // n° passi per una rivoluzione interna che corrispondono a 2048 xxx? passi per una rivoluzione esterna
volatile boolean TurnDetected;  // serve per l'Interrupt
volatile boolean rotationdirection;  // rotazione oraria o antioraria
const int PinCLK = 2;  // per generare l'Interrupt usando il segnale CLK dell'encoder
const int PinDT = 3;  // per leggere il segnale DT dell'encoder
const int PinSW = 4;  // per leggere se si preme il pulsante dell'encoder
const int RISOLUZIONE = 50;  // 90 GRADI 257 xxx?
int RotaryPosition = 0;  // per salvare la posizione del motore passo passo
int PrevPosition;  // valore della posizione precedente dell'encoder, per testare l'accuratezza
int StepsToTake;  // quanto si muove il motore passo passo

// Settaggio della corretta sequenza per i pin del motore passo passo: In1, In2, In3, In4 con sequenza 1-3-2-4 
Stepper small_stepper(STEPS, 8, 10, 9, 11);  

// Funzione di Interrupt che si attiva se il CLK passa da HIGH a LOW, identifica la direzione di rotazione
void isr(){  
  delay(4);  // attesa per debouncing
  if (digitalRead(PinCLK)) rotationdirection = digitalRead(PinDT);
  else rotationdirection = !digitalRead(PinDT); 
  TurnDetected = true; 
}


void setup(){ 
  pinMode(PinCLK,INPUT);  // funzione presa dalle librerie restituisce void 
  pinMode(PinDT,INPUT);
  pinMode(PinSW,INPUT); 
  digitalWrite(PinSW,HIGH);  // pulsante di tipo pull-up
  attachInterrupt(0,isr,FALLING);  // interrupt 0 sempre connesso al pin del CLK
} 


void loop () { 
  small_stepper.setSpeed(600);  // max sembra essere 700
  
  if(!(digitalRead(PinSW))){  // riporta a zero se schiaccio il bottone
    if (RotaryPosition == 0){  
    }
    else{ 
      small_stepper.step(-(RotaryPosition*RISOLUZIONE));
      RotaryPosition = 0;  
    } 
  } 
  
  if(TurnDetected){  // se avviene la rotazione 
    PrevPosition = RotaryPosition;  // salva la precedente posizione
    if(rotationdirection){  // diminuisce di uno 
      RotaryPosition = RotaryPosition-1;
    }  
    else{  // aumenta di uno 
      RotaryPosition = RotaryPosition+1;
    }  
    TurnDetected = false; // non ripete il ciclo IF fino a nuova rilevazione di rotazione

   // Ciclo per individuare in quale senso di rotazione muovere il motore passo passo 
   if ((PrevPosition + 1) == RotaryPosition) { // senso orario (o viceversa)
     StepsToTake=RISOLUZIONE; 
     small_stepper.step(StepsToTake); 
   } 
   if ((RotaryPosition + 1) == PrevPosition) { // senso antiorario (o viceversa) 
     StepsToTake=-RISOLUZIONE; 
     small_stepper.step(StepsToTake); 
   } 
 } 
}


// fonti primarie:
// fonte https://www.brainy-bits.com/stepper-motor-rotary-encoder-p1/
// supporto: Maria Panteghini


*/


































/*


// MOTORE PASSO PASSO - con Arduino UNO da tablet ok
// senza uso della libreria

// pin di collegamento col motore
const int  IN1 = 8;   
const int  IN2 = 9;   
const int  IN3 = 10;  
const int  IN4 = 11;  

// costante per motore spento
const int MotoreOFF = 99; 

// funzione a quattro variabili che alza o abbassa i pin
void Uscita( int i4,int i3,int i2,int i1){
  if (i1==1) digitalWrite(IN1,HIGH); else digitalWrite(IN1,LOW);
  if (i2==1) digitalWrite(IN2,HIGH); else digitalWrite(IN2,LOW);
  if (i3==1) digitalWrite(IN3,HIGH); else digitalWrite(IN3,LOW);
  if (i4==1) digitalWrite(IN4,HIGH); else digitalWrite(IN4,LOW);
}

// funzione a una variabile che imposta il movimento del motore in otto casi distinti
void EseguiPasso(int stato){
  int i1,i2,i3,i4;
  switch ( stato ) {  // vedi tabella nel PDF del motore passo passo
       case 0: Uscita(0,0,0,1); break;
       case 1: Uscita(0,0,1,1); break;
       case 2: Uscita(0,0,1,0); break; 
       case 3: Uscita(0,1,1,0); break;
       case 4: Uscita(0,1,0,0); break;
       case 5: Uscita(1,1,0,0); break;
       case 6: Uscita(1,0,0,0); break;
       case 7: Uscita(1,0,0,1); break;
       case MotoreOFF: Uscita(0,0,0,0); break;
  } 
  delay(1); //ritardo almeno 1 mS
}  

// funzione di attesa prima di accendere il motore
void RitardoAccensione(){ 
  EseguiPasso(MotoreOFF); 
  for(int i=0; i<20; i++){
    digitalWrite(13,HIGH);
    delay(250);
    digitalWrite(13,LOW);
    delay(250);
  } 
}  


void setup()
{
    pinMode(IN1, OUTPUT); 
    pinMode(IN2, OUTPUT); 
    pinMode(IN3, OUTPUT); 
    pinMode(IN4, OUTPUT);
    pinMode(13,OUTPUT); 
    RitardoAccensione();  
}


void loop(){
  int stato;  
  stato=0; //inizio da uno stato arbitrario
  //digitalWrite(13,HIGH);  

  // realizzo un movimento di rotazione oraria
  for(int k=0; k<4; k++){
    for (int i=0; i<1024; i++) { // 90 gradi a ciclo 
        EseguiPasso(stato);
        stato+=1; // avanza nella tabella
        if ((stato)>7) stato=0; 
      } 
    EseguiPasso(MotoreOFF);  
    delay(500);  // pausa di mezzo secondo
  }  
  delay(1000); // pausa di 1 secondo
  //digitalWrite(13,LOW);  //spento LED13

  // realizzo un movimento di rotazione antioraria
  for(int k=0; k<4; k++){
    for (int i=0; i<1024; i++) { // 90 gradi a ciclo
        EseguiPasso(stato);
        stato-=1; //torna indietro nella tabella
        if ((stato)<0) stato=7; 
      } 
    EseguiPasso(MotoreOFF);  
    delay(500);
    }
  delay(1000);  
}
// Fonte: https://aspettandoilbus.blogspot.com/2014/09/collegare-il-motore-passo-passo-28byj.html


*/




































/*


// ok con UNO e tablet

#include <Stepper.h>
 const int stepsPerRevolution = 500; //Inicializa a biblioteca utilizando as portas de 8 a 11 para //ligacao ao motor
 Stepper myStepper(stepsPerRevolution, 8,10,9,11); 

void setup() { //Determina a velocidade inicial do motor
 myStepper.setSpeed(60); }

 void loop() { //Gira o motor no sentido horario a 90 graus 
for (int i = 0; i<=3; i++) { 
myStepper.step(-512); 
delay(2000); } //Gira o motor no sentido anti-horario a 120 graus
 for (int i = 0; i<=2; i++) { 
myStepper.step(682); 
delay(2000); } //Gira o motor no sentido horario, aumentando a //velocidade gradativamente 
for (int i = 10; i<=60; i=i+10) { 
myStepper.setSpeed(i); 
myStepper.step(40*i); } 
delay(2000); }

// fonte https://www.filipeflop.com/blog/controlando-um-motor-de-passo-5v-com-arduino/


*/
