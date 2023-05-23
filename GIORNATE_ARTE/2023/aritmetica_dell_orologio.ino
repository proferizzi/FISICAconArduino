
/*
// ESERCIZIO 1

// Un operatore molto utile è il modulo (simbolo %) 
// che restituisce il resto della divisione tra due numeri;
// ad esempio il seguente sketch calcola e stampa questo resto.
// Prova a modificarlo per capire come funziona.

void setup() {
  Serial.begin(9600);  
}

void loop() {
  Serial.print(13);
  Serial.print(" diviso ");
  Serial.print(12);
  Serial.print(" uguale a ");
  Serial.println(13%12); 
}

// Troppo facile? Modifica rapidamente il 13, presente due volte, 
// inserendo una variabile intera.
*/




/*
// SOLUZIONE 

int i = 14;
void setup() { Serial.begin(9600); }
void loop() { Serial.print(i); Serial.print(" diviso "); Serial.print(12);
              Serial.print(" uguale a "); Serial.println(i%12); }
*/








/*
// ESERCIZIO 2

// Stampa tutti i resti possibili al crescere del dividendo, fissato il divisore

int i = 0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  Serial.print(i);
  Serial.print(" diviso ");
  Serial.print(12);
  Serial.print(" uguale a ");
  Serial.println(i%12);
  i++; 
}

// Troppi dati veloci? Metti una pausa di mezzo secondo ogni stampa
*/


/*
// SOLUZIONE
int i = 0;
void setup() { Serial.begin(9600); }

void loop() { Serial.print(i); Serial.print(" diviso "); Serial.print(12);
              Serial.print(" uguale a "); Serial.println(i%12);  i++; delay(500); 
}
*/


















// ESERCIZIO 3

// Hai notato che se il divisore è 12 hai 12 possibili resti? 
// Possiamo sfruttare questo fatto se vogliamo che Arduino mandi un comando,
// tipo "Accendi una luce e poi spegnila", ogni volta che esce uno specifico resto.
// Tipo nel seguente esempio, dove accende la luce coi multipli di 12 
// e la tiene spenta negli altri casi.

int i = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(13,OUTPUT);
}

void loop() {
  Serial.print(i);
  Serial.print(" diviso ");
  Serial.print(12);
  Serial.print(" uguale a ");
  Serial.println(i%12);
  
  if((i%12) == 0) {
    Serial.println("suona le campane, din don dan");
    digitalWrite(13,HIGH);
    delay(10);
    digitalWrite(13,LOW);
  }
  i++; 
  delay(50); 
}









/*

void setup() {
  Serial.begin(9600);
  while (!Serial);
  long int b = 1111000;
  int d = binary2decimal(b);
  Serial.println(d);
}

int binary2decimal(long int n){
  int decimal = 0, i = 0, remainder;
  while (n != 0)
  {
    remainder = n % 10;
    n /= 10;
    decimal += remainder * (1 <<i);
    ++i;
  }
  return (decimal);
}


void loop() {
}


// Fonte https://forum.arduino.cc/t/integer-to-decimal-conversion/638981


*/







