// CARICA E SCARICA DEL CONDENSATORE

//PORTA ANALOGICA A0 PER MISURA DELLA TENSIONE AI CAPI DEL CONDENSATORE 
#define analogPin 0 // Crea una costante per evitare ogni volta di scrivere lo zero del pin A0 
//PORTA DIGITALE 2 PER LA CARICA DEL CONDENSATORE 
#define chargePin 2 
int numero_misure = 150;  // 150 valore ottimo con due resistori da 4,7 kOhm? in serie
                          // 300 se uso 4 resistori e non due (infatti tau = R C) 
int deltaT = 20; // intervallo di tempo in ms tra due misure successive
                 // valore adeguato 20, relazionato a 150 misure

void setup(){ 
  pinMode(chargePin, OUTPUT); // Imposta la porta digitale in uscita 
  digitalWrite(chargePin, LOW); // Imposta la porta digitale a 0 Volt, per scaricare il condensatore 
  //Serial.println("STO ASPETTANDO 2 s PER FAR SCARICARE COMPLETAMENTE IL CONDENSATORE");
  delay(2500); // Tempo di attesa in ms per essere certi di aver scaricato completamente il condensatore 
  Serial.begin(9600); // Impostiamo la velocità di trasmissione dati a 9600 baud 
} 


void loop(){ 
  double Vout; // valori di tensione misurati  
  digitalWrite(chargePin, HIGH); // Si imposta la porta digitale a 5 Volt, per la carica del condensatore 
  for(int i=0 ; i < numero_misure ; i++){  // SONO UN SACCO DI MISURE!
    Vout = analogRead(analogPin)*5.0/1023.0; // lettura del valore di tensione e conversione da canali a Volt 
    Serial.println(Vout,4);  // CON QUATTRO CIFRE DECIMALI
    delay(deltaT); // Aspetto deltaT ms prima della prossima misura 
  } 
  digitalWrite(chargePin, LOW); // Si imposta la porta digitale a 0 Volt, per scaricare il condensatore 
  for(int i=0 ; i<numero_misure ; i++) { 
    Vout = analogRead(analogPin)*5.0/1023.0; //lettura del valore di tensione e conversione da canali a Volt 
    Serial.println(Vout,4);
    delay(deltaT); // Aspetto deltaT ms prima della prossima misura 
  } 
} 


/*

// BLINK IN VARI MODI CON LED PULSANTE POTENZIOMETRO

bool puls = 0;  // Definizione di variabile booleana
int x = 0;
unsigned long t0 = 0;
int stato = 1;  // CAMBIARE VALORE PER CASO ZERO O CASO UNO


void setup(){
  pinMode(7, INPUT_PULLUP);  
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}


void loop(){
  if(!stato){  // CASO 0 comando col pulsante
    x = 0;
    puls = digitalRead(7);    
  }
  if(stato){  // CASO 1 comando col potenziometro
    x = analogRead(A0)/50;  
    Serial.println(x);
  }
  
  digitalWrite(13, !puls); // CASO A bloccante ok sfarfallìo
  delay(x);                 
  digitalWrite(13, puls);    
  delay(x);  
  
  //if((millis() - t0) >= x){  // CASO B non bloccante 
    //t0 = millis();           // non riesco a sfarfallare
    //if(puls == 0) puls = 1;     
  //}else{
    //puls = 0;    
  //}
  //digitalWrite(13, puls);
}


*/
