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
                         // | la sua conversione e assegnazione alla variabile x.                       
                           
  soglia = x + 100;      // | Autoimpostazione del valore di soglia. |
  
  pinMode(LED_BUILTIN, OUTPUT);  // | Per attivare LED integrato nella scheda. |
} 

 
void loop(){
  x = analogRead(A0);    // | La prima cosa ad ogni ciclo è misurare il voltaggio, |
                         // | convertirlo e assegnarlo alla variabile x.           |          

  Serial.print(x);     // | Arduino invia tramite comunicazione seriale il dato x     |
                       // | e posso visualizzarlo grazie al Monitor Seriale o al      |
                       // | Plotter Seriale che trovo alla voce "Strumenti" del menù. |

  Serial.print(" "); Serial.println(soglia);  // | Invia uno spazio vuoto e poi "soglia" |
  
  if (x > soglia) {                  // | Struttura di controllo per cui se x supera "soglia"  |
    digitalWrite(LED_BUILTIN, HIGH); // | allora il LED che si trova al pin digitale 13        |
  }else{                             // | si accende, altrimenti si spegne. "HIGH" = 1 cioè    |
    digitalWrite(LED_BUILTIN, LOW);  // | VCC cinque volt e "LOW" = 0 cioè GND o messa a terra |
  } 

  delay(10); // | Istruzione bloccante, se i dati sono veloci aumentare (unità in millisecondi). |
}


// Fonte per partitore con fotoresistore: https://www.youtube.com/watch?v=m9kkf-XXQVU






/*

// Esperimento #4: come il precedente ma con aggiunta di filtro a media mobile 

int soglia = 0;   
int const fsize = 10;    
int fil[fsize];                       
float avg = 0.0;


void setup() {
  Serial.begin(9600); 
  avg = analogRead(A0);                
  soglia = avg + 100;    
  pinMode(LED_BUILTIN, OUTPUT); 
}


void loop(){
  avg = 0;
  for(int j=0; j<fsize; j++){
    fil[j] = analogRead(A0);
    avg += (float)fil[j];
  }
  avg = avg / (float)(fsize); // errore da modificare ma ora non ho tempo
  Serial.print(avg);    
  Serial.print(" "); Serial.println(soglia);  
  if (avg > soglia) {          
    digitalWrite(LED_BUILTIN, HIGH);  
  }else{                     
    digitalWrite(LED_BUILTIN, LOW); 
  } 

}

*/









/*

// Esperimento #5: come il precedente ma con aggiunta di stima durata soprasoglia

int soglia = 0;   
int const fsize = 10;    
int fil[fsize];                       
float avg = 0.0;

int conteggio = 0;
#define ON HIGH
#define OFF LOW
long t0 = 0;
long t = 0;


void setup() {
  Serial.begin(9600); 
  avg = analogRead(A0);                
  soglia = avg + 100;   
  Serial.print("Soglia = "); Serial.println(soglia); 
  pinMode(LED_BUILTIN, OUTPUT); 

  conteggio = OFF;
}


void loop(){
  avg = 0;
  for(int j=0; j<fsize; j++){
    fil[j] = analogRead(A0);
    avg += (float)fil[j];
  }
  avg = avg / (float)(fsize);
  //Serial.print(avg);    
  //Serial.print(" "); Serial.println(soglia);  
  if ((avg > soglia) && (conteggio == OFF)) { 
    conteggio = ON;
    t0 = millis();
    Serial.print("Inizio");         
    digitalWrite(LED_BUILTIN, HIGH);  
  }
  if ((avg < soglia) && (conteggio == ON)){
    conteggio = OFF;
    t = millis() - t0;
    Serial.print(" - Fine - ");         
    Serial.print("tempo = "); Serial.print(t); Serial.println(" millisecondi");                     
    digitalWrite(LED_BUILTIN, LOW); 
  } 

}

// Fonte https://www.youtube.com/watch?v=EDYA7WZKhn8

*/








/*

// Esperimento #6: come il precedente ma con aggiunta del conteggio - da controllare

int soglia = 0;   
int const fsize = 10;    
int fil[fsize];                       
float avg = 0.0;

int conteggio = 0;
#define ON HIGH
#define OFF LOW
long t0 = 0;
long t = 0;

bool passaggio = false;
bool prev_passaggio = false;
bool count = false;
long istante = 0;
#define FINESTRA 2000
int click = 0;


void setup() {
  Serial.begin(9600); 
  avg = analogRead(A0);                
  soglia = avg + 100;   
  Serial.print("Soglia = "); Serial.println(soglia); 
  pinMode(LED_BUILTIN, OUTPUT); 

  conteggio = OFF;
}


void loop(){
  avg = 0;
  for(int j=0; j<fsize; j++){
    fil[j] = analogRead(A0);
    avg += (float)fil[j];
  }
  avg = avg / (float)(fsize);
  //Serial.print(avg);    
  //Serial.print(" "); Serial.println(soglia);  
  if ((avg > soglia) && (conteggio == OFF)) { 
    conteggio = ON;
    t0 = millis();
    Serial.print("Inizio");         
    digitalWrite(LED_BUILTIN, HIGH);  
    passaggio = true;
    if(!prev_passaggio && passaggio){
      Serial.println("salita");
      prev_passaggio = passaggio;
      if(!count){
        count = true;
        istante = millis();
        Serial.println("start");
        click = 0;
      }
    }
  }
  if ((avg < soglia) && (conteggio == ON)){
    conteggio = OFF;
    t = millis() - t0;
    Serial.print(" - Fine - ");         
    Serial.print("tempo = "); Serial.print(t); Serial.println(" millisecondi");                     
    digitalWrite(LED_BUILTIN, LOW);
    if(prev_passaggio && !passaggio){
      Serial.println("discesa");
      prev_passaggio = passaggio;
      click++;
    }
  } 
  if(count && ( (millis()-istante) > FINESTRA) ){
    count = false;
    Serial.println("fine");  
    Serial.print("click = "); Serial.println(click); Serial.println("-----------");
  }
}

// Fonte https://www.youtube.com/watch?v=EDYA7WZKhn8
// Fonte https://www.youtube.com/watch?v=Utl1bhzv0dY&t=499s

*/

