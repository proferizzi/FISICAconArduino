
// *** BLINK DI UN LED TRAMITE FUNZIONE COMPOSTA *** //
// Utile per primi passi con classi terze liceo scientifico tradizionale



// *** IMPOSTAZIONI INIZIALI

// VARIABILI INTERE
int x = 0;  // CONTROIMMAGINE DELLA g
int y = 0;  // IMMAGINE DELLA f
// VARIABILE BOOLEANA CIOE' ASSUME SOLO VALORE VERO O FALSO
bool z = false;  // IMMAGINE DELLA g USATA COME CONTROIMMAGINE DELLA f


void setup() {
  // INIZIALIZZA LA SERIALE PER LEGGERE I DATI SUL MONITOR
  Serial.begin(9600);
  // IMPOSTA IL PIN DIGITALE COME UNA USCITA
  pinMode(13,OUTPUT);
}



// *** QUESTO CODICE SEGUENTE SI RIPETERÀ ALL'INFINITO

void loop() {
  // CAMBIO VALORE ALLA x
  x = 1;

  // APPLICO LA COMPOSIZIONE DI FUNZIONI:
  // PRENDO LA CONTROIMMAGINE x CALCOLO LA SUA IMMAGINE TRAMITE LA g
  // POI TALE IMMAGINE DIVIENE CONTROIMMAGINE PER LA f, LA CUI IMMAGINE È y
  y = f(g(x));

  // CONTROLLO SE t VALE 1 E SE È COSÌ "ACCENDO IL LED"
  if(y == 1){
    accendi_il_LED();
  }

  // ASPETTO UN SECONDO, BLOCCANDO TUTTO
  delay(1000);

  // RICAMBIO IL VALORE ALLA x
  x = 0;

  // RIAPPLICO LA COMPOSIZIONE DI FUNZIONI
  y = f(g(x));

  // CONTROLLO SE t VALE 0 E SE È COSÌ "SPENGO IL LED"
  if(y == 0){
    spegni_il_LED();
  }

  // ATTENDO UN ALTRO SECONDO, BLOCCANDO TUTTO 
  delay(1000);
}
// *** FINE DEL CODICE CHE SI RIPETE ALL'INFINITO




// *** FUNZIONI AUSILIARIE PRESENTI IN TUTTO IL CODICE PRECEDENTE


// COME OPERA LA FUNZIONE "INTERNA" z = g(x)
bool g(int x){
  // STRUTTURA DI CONTROLLO if
  // SE È VERO CIÒ CHE È PRESENTE TRA LE PARENTESI TONDE
  // ALLORA ESEGUE CIÒ CHE È PRESENTE TRA LE GRAFFE,
  // ALTRIMENTI SE È FALSO SALTA A DOPO LA CHIUSURA DELLA GRAFFA
  if(x == 0){
    // L'USCITA DELLA FUNZIONE SARÀ DATA DAL VALORE "false"
    return false;
  }
  else if(x == 1){
    return true;
  }
}


// COME OPERA LA FUNZIONE "ESTERNA" y = f(z) 
int f(bool z){
  if(z == true){
    return 1;
  }
  else if(z == false){
    return 0;
  }
}






// CODICE PER ACCENDERE E SPEGNERE IL LED
void accendi_il_LED(){
  digitalWrite(13,HIGH);
  Serial.println("ACCESO");
}
void spegni_il_LED(){
  digitalWrite(13,LOW);
  Serial.println("SPENTO");
}



// Fonte Aliverti lezioni di base + cercare "funzioni e Arduino"
