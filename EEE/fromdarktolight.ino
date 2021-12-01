// FROM DARK TO LIGHT - LABORATORIO LICEEEO MORETTI dicembre 2021



// Esperimento #1 fai lampeggiare il LED integrato nella scheda Arduino (cerca negli esempi il "Blink" e caricalo)

// Esperimento #2 cosa è un fotoresistore? Senza usare Arduino vedi  https://www.tinkercad.com/things/iJByX5fTmzz  

// Esperimento #3
// 1) carica lo sketch seguente
// 2) costruisci lo schema elettrico come mostrato a lavagna (oppure  https://www.tinkercad.com/things/cjDZhyVCYh9 )
// 3) nel software apri il Serial Monitor e osserva i valori letti  
// 4) avvicina la mano al fotoresistore, allontanala e osserva i valori che cambiano
// 5) apri il Serial Plotter e osserva i valori nel grafico
// 6) avvicina la mano al fotoresistore, allontanala e osserva i valori che cambiano nel grafico; simula il passaggio di un "muone"
// 7) descrivi come funziona lo schema elettrico o fai ricerca con parole chiave "legge di Ohm" e "partitore resistivo" o chiedi aiuto al profe
// 8) leggi lo sketch e descrivi come funziona o chiedi aiuto al profe; a cosa serve la soglia?


int x = 0;    // | Definisco una variabile x intera e la inizializzo a zero, essa conterrà |
              // | un numero tra 0 e 1023 in quanto Arduino converte il voltaggio          |
              // | in ingresso sul pin analogico in un numero intero a 10 bit.             |

int soglia = 0;    // | Definisco "soglia" e la inizializzo a zero, |
                   // | serve per la struttura di controllo "if".   |


void setup(){
  Serial.begin(9600);   // | Inizializzo la comunicazione seriale tra Arduino e PC:         |
                        // | uso Monitor Seriale o Plotter Seriale per visualizzare i dati. |
  
  x = analogRead(A0);    // | Qui avviene la misura del voltaggio dal pin analogico A0, |
                         // | la sua conversione e assegnazione alla variabile x.                         |
                           
  soglia = x + 100;      // | Autoimpostazione del valore di soglia. |
} 

 
void loop(){
  x = analogRead(A0);    // | La prima cosa ad ogni ciclo è misurare il voltaggio, |
                         // | convertirlo e assegnarlo alla variabile x.           |                 |

  Serial.print(x);     // | Arduino invia tramite comunicazione seriale il dato x     |
                       // | e posso visualizzarlo grazie al Monitor Seriale o al      |
                       // | Plotter Seriale che trovo alla voce "Strumenti" del menù. |

  Serial.print(" "); Serial.println(soglia);  // | Invia uno spazio vuoto e poi "soglia" |
  
  if (x > soglia) {          // | Struttura di controllo per cui se x supera "soglia"  |
    digitalWrite(13, HIGH);  // | allora il LED che si trova al pin digitale 13        |
  }else{                     // | si accende, altrimenti si spegne. "HIGH" = 1 cioè    |
    digitalWrite(13, LOW);   // | VCC cinque volt e "LOW" = 0 cioè GND o messa a terra |
  } 
}


// Fonte per partitore con fotoresistore: https://www.youtube.com/watch?v=m9kkf-XXQVU






/*

// Esperimento #4: inserire filtro a media mobile 

int x = 0;    // | Definisco una variabile x intera e la inizializzo a zero, essa conterrà |
              // | un numero tra 0 e 1023 in quanto Arduino converte il voltaggio          |
              // | in ingresso sul pin analogico in un numero intero a 10 bit.             |

int soglia = 0;    // | Definisco "soglia" e la inizializzo a zero, |
                   // | serve per la struttura di controllo "if".   |


int const fsize = 4;    // | Ogni 4 valori letti fa la media e poi stampa:                  |
int fil [fsize];        // | se aumenti il valore cala la prontezza ma è più dolce la linea |
int i=0;                // | viceversa se diminuisci il valore 
float avg = 0.0;


void setup() {
  Serial.begin(9600);   // | Inizializzo la comunicazione seriale tra Arduino e PC:         |
                        // | uso Monitor Seriale o Plotter Seriale per visualizzare i dati. |
  
  x = analogRead(A0);    // | Qui avviene la misura del voltaggio dal pin analogico A0, |
                         // | la sua conversione e assegnazione alla variabile x.                         |
                           
  soglia = x + 100;      // | Autoimpostazione del valore di soglia. |
}


void loop(){
  x = analogRead(A0);    // | La prima cosa ad ogni ciclo è misurare il voltaggio, |
                         // | convertirlo e assegnarlo alla variabile x.           |                 |
  
  fil[i] = x;
  if(i < (fsize-1)) i++;
  else i = 0;
  avg = 0;
  for(int j=0; j<fsize; j++){
    avg += (float)fil[j];
  }
  avg = avg / (float)(fsize);
  Serial.print(avg);     // | Arduino invia tramite comunicazione seriale il dato x     |
                       // | e posso visualizzarlo grazie al Monitor Seriale o al      |
                       // | Plotter Seriale che trovo alla voce "Strumenti" del menù. |

  Serial.print(" "); Serial.println(soglia);  // | Invia uno spazio vuoto e poi "soglia" |
  
  if (x > soglia) {          // | Struttura di controllo per cui se x supera "soglia"  |
    digitalWrite(13, HIGH);  // | allora il LED che si trova al pin digitale 13        |
  }else{                     // | si accende, altrimenti si spegne. "HIGH" = 1 cioè    |
    digitalWrite(13, LOW);   // | VCC cinque volt e "LOW" = 0 cioè GND o messa a terra |
  } 

}


*/


