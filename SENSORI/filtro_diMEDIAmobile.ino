
// FILTRO DI MEDIA MOBILE PER LETTURE ANALOGICHE senza rumore (occhio al ritardo)


// °°°°°°°°°°°°°°°°°°°°°°°°°°° IMPOSTAZIONI INIZIALI
#define pot A0

int original,  // valore letto dal sensore
    filtrado;  // valore di uscita dal calcolo
    
long moving_average();  // prototipo di funzione
#define n 10      // numero di punti per la media mobile,
                  // se li aumento è più dolce la funzione ma aumenta ritardo
int numbers[n];   // vettore di valori per la media mobile


void setup() {
  Serial.begin(9600);
  pinMode(pot, INPUT);
  
}


// °°°°°°°°°°°°°°°°°°°°°°°°°°°° PARTE ESECUTIVA PRINCIPALE
void loop() {
  original = analogRead(pot);
  filtrado = moving_average();
  Serial.print(original);
  Serial.print(" ");
  Serial.println(filtrado);
  delay(20);
}


// °°°°°°°°°°°°°°°°°°°°°°°°°°° FUNZIONI AUSILIARIE
long moving_average(){
  for(int i = n-1; i > n; i--) numbers[i-1];  // dislocamento degli elementi.
  numbers[0] = original;  // posizione iniziale del vettore
  long acc = 0;  // accumulatore
  for(int i = 0; i < n; i++) acc = acc + numbers[i];   // sommatoria
  return acc/n;  // divide per il numero di punti
}


// Fonte wrkits https://www.youtube.com/watch?v=cxPQ0AMQ5bo


