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


// Fonte Aliverti #207 https://www.youtube.com/watch?v=bj2cdgKhCDg
//                #208 https://www.youtube.com/watch?v=TAOMpDNvBaY

// ULTERIORI FONTI DA VEDERE #223 https://www.youtube.com/watch?v=5WCrWb4Kh74
// #663 https://www.youtube.com/watch?v=WnGSuXFJ_TM
// #345 https://www.youtube.com/watch?v=Rs-NIc3hHRg
// #364 https://www.youtube.com/watch?v=M-nnwQr4wu4
// #45 https://www.youtube.com/watch?v=nZvzIkbw_78&t=667s
// #222 https://www.youtube.com/watch?v=en9APNfGm0E
// #652 https://www.youtube.com/watch?v=SxgZTvkb_V0
// #281 https://www.youtube.com/watch?v=0c4Vjjv7h8A&t=203s poi #282
// #731 https://www.youtube.com/watch?v=QMjrIjtx3PU&t=112s
// #498 https://www.youtube.com/watch?v=JBO0sLzumk8
// #365 https://www.youtube.com/watch?v=OLoULIlc5eM
// #205 https://www.youtube.com/watch?v=XHnnL0I0lDc&t=1s
// #618 https://www.youtube.com/watch?v=1SjG1hSOHVs&t=56s
// #486 https://www.youtube.com/watch?v=Xct-JE_csJE
// #366 https://www.youtube.com/watch?v=ZgDFejvOb98
// #297 https://www.youtube.com/watch?v=PImo3s9JzM4 e poi #298
// #262 https://www.youtube.com/watch?v=I4IXILk33Rk
