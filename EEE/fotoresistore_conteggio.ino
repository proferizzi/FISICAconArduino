// Esperimento con fotoresistore - conteggio

int x = 0;       // variabile dove salviamo la media dei dati
int soglia = 0;  // variabile misurata solo all'inizio                

bool stato = false;       // stato e prev_stato falsi: sotto soglia
bool prev_stato = false;  // stato e prev_stato veri: sopra soglia
                          // fronte salita se stato vero ma prev_stato falso
                          // fronte discesa se stato falso ma prev_stato vero
                          
bool count = false;  // variabile che ci dice se stiamo conteggiando o no    
long istante = 0;    // variabile che misura l'istante a inizio conteggio,
                     // che inizierà ad ogni fronte di salita 

#define FINESTRA 10000  // durata fissa di conteggio, in millisecondi
int click = 0;          // variabile che aumenta ad ogni fronte di discesa


int const fsize = 3;  // numero costante di misure prima di fare la media
int fil[fsize];       // array che conterrà le misure
int i = 0;            // indice per segnarci quale misura si sta facendo
float avg = 0.0;      // variabile utile per calcolare la media mobile


void setup() {
  Serial.begin(9600);   // Attiviamo la seriale fissandola a 9600 baud
  
  x = analogRead(A0); //Serial.print(x); Serial.print(" ");  
  delay(500);                  
  x += analogRead(A0); //Serial.print(x/2); Serial.print(" ");  
  delay(500);
  x += analogRead(A0); //Serial.println(x/3);   

  soglia = x/3 + 10;   // la soglia è frutto di una media di tre misure,
                       // poi sommiamo un valore consono per la luce ambientale
  Serial.print("soglia = "); Serial.println(soglia); 
    
  pinMode(LED_BUILTIN, OUTPUT);  // LED al pin 13, se usiamo Arduino UNO
}


void loop(){
  
  fil[i] = analogRead(A0);   // facciamo la misura, qui e ora
  delay(50);                 // aspettiamo 50 millisecondi 
  if(i < (fsize-1)) i++;     // aumentiamo di uno il contatore della misura
  else i = 0;                // se siamo a fine misura risettiamo a zero

  avg = 0;   // risettiamo a zero
  for(int j = 0; j< fsize; j++){
    avg += (float)fil[j];   // sommiamo tutti i valori di array
  }
  avg = avg / (float)(fsize);  // divido la somma attuale per dimensione array 
                        // NB si potrebbe migliorare questa parte, 
                        // troppi i calcoli di avg, 
                        // infatti solo alla fine ho la media adeguata...
                        
  if(i == (fsize-1)){  // solo alla fine 
    x = avg;  // valuto x
    //Serial.print(x); Serial.print(" "); Serial.println(soglia); 
    //Serial.println(stato);
    if(x > soglia){   // lo confronto con la soglia
      stato = true;
    }else{
      stato = false;
    }
  }
  
  if(!prev_stato && stato) {        
    digitalWrite(LED_BUILTIN, HIGH);    
    Serial.println("salita");
    if(!count){
      count = true;
      istante = millis();
      Serial.println("start");
      click = 0;
    }
  }
 
  if (prev_stato && !stato){                   
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("discesa");
    click++;
  }

  prev_stato = stato;

  // DI SEGUITO: la differenza (millis() - istante) è intervallo di tempo,
  // se supera la finestra finisce il conteggio, altrimenti riparte col loop         
  if(count && ( (millis()-istante) > FINESTRA) ){   
    count = false;             
    Serial.println("fine");  
    Serial.print("Numero di rilevazioni = "); Serial.println(click); Serial.println("-------");
  }
  
}


// Da Paolo Aliverti:
// Fonte https://www.youtube.com/watch?v=GOGpCERzdns 
//       (partitore resistivo e lettura dati analogici)
// Fonte https://www.youtube.com/watch?v=Utl1bhzv0dY 
//       (fronti salita e discesa)
// Fonte https://www.youtube.com/watch?v=cnQSCPUgiA4 
//       (per filtro a media mobile)
// Fonte per sviluppo futuro https://www.youtube.com/watch?v=EDYA7WZKhn8 
//       (quanto tempo l'hai premuto)
