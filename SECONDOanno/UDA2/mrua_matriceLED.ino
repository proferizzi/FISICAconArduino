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


volatile int stato = 0;
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
