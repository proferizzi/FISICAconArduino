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
