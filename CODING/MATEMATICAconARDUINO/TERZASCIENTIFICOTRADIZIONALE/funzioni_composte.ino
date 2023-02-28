
// *** BLINK DI UN LED TRAMITE FUNZIONE COMPOSTA *** //
// Utile per primi passi con classi terze liceo scientifico tradizionale



// *** IMPOSTAZIONI INIZIALI

// VARIABILE INTERA
int x = 0;
// VARIABILE BOOLEANA CIOE' ASSUME SOLO VALORE VERO O FALSO
bool z = false;


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

  // APPLICO LA COMPOSIZIONE DI FUNZIONI
  f(g(x));

  // ASPETTO UN SECONDO
  delay(1000);

  // RICAMBIO IL VALORE ALLA x
  x = 0;

  // RIAPPLICO LA COMPOSIZIONE DI FUNZIONI
  f(g(x));

  // ATTENDO UN ALTRO SECONDO
  delay(1000);
}
// *** FINE DEL CODICE CHE SI RIPETE ALL'INFINITO




// *** FUNZIONI AUSILIARIE PRESENTI IN TUTTO IL CODICE PRECEDENTE


// COME OPERA LA FUNZIONE "INTERNA" z = g(x)
bool g(int x){
  if(x == 0){
    return false;
  }
  else if(x == 1){
    return true;
  }
}


// COME OPERA LA FUNZIONE "ESTERNA" y = f(z) 
void f(bool z){
  if(z == true){
    accendi_il_LED();
    Serial.println("ACCESO");
  }
  else if(z == false){
    spegni_il_LED();
    Serial.println("SPENTO");
  }
}






// CODICE PER ACCENDERE E SPEGNERE IL LED
void accendi_il_LED(){
  digitalWrite(13,HIGH);
}
void spegni_il_LED(){
  digitalWrite(13,LOW);
}



// Fonte Aliverti lezioni di base + cercare "funzioni e Arduino"
