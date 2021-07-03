// NB se si usa un BUZZER con resistore "102" è 1 kOhm e con transistor forse è un pnp S8550 / 2ty


// hcsr04, buzzer e led

int ledPin = 13;
int trig = 9;
int echo = 8;
int cicalino = 4;
float durata;
float distanza;

void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  pinMode(echo,INPUT);
  delay(2000);
  pinMode(cicalino,OUTPUT);
  //Serial.println("Distanza:");
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
}

void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  durata = pulseIn(echo,HIGH);
  distanza = durata/58.0;
  //Serial.println(distanza);
  //Serial.print("cm");
  //Serial.print("\n");
  int i = 20;
  if(distanza<=200 && distanza>=2){
    i=distanza*i;
    digitalWrite(ledPin,HIGH);
    tone(cicalino,100);  
    delay(i);
    digitalWrite(ledPin,LOW);
    tone(cicalino,1000);
    delay(i);
  }
  delay(60);
}
// Fonte: da "5volt solution" su youtube











/*
// sensore a ultrasuoni con buzzer attivo

int triggerPort = 7;
int echoPort = 8;
int cicalino = 9;
unsigned long time;
unsigned long lampeggio_time;
unsigned long pausa_time;
void setup() {
pinMode( triggerPort, OUTPUT );
pinMode( echoPort, INPUT );
pinMode( cicalino, OUTPUT );
Serial.begin( 9600 );
Serial.println( "Sensore ultrasuoni: ");
}
void loop() {
//porta bassa l'uscita del trigger
digitalWrite( triggerPort, LOW );
//invia un impulso di 10microsec su trigger
digitalWrite( triggerPort, HIGH );
delayMicroseconds( 10 );
digitalWrite( triggerPort, LOW );
long duration = pulseIn( echoPort, HIGH );
long r = 0.034 * duration / 2;
Serial.print( "durata: " );
Serial.print( duration );
Serial.print( " , " );
Serial.print( "distanza: " );
if( duration > 38000 ) Serial.println( "fuori portata");
else { Serial.print( r ); Serial.println( "cm" );}
if( r > 3 && r <= 200){
delay(r*10);
digitalWrite(cicalino, HIGH);
delay(r*10); }
if( r <= 3){
digitalWrite(cicalino, HIGH);
delay(1000);}
digitalWrite(cicalino, LOW);
delay(10);
}
// fonte https://www.progettiarduino.com/arduino-sensore-parcheggio-con-hc-sr04.html
// occhio al circuito con transistor https://startingelectronics.org/pinout/geekcreit-active-buzzer-module-pinout/
*/




















/*

// Modulo cicalino con resistenza "102" da 1kOhm e un transistor 2ty - uso di funzione tone()
// scrittura di frequenze in Hz uso anche della funzione random()

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

int pin = 6;

void setup() {
  pinMode(pin, OUTPUT);  

  tone(pin, a, 500);
  delay(500);
  tone(pin, b, 500);
  delay(500);
  tone(pin, c, 500);
  delay(500);
  tone(pin, d, 500);
  delay(500);
}

void loop() {
  int nota = random(200, 1000);
  tone(pin, nota, 100);
  delay(100);
}


// Fonte corso Aliverti





  
/*


// Modulo cicalino con resistenza "102" da 1kOhm e un transistor 2ty - uso di analogWrite su pin PWM

int buzzerPin = 3; //Define buzzerPin


void setup() {
  pinMode(buzzerPin, OUTPUT); //Set buzzerPin as output
  beep(50); //Beep
  beep(50); //Beep
  delay(1000); //Add a little delay

}


void loop() {
  beep(50); //Beep every 500 milliseconds
  delay(500);
}


void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 20); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
  
} 
  
  
// Fonte https://www.instructables.com/id/Arduino-YL-44-Buzzer-module/
// Fonte transistor http://images.lightstrade.com/201510/201510091717500372.jpg


*/





























/*


// Utilizzo del buzzer passivo con funzione tone
      
const int pinBuzzer = 4;  
// pin a cui è collegato il buzzer  
      
int frequenzaquenza;  
// variabile in cui memorizzare il valore della frequenza  
    

void setup(){  
  pinMode(pinBuzzer,OUTPUT); // inizializzazione del pin a cui è collegato il buzzer  
}  


void loop() {  
  for(int i = 200; i <= 1000; i++)   // loop di frequenze da 200 a 1000 hz  
  {  
    tone(pinBuzzer,i);   // viene emesso dal buzzer un suono a frequenza i  
    delay(5);            // attesa di 5 millisecondi (in modo da percepire il suono emesso)     
  }  
  delay(3000);           // attesa di 3 secondi. La frequenza più alta sarà emessa per 4 secondi  
  for(int i = 1000; i >= 200; i--)  // loop di frequenze da 100 a 200 hz  
  {  
    tone(pinBuzzer,i);   // viene emesso dal buzzer un suono a frequenza i  
    delay(5);            // attesa di 5 millisecondi (in modo da percepire il suono emesso)     
  }  
}  

// Fonte Prof. Michele Maffucci - 08.01.15
    
*/    
    
    
    
  
  
  
  
  
  
  








/*

    // Utilizzo di un Sensor Tracking e di un buzzer passivo  
      
    const int pinSensore = 7;  
    // pin a cui è collegato il sensore  
      
    const int pinLed = 13;  
    // pin a cui è collegato il led  
      
    //const int pinBuzzer = 4;  
    // pin a cui è collegato il buzzer  
      
    //const int frequenza = 440;  
    // frequenza emessa dal buzzer (440 Hz)  
      
    void setup()  
    {  
      // inizializzazione del pin sensore, led e buzzer  
      pinMode(pinSensore, INPUT);  
      //pinMode(pinLed, OUTPUT); 
      Serial.begin(9600);
      //pinMode(pinBuzzer,OUTPUT);  
    }  
      
    void loop()  
    {  
      millis();
      //Serial.println(digitalRead(pinSensore)); // print the data from the sensor
      //delay(500);
      
      // conserviamo nella variabile var lo stato del sensore  
      int val = digitalRead(pinSensore);  
      // verifichiamo se viene letto "NERO"  
      // se vero accendiamo il led  
      if(val == LOW)  
      {  
        Serial.println(millis());
        //digitalWrite(pinLed, HIGH);   // accende il led  
        //tone(pinBuzzer, frequenza);   // viene emesso dal buzzer un suono a frequenza fissata  
        delay(5);                     // attesa di 5 millisecondi (in modo da percepire il suono emesso)     
      }  
      // altrimenti spegniamo il led  
      //else  
      //{  
        //digitalWrite(pinLed, LOW);   // spegne il led 
        //noTone(pinBuzzer);           // non viene emesso nessun suono dal buzzer  
      //}  
    }  
    
    */



















/*


    // Utilizzo del pinBuzzer attivo  
    const int pinBuzzer = 11; 
      
    void setup()  
    {  
      pinMode(pinBuzzer,OUTPUT);  
    }  
      
    void loop()  
    {  
      int a,b;  
      
      // la condizione del while è sempre vera "1" quini il ciclo sarà infinito  
      // all'interno di ogni ciclo sul pin a cui è collegato il buzzer viene inviata  
      // un segnale alto per x ms ed un segnale basso per y ms il periodo totale dell'onda  
      // sarà T = x + y e quindi la frequenza sarà f = 1/T  
      
      while(1)  
      {  
        // emissione di un segnale a frequenza di 500 hz  
        for(a=0;a<80;a++)  
        {  
          digitalWrite(pinBuzzer,HIGH);  
          delay(1);                      // attesa di 1 ms  
          digitalWrite(pinBuzzer,LOW);  
          delay(1);                      // attesa di 1 ms  
        }  
        // emissione di una segnale a frequenza di 250 hz  
        for(b=0;b<100;b++)  
        {  
          digitalWrite(pinBuzzer,HIGH);  
          delay(2);                  // attesa di 2 ms  
          digitalWrite(pinBuzzer,LOW);  
          delay(2);                  // attesa di 2 ms  
        }  
      }  
    }   
    
    */

