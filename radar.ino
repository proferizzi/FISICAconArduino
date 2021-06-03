// GIORNATA DELL'ARTE GIUGNO 2021 - LICEO 


// Inseguitore RADAR ACUSTICO
// Sono previsti due servomotori: il primo (servo_scan) fa ruotare il sensore HC-SR04  
// e il secondo (servo_track) si posizione all'angolo in cui c'è la distanza minima
// Tutti i Serial.print() si possono eliminare. Servono solo per monitoraggio



// °°°°°°°°°°°°°°°°°°° IMPOSTAZIONI INIZIALI

#include <Servo.h>

#define echoPin 11 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 10 //attach pin D3 Arduino to pin Trig of HC-SR04
#define DIM_ARRAY 17 // da 10  a 170 °
#define STEP 10

int distance,distance_1, dist_min; // variable for the distance measurement
int array_dist[DIM_ARRAY] ; 

Servo servo_scan, servo_track;
int i,k;
int ang_min;
int n;


void setup() {
  servo_scan.attach(7);
  servo_track.attach(13);
  pinMode(trigPin, OUTPUT); // Set trigPin as  OUTPUT
  pinMode(echoPin, INPUT); // Sets echoPin aa INPUT
  Serial.begin(9600); // // Serial @ 9600 baudrate 
  for(k=0;k<DIM_ARRAY;k++){
    i=10+k*STEP;
    servo_scan.write(i);
    delay(50); 
    distance = misura_distanza();
    array_dist[k] = distance; // riempio l'array                       
  }
  dist_min=400;                
  for(k=0;k<DIM_ARRAY;k++){
    if(array_dist[k]<dist_min){
      dist_min=array_dist[k];
      i=10+k*STEP; 
    }
   //Serial.print(array_dist[k]);
   //Serial.print("-");                                        
  }
  //Serial.println("");
  //Serial.print("dist_min_iniziale:");
  //Serial.print(dist_min); 
  //Serial.print(" at:");
  //Serial.println(i);
  //Serial.println("--------------"); 
  servo_track.write(i); // aggiorno il tracciamento
  delay(60);                  
}




// °°°°°°°°°°°°°°°°°°°°°°° PARTE ESECUTIVA PRINCIPALE DEL PROGRAMMA

void loop() {
  distance=misura_distanza(); // fittizia  
  //Serial.println("--------------");
  //Serial.print("dist_inizio_loop:");
  //Serial.println(dist_min);  
  //Serial.println("--------------");
  for(k=0;k<DIM_ARRAY;k++){        
    i=10+k*STEP;
    servo_scan.write(i);
    delay(60); 
    distance = misura_distanza();
    //Serial.print("dist:");
    //Serial.println(distance);
    if(distance>0 && distance<(dist_min-2) ){ // aggiorno ma con cautela
      dist_min=distance;
      ang_min=i; 
      servo_track.write(i); // aggiorno il  tracciamento
      delay(60);
      //Serial.println("-------------");
      //Serial.print("d_min:");
      //Serial.print(dist_min);
      //Serial.print(" at:");
      //Serial.println(i);
      //Serial.println("-------------");
    }
    array_dist[k] = distance; // riempio l'array  
    if(k==0) array_dist[k]=400;   // per evitare un errore del sensore      
  }
  dist_min=400;  // perchè fisso il minimo al valore massimo ?     
  array_dist[0]=400;  // per evitare un errore del sensore                
  for(k=0;k<DIM_ARRAY;k++){
    if(array_dist[k]<(dist_min-2)){
      dist_min=array_dist[k];
      i=10+k*STEP; 
    }
  }
  servo_track.write(i);
  //Serial.print("Fine ciclo: ");
  //Serial.print(dist_min);
  //Serial.print(" at:");
  //Serial.println(i);
  //Serial.println("......");      
}



// °°°°°°°°°°°°°°°°°°°°°°°°°° FUNZIONI AUSILIARIE

int misura_distanza(void){
  long durata;
  int dist;
  digitalWrite(trigPin, LOW);// azzera trigPin
  delayMicroseconds(5);   // tieno a zero per 5 microsec
  digitalWrite(trigPin, HIGH);// Alza trigPin per 15 microseconds
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);// Abbassa trigPin
  durata = pulseIn(echoPin, HIGH); // durata dell'impulso su echoPin
  dist= durata/58;  // DA DOVE ESCE QUESTO 58 ? (velocità del suono ... andata e ritorno...)
  if(dist>400) dist=400; // max 4m di default per non avere misure assurde
  return dist;   
}




// Fonte: Un ringraziamento a Leonardo (Bibliolab Concesio)




































// °°°°°°°°°°°°°°°°°°°°°° ALTRO CODICE NON USATO, MA SIMILE


/*

// RADAR CON SERVO, SENSORE A ULTRASUONI, CICALINO E LED  

#define ECHO 8      // Pin per ricezione del segnale al sensore a ultrasuoni
#define TRIG 9      // Pin per trasmissione del segnale dal sensore a ultrasuoni
#define LED 13      // Pin per LED
#define CIC 4       // Pin per cicalino
#define SERVO 3     // Pin del servomotore
#include <Servo.h>  // Libreria per gestire il servomotore
Servo myservo;      // Creazione oggetto "myservo" per controllare il servomotore


void setup() {
  Serial.begin(9600);       // Inizializzo la seriale
  pinMode(TRIG,OUTPUT);     // Inizializzo il pin di trasmissione come uscita 
  digitalWrite(TRIG,LOW);   // Lo pongo a zero Volt
  delayMicroseconds(2);     // Attendo 2 microsecondi
  pinMode(ECHO,INPUT);      // Inizializzo il pin di ricezione come ingresso
  delayMicroseconds(2);     // Attendo 2 microsecondi
  pinMode(CIC,OUTPUT);      // Inizializzo il pin del cicalino come uscita
  digitalWrite(CIC,LOW);    // Lo pongo a zero Volt
  pinMode(LED,OUTPUT);      // Inizializzo il pin del LED come uscita
  digitalWrite(LED,LOW);    // Lo pongo a zero Volt
  myservo.attach(SERVO);    // Collego l'oggetto "myservo" al pin del servomotore 
}


void loop() {
  for (int i = 45; i < 135; i = i + 5) {
    myservo.write(i);
    int d = readDistanza(); 
    Serial.println(d);  
    if((d <= 200) && (d >= 2)){
      int j = d*20;
      digitalWrite(LED,HIGH);
      tone(CIC,100);  
      delay(j);
      digitalWrite(LED,LOW);
      tone(CIC,1000);
      delay(j);
    }
    while(d < 5){
      int r = random(100,1000);
      tone(CIC,r);
      d = readDistanza(); 
    }
  }
}


int readDistanza() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);   
  float d = pulseIn(Echo, HIGH);  
  d = d / 58.0;       
  return (int)d;
}  



// Fonti:  https://www.youtube.com/watch?v=QEpUTYRSftY
//         https://www.youtube.com/watch?v=xbvMzptK8H8


*/
