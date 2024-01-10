// ********* Progetto EEE - gennaio 2024 - Liceo - a cura di Rizzinelli


// *** Sensori magnetici analogici e pulsante





// (#1) Attività: attivare il Plotter Seriale,
//                tenere schiacciato il pulsante con una mano
//                e fare scorrere un magnete lungo direzione e verso dei sensori


int PinPulsante = 8;  // scelta del pin per il pulsante


void setup() {
  Serial.begin(9600);  // Attiviamo la seriale fissandola a 9600 baud
  pinMode(PinPulsante,INPUT);  // impostazione a INPUT del pin per il pulsante
  digitalWrite(PinPulsante,LOW);  // impostanze a LOW del pin per il pulsante
}

void loop() {
  int x0 = analogRead(A0);  // misuro il valore analogico del sensore 
  int x1 = analogRead(A1);  // misuro il valore analogico del sensore 
  int x2 = analogRead(A2);  // misuro il valore analogico del sensore 
  int x3 = analogRead(A3);  // misuro il valore analogico del sensore 
  int x4 = analogRead(A4);  // misuro il valore analogico del sensore 
  int x5 = analogRead(A5);  // misuro il valore analogico del sensore 

  if(digitalRead(PinPulsante) == 1){  // se schiaccio il pulsante
    Serial.print(x0);Serial.print(" ");  // stampo il valore analogico
    Serial.print(x1);Serial.print(" ");  // stampo il valore analogico
    Serial.print(x2);Serial.print(" ");  // stampo il valore analogico
    Serial.print(x3);Serial.print(" ");  // stampo il valore analogico
    Serial.print(x4);Serial.print(" ");  // stampo il valore analogico
    Serial.println(x5);  // stampo il valore analogico e vado a capo
  }
  delay(10);  // attendo 10 millisecondi 
}







/*

// (#2) Attività: attivare il Monitor Seriale
//                fare scorrere un magnete più volte davanti al primo sensore
//                leggere il conteggio

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

*/




























// Sensore a ultrasuoni

int led = 13;
int trig = 6;
int echo = 7;
float duration;
float distance;
//int buzz = 11;


void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  pinMode(trig,OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  pinMode(echo,INPUT);
  delay(1000);
}


void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = duration/58.2;
  if((distance<60) && (distance>0)){   
    Serial.println(distance);
    delay(10);
  }
  //tone(buzz,1/duration);
}
// Fonte: da "5volt solution" su youtube


*/








