// MACCHINA A STATI - PROTOTIPO COMMENTATO PER PRINCIPIANTI

int stato = 0;  // Variabile che definisce in ogni istante lo stato in cui
                // la macchina si trova.

unsigned long t0, dt = 0;  // Variabili utili per fare un blink.
int statoled = LOW;


void setup(){   // Queste istruzioni verranno eseguite solo una volta.
  
  //pinMode(3, OUTPUT);
  Serial.begin(9600);
}


void loop(){   
  switch(stato){   // Controlla valore dello stato e fa saltare la macchina
                   // nel loop numerato da tale stato.
    case 0: 
      loop0();
    break;

    case 1: 
      loop1();
    break;
    
    case 2: 
      loop2();
    break;
  }
  delay(1000);
}

void loop0(){
  // STATO
  Serial.println(0);
  digitalWrite(3, LOW);
  delay(500);
  analogWrite(3, 50);

  // TRANSIZIONE
  if(digitaleRead)stato = 1;
}
  
void loop1(){
  // STATO
  Serial.println(1);
  digitalWrite(3, HIGH);

  // TRANSIZIONE
  stato = 2;
}


void loop2(){
  // STATO
  Serial.println(2);
  dt = millis() - t0;
  if(dt >= 500){
    statoled = !statoled;
    digitalWrite(3, statoled);
    t0=millis(); 
  }
  
  // TRANSIZIONE
  stato = 0;
}


// Fonte Aliverti https://www.youtube.com/watch?v=bj2cdgKhCDg
//                https://www.youtube.com/watch?v=TAOMpDNvBaY
