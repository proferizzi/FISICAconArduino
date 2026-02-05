// Sequencer a 5 passi in tre possibili configurazioni:
//
// 1) Pentatonica in LA minore 
// 2) Idem ma ripetendo solo due note
// 3) Idem ma con frequenze mescolate casualmente con algoritmo di Fisher-Yates 
//
// Il clock del sequencer è regolato da misurazione della distanza
// con sensore a ultrasuoni e filtro  di Kalman

 

int pitch_untouched[5] = {220, 262, 294, 330, 392};
int pitch_untouchedBIS[5] = {220,294,220,294,220};
int pitch[5] = {220, 262, 294, 330, 392};
int result[5];
int flag = 0;
int temp[5];

int i = 0;


long duration = 0;  // Creiamo variabile intera e le diamo un certo valore (in millisecondi)
float distance = 0; // Creiamo variabile a virgola mobile e le diamo un certo valore (in cm)
// IMPOSTAZIONI INIZIALI DEI PARAMETRI PER IL FILTRO di KALMAN
float x_est = 0;  // stima iniziale, dipende dal fenomeno studiato
float P = 1;   // incertezza stima, dipende dal fenomeno studiato
float Q = 0.75;  // basso se il dato cambia poco, 
                 // se cambia molto si aumenta fino a 1
float R = 4; // vicino a 1 se è poco rumoroso il sensore, altrimenti verso il 10
float kout;

#define trigPin 11  
#define echoPin 12


void setup() {
  Serial.begin(9600);  
  pinMode(A1,OUTPUT);
  digitalWrite(A1,HIGH);
  pinMode(A3,OUTPUT);
  digitalWrite(A3,LOW);
  randomSeed(analogRead(A0));
  int osize = 5;
  for(int k = 0; k < 5; k++){
    int p = random(osize);
    int estratto = pitch[p];
    result[i] = estratto;
    i++;
    int ti = 0;
    for(int n = 0; n < osize; n++){
      if(n != p){
        temp[ti] = pitch[n];
        ti++;
      }
    }
    osize--;
    for(int x = 0; x < 5; x++){
      if(x < osize){
        pitch[x] = temp[x];
      }else{
        pitch[x] = 0;
      }
    }
  }

  pinMode(trigPin, OUTPUT);  // pin per HCSR04
  pinMode(echoPin, INPUT);  
}


void loop() {
  digitalWrite(trigPin, LOW);   // procedura di misura del sensore a ultrasuoni
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);   // cosa viene misurato?

  distance = duration/2.0 * 0.0343;  // cosa viene calcolato?

  if((distance<100) && (distance>2)){    // per un buon grafico sul serial plotter
    kout = kalman(distance);
    //Serial.println(kout);  // stampiamolo
    //Serial.print(",");
    //Serial.println(kout);
    //Serial.println(",0,100");
    if(distance > 20){  // creiamo una soglia adeguata 
      //digitalWrite(led,HIGH);  // accendiamo il LED
    }else{  // altrimenti
      //digitalWrite(led,LOW);  // si spegne il LED
    }
  }else{
    //Serial.println("0,0,0,200");
  }
  delay(50);
  
  int pot = analogRead(A2);
  if(pot < 300){
    for(int x = 0; x < 5; x++){
      Serial.println(pitch_untouched[x]);
      tone(8, pitch_untouched[x]);
      delay(10*int(kout));
      noTone(8);
      delay(10*int(kout));
      flag = 0;
    }
  }else if(pot < 600){
    for(int x = 0; x < 5; x++){
      Serial.println(pitch_untouchedBIS[x]);
      tone(8, pitch_untouchedBIS[x]);
      delay(10*int(kout));
      noTone(8);
      delay(10*int(kout));
      flag = 0;
    }
  }else {   
    if(flag = 0){
      randomSeed(analogRead(A0));
      int osize = 5;
      for(int k = 0; k < 5; k++){
        int p = random(osize);
        int estratto = pitch[p];
        result[i] = estratto;
        i++;
        int ti = 0;
        for(int n = 0; n < osize; n++){
          if(n != p){
            temp[ti] = pitch[n];
            ti++;
          }
        }
        osize--;
        for(int x = 0; x < 5; x++){
          if(x < osize){
            pitch[x] = temp[x];
          }else{
            pitch[x] = 0;
          }
        }
      }
    }
    flag = 1;
    for(int x = 0; x < 5; x++){
      //Serial.println(result[x]);
      tone(8, result[x]);
      delay(10*int(kout));
      noTone(8);
      delay(10*int(kout));
      //Serial.println((kout));
    }
  }
}


// FUNZIONE DI CALCOLO DEL DATO FILTRATO - per loop2 e loop3
float kalman(float misura){
  float x_pred = x_est;   // posizione stimata, predetta
  float P_pred = P + Q;  // dovrebbe ridursi man mano si procede coi calcoli
  float K = P_pred / (P_pred + R);  // guadagno di Kalman, il suo valore tra 0 e 1
                                    // esprime bontà del sensore vista dal filtro
  x_est = x_pred + K * (misura - x_pred);
  P = (1 - K) * P_pred;
  return(x_est);
}






// FONTE ALIVERTI https://www.youtube.com/watch?v=jmD-qDlaOCg







