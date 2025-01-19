// SECONDO INCONTRO, RIPRENDIAMO L'ESPERIMENTO 5 (PER CHI NON ERA RIUSCITO A FARLO BENE) 
// E POI PROSEGUIAMO. BUON LAVORO!





/* ESPERIMENTO 5. CONTEGGIAMO I FRONTI DI DISCESA - ANALOGIA CON ARDUSIPM - "EEE.ino" 
 * Riprendiamo l'esperimento 3 del partitore resistivo 
 * con fotoresistore come sensore analogico
 * 
 * Circuito:
 * Colleghiamo un estremo del fotoresistore con un estremo del resistore
 * e da lì partiamo con un filo da collegare ad un ingresso analogico di Arduino;
 * L'altro estremo del fotoresistore andrà a GND e l'altro estremo del resistore a +5V
 */

int x = 0;
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


void setup() {
  Serial.begin(9600);   // Attiviamo la seriale fissandola a 9600 baud

  x = analogRead(A0); // misuro il valore analogico  
  delay(500);  // aspetto mezzo secondo                  
  x += analogRead(A0); // misuro di nuovo e sommo le prime due misure  
  delay(500);  // aspetto mezzo secondo                  
  x += analogRead(A0); // misuro di nuovo e sommo le prime tre misure    

  soglia = x/3 + 10;  // calcolo la media e sommo un valore adeguato
  Serial.print("soglia = "); Serial.println(soglia);  // stampo la soglia 
}


void loop(){
  x = analogRead(A0);  // misuro il valore analogico del sensore 
  
  //Serial.print(x); Serial.print(" ");  // stampo il valore analogico
  //Serial.println(soglia);  // stampo il valore della soglia e vado a capo
  delay(10);  // attendo 10 millisecondi 

    //Serial.println(stato);
  if(x > soglia){   // lo confronto con la soglia
    stato = true;
  }else{
    stato = false;
  }
  
  if(!prev_stato && stato){        
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
// Fonte per sviluppo futuro https://www.youtube.com/watch?v=EDYA7WZKhn8 
//       (quanto tempo l'hai premuto)

/* osservazione: Ma se arrivano due "muoni" quasi contemporaneamente?
 * ipotesi: potremmo stimare il tempo per cui si sta sopra soglia e...
 * esperimento: provare a realizzare la situazione indesiderata, seppur rara
 * riflessioni: e per rilevare solo i "muoni" che passano lungo certe direzioni? */






// ESPERIMENTO 6: INTRODUZIONE DI UN FILTRO DI KALMAN DA USARE
//                QUANDO I DATI RACCOLTI SONO RUMOROSI (PICCOLE E RAPIDE VARIAZIONI INDESIDERATE)

???



  
// ESPERIMENTO 7: MISURA DELLA DURATA DI PASSAGGIO SOPRASOGLIA E MODIFICA DEL CONTEGGIO
//                DEL PASSAGGIO DI FINTI MUONI PER CASI RARI (COPPIE O TERNE DI MUONI VICINI)

???




// ESPERIMENTO 8: REALIZZAZIONE DELL'ESPERIMENTO 5 MA CON SENSORE A ULTRASUONI HCSR04

???


// ESPERIMENTO 9: REALIZZAZIONE DELL'ESPERIMENTO 6 MA CON SENSORE A ULTRASUONI HCSR04

???


// ESPERIMENTO 10: REALIZZAZIONE DELL'ESPERIMENTO 7 MA CON SENSORE A ULTRASUONI HCSR04

???



  
// ALTRI ESPERIMENTI: REALIZZAZIONE PRECEDENTI ESPERIMENTI MA CON SENSORI DIFFERENTI







  
