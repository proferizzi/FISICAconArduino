// ESPERIMENTO DI MRUA CON SINGOLO LED IN MOTO
// pulsante sul pin digitale 2 con interrupt per selezionare partenza da fermo
// con accelerazione costante pari a circa 5 led al secondo quadrato oppure
// frenata fino a fermarsi con decelerazione opposta alla precedente

/*
 * Considerazioni generali:
 * Il sistema è discreto quindi rappresentiamo il tutto come segmenti successivi di moto uniforme.
 * In altre parole, fissato un intervallo di tempo dt consideriamo che in tale tempo il moto sia a velocità costante.
 * Al successivo intervallo dt, aggiorniamo la velocità.
 * il LED resta acceso per il tempo necessario a percorrere una distanza prefissata.
 * Esempio.
 * Fissiamo in 0.2 m la distanza fissa cioè andremo a calcolare il tempo impiegato a percorrerla alle varie velocità.
 * Il tempo di accensione del LED sarà quindi 0.2/v [sec] ossia 200/v [msec] dove v = [m/sec]
 * 
 * Fissiamo anche un intervallo di campionamento, pari a 10msec ossia 0.01 sec
 * chiamo a l'accelerazione costante
 * Al primo campionamento la velocità è pari ad a m/sec  e l'accensione LED corrisponde a 200/a msec. 
 * 
 * Ad ogni istante di campionamento si deve verificare: è esaurito il tempo? Se no non si prosegue 
 * altrimenti si spegne il led e si accende il successivo
 
 *
 * La velocità aumenta costantemente ad ogni intervallo di campionamento, 
 * dopo 1 sec ossia dopo 100 istanti di campionamento la velocità sarà di 10 m/sec con a = 0.1 m/sec^2
 * A questa velocità il LED rimane acceso per 200/10 = 20 msec.
 * 
 * 
 * Non consideriamo il tempo 0 altrimenti andiamo in overflow.
 * dopo 1 msec, la velocità è diventata v = 0 + 0.01  quindi t= 20000 msec
 * dopo 2 msec avremo v=0.01+0.01= 0.02 da cui t= 10000
 * dopo 3 msec v= 0.03 da cui t=6666
 * dopo 100 msec v = 0.01+99*0.01=0.01+0.99=100  da cui t = 2 msec
 *  
 * Considero che minimo un LED deve restare acceso 20msec per essere percepibile
 * 
 * Coordinate LED. considerando il gruppo orizzontale, connettore a sx
 * Ci sono 4 moduli che chiamo m1,m2,m3,m4
 * Ogni modulo ha 8 colonne e 8 rghe numerate da 7 a 0
 * La funzione setLed(modulo,riga,colonna,stato); accende il singolo LED
 * setLed(1,7,7,true); accende il primo LED in alto a sx
 * setLed(1,7,6,true); accende il secondo LED. con parametro false lo spegne
 * setLed(1,7,0,true); accente l8° LED del primo modulo
 * setLed(2,7,7,true); accende il 9° LED della prima riga
 * 
 * 
 * Per semplificare  fisso la variabile colonna da 0 a 7, le variabile righa  da 0 a 7 e la variabile modulo da 0 a 3
 * La colonna effettiva col_e= 7-colonna. riga_e=7-riga, modulo_e=1+modulo 
 * 
 */
#include <LedControl.h>

LedControl lc=LedControl(12, 10, 11, 4);     // DIN, CLK, CS, numero matrici

int modulo=0;
int riga=0;
int colonna=0;

void setup() { 
  for(int a=0 ; a<4 ; a++){  // IMPOSTAZIONI INIZIALI MATRICE LED
    lc.shutdown(a,false);    // equivale a "Write_Max7219(0x0c, 0x01);"
    lc.setIntensity(a,15);   // luminosità 1...15 
    lc.setScanLimit(a,7);    // limite scan, gestisco tutte le 8 righe
    lc.clearDisplay(a);  
  }
  
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);  // aggiunto PULLUP
 // attachInterrupt(digitalPinToInterrupt(2), cambia, FALLING);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);    
} 


// accendi il led alla posizione assegnata
void accendi_LED(int modulo, int riga, int colonna)
{
 lc.setLed(3-modulo,7-riga,7-colonna,true); 
}
// spegni il led alla posizione assegnata
void spegni_LED(int modulo, int riga, int colonna)
{
 lc.setLed(3-modulo,7-riga,7-colonna,false); 
}



// sposta in avanti il puntatore al led e ricicla 
void incrementa_posizione(void)
{
  if(++colonna>7){
                   colonna=0;
                   if(++modulo>3){
                                 modulo=0;
                                 if(++riga>7){
                                             modulo=0;
                                             colonna=0;
                                             riga=0;
                                           }
                               }
                  }
}



float velocita=0;  // parto da fermo
unsigned long t,tp;
int Ts = 1;
float accelerazione = 10; // accelerazione in m/sec
float tempo_led;
int num_passi,tempo_acceso;
float delta_v;

void loop() {
               delta_v= accelerazione*Ts/(1000);  // incremento velocità ad ogni campionamento
      t=millis();
      if((t-tp) > Ts){  // al tempo di campionamento Ts
          tp=t;      
          velocita=velocita+delta_v; // incremento velocità ad ogni campionamento
          tempo_led=200/velocita; // calcolo tempo accensione led
          if(tempo_led<1) tempo_led=1; // non scendo sotto i 1 msec
          num_passi=(int)(tempo_led/Ts); // numero intervalli di campionamento corrispondenti al tempo_led
          accendi_LED(modulo,riga,colonna);
          if(++tempo_acceso > num_passi){ // in caso di supero del tempo di acceso
                                          tempo_acceso=0; // spengo e incremento
                                          spegni_LED(modulo,riga,colonna);
                                          incrementa_posizione();
                                            }
                       }
    
      
     // qui posso aggiungere la gestione seriale
      

      
}

// Fonte Leonardo












/*

// ESPERIMENTO DI MRUA CON SINGOLO LED IN MOTO
// pulsante sul pin digitale 2 con interrupt per selezionare partenza da fermo
// con accelerazione costante quadrato oppure
// frenata fino a fermarsi con decelerazione opposta alla precedente

// testato abbastanza ok

#include <LedControl.h>

LedControl lc=LedControl(12, 10, 11, 4);     // DIN, CLK, CS, numero matrici

int deltat = 0;
int dt = 5;
int tmax = 1000;
int tmin = 20;
unsigned long t = 0;


volatile int stato = 2;
const int PARTENZA = 0;
const int FRENATA = 2;


void setup() { 
  for(int a=0 ; a<4 ; a++){  // IMPOSTAZIONI INIZIALI MATRICE LED
    lc.shutdown(a,false);    // equivale a "Write_Max7219(0x0c, 0x01);"
    lc.setIntensity(a,15);   // luminosità 1...15 
    lc.setScanLimit(a,7);    // limite scan, gestisco tutte le 8 righe
    lc.clearDisplay(a);  
  }
  
  Serial.begin(9600);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), cambia, FALLING);
} 


void loop() {
  switch(stato){    
    case PARTENZA:
      lc.clearDisplay(0);lc.clearDisplay(1);
      lc.clearDisplay(2);lc.clearDisplay(3);
      t = 0;
      deltat = tmax;
      for (int r=0 ; r<8 ; r++){
        for (int a=0 ; a<4 ; a++){
          for (int c=0; c<8 ; c++){ 
            lc.setLed(a,r,c,true);        // Accendo il singolo LED
            //lc.setLed(3-a,7-r,7-c,true);
            //lc.setLed(3-a,7-r,6-c,true);
            //lc.setLed(a,r,7-c,true);    // SOLO PER MATRICE STORTA
            //lc.setLed(3-a,7-r,c,true);  // SOLO PER MATRICE STORTA
            //lc.setLed(3-a,7-r,c-1,true); // SOLO PER MATRICE STORTA
            //Serial.print("c = ");Serial.print(c);Serial.print(" ");
            //Serial.print("a = ");Serial.print(a);Serial.print(" ");
            //Serial.print("r = ");Serial.print(r);Serial.print(" ");
            if(deltat>dt) deltat = deltat - dt;
            //deltat = 10;
            t = millis();
            delay(deltat);
            Serial.println(millis()-t);
            //Serial.println(stato);
            //unsigned long istante_attuale = millis();
            //if((istante_attuale - istante) >= deltat){
            //istante = istante_attuale;
            if(deltat>dt)lc.setLed(a,r,c,false);   // Spengo il singolo LED
            //lc.setLed(a,r,7-c,false); // SOLO PER MATRICE STORTA
            //}
            //unsigned long istante_attualeBIS = millis();
            //if((istante_attualeBIS-istanteBIS) >= deltatBIS){
            //istanteBIS = istante_attualeBIS; 
            //lc.setLed(3-a,7-r,7-c,false); 
            //lc.setLed(3-a,7-r,6-c,false); 
            //lc.setLed(3-a,7-r,c,false);  // SOLO PER MATRICE STORTA
            //lc.setLed(3-a,7-r,c-1,false);  // SOLO PER MATRICE STORTA
            //}
            if(stato == 2){ r = 8; a = 4; c= 8; }
          }
        }
      }
    break;

    case FRENATA:
      lc.clearDisplay(0);lc.clearDisplay(1);
      lc.clearDisplay(2);lc.clearDisplay(3);
      t = 0;
      deltat = tmin;
      for (int r=0 ; r<8 ; r++){
        for (int a=0 ; a<4 ; a++){
          for (int c=0; c<8 ; c++){ 
            lc.setLed(a,r,c,true);        // Accendo il singolo LED
            //lc.setLed(3-a,7-r,7-c,true);
            //lc.setLed(3-a,7-r,6-c,true);
            //lc.setLed(a,r,7-c,true);    // SOLO PER MATRICE STORTA
            //lc.setLed(3-a,7-r,c,true);  // SOLO PER MATRICE STORTA
            //lc.setLed(3-a,7-r,c-1,true); // SOLO PER MATRICE STORTA
            //Serial.print("c = ");Serial.print(c);Serial.print(" ");
            //Serial.print("a = ");Serial.print(a);Serial.print(" ");
            //Serial.print("r = ");Serial.print(r);Serial.print(" ");
            if(deltat<tmax) deltat = deltat + dt;
            //deltat = 10;
            t = millis();
            delay(deltat);
            Serial.println(millis()-t);
            //Serial.println(stato);
            //unsigned long istante_attuale = millis();
            //if((istante_attuale - istante) >= deltat){
            //istante = istante_attuale;
            if(deltat<tmax) lc.setLed(a,r,c,false);   // Spengo il singolo LED
            //lc.setLed(a,r,7-c,false); // SOLO PER MATRICE STORTA
            //}
            //unsigned long istante_attualeBIS = millis();
            //if((istante_attualeBIS-istanteBIS) >= deltatBIS){
            //istanteBIS = istante_attualeBIS; 
            //lc.setLed(3-a,7-r,7-c,false); 
            //lc.setLed(3-a,7-r,6-c,false); 
            //lc.setLed(3-a,7-r,c,false);  // SOLO PER MATRICE STORTA
            //lc.setLed(3-a,7-r,c-1,false);  // SOLO PER MATRICE STORTA
            //}
            if(stato == 0){ r = 8; a = 4; c= 8; }
          }
        }
      }
    break;
  }
}


void cambia(){
  stato = stato + 1;
  if(stato == 4) stato = 0;
}

// Fonte: http://www.brescianet.com/ e
//        https://www.arduino.cc/en/tutorial/BlinkWithoutDelay,
//        poi modificato da me al bisogno
// Fonte pulsante https://www.youtube.com/watch?v=cBojpLr9ARk
//       con interrupt https://www.youtube.com/watch?v=7Xo9mAMZPjQ


*/
