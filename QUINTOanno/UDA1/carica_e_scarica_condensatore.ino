#define analogPin      0          
#define chargePin      13         
#define dischargePin   11        
#define resistorValue  20000.0F  // in Ohm, di tipo float   

unsigned long startTime;
unsigned long elapsedTime;
float capacita;                
float nanoFarads;

void setup(){
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);  
  Serial.begin(9600);             
}

void loop(){
  digitalWrite(chargePin, HIGH);  
  startTime = millis();
  
  while(analogRead(analogPin) < 648){      // il 63,2% di 1024       
    Serial.println(analogRead(analogPin));
  }   
  
  elapsedTime= millis() - startTime;  // misuro il tau in millisecondi
  capacita = ((float)elapsedTime / resistorValue) * 1000;  // C = tau/R   calcolato in Farad   
  //Serial.print("tau = ");
  //Serial.print(elapsedTime);       
  //Serial.print(" ms    C = ");    
  //Serial.print(capacita);
  //Serial.println(" muF");
  //if (capacita > 1){
    //Serial.print((long)capacita);       
    //Serial.println(" muF");         
  //} else{
    //capacita = capacita * 1000.0;      
    //Serial.print((long)capacita);         
    //Serial.println(" nF");          
  //}
  while(analogRead(analogPin) < 1022){
    Serial.println(analogRead(analogPin));
  }
  digitalWrite(chargePin, LOW);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);          
  while(analogRead(analogPin) > 0){
    Serial.println(analogRead(analogPin));
  }
  
  pinMode(dischargePin, INPUT);            
} 


// Fonte http://www.circuitbasics.com/how-to-make-an-arduino-capacitance-meter/










/*

// CARICA E SCARICA DI UN CONDENSATORE

#define PinCarica  13   // pin digitali
#define PinScarica 11
#define PinControllo 0  // pin analogico

//variabili in uso
unsigned long t0_Carica = 0;  // istante di inizio carica
int t1_Carica = 0;            // xxx progressione del tempo di carica

int tau = 1000;  // xxx costante di tempo 

unsigned long t0_Scarica = 0;  // istante di inizio scarica
unsigned long t1_SCarica = 0;  // xxx tempo di scarica 

//parametri circuito
xxxdouble prec = 1E3;   // costante milli
double R = 1000.0;   //Resistenza di scarica in omm (valore misurato)
double C = 22E-6;  //Condensatore in Farad (22 micro-F)
double Vi = 4.78;   //Vo = tensione iniziale (condensatore carico) 5 volt
double Vf = 0.025 ; //Vs = tensione finale (condensatore scarico) 25 millivolt
                    // non porre a 0 questo valore altrimenti avremo errore 
                    // divisione per "0"

// contiene il valore numerico attribuito dal dac di arduino  ai 25 mV.                     
int sogliaADC = floor(Vf * 1024 / Vi); 


// ***********************************************************************                                  

// formula e formule inverse qui sotto ho inserito queste formule per 
//controlli in fase di prove di funzionamento queste funzionano solo se 
//nelle variabili sopra indicate sono stati inseriti i valori presenti nel 
//circuito.
//calolaC funziona se è fissata la R ( logicamente anche Vi e Vf )
//calcolaR funziona se è fissato C (logicamente anche Vi e Vf )
//Con le opportune modifiche è possibile eliminare quelle che non interessano *
//

double tempoScaricaTeorico = (R*C*log(Vi/Vf)); 
// formula per stabilire il tempo di scarica teorico che confronteremo
//con il tempo misurato, si devono impostare R e C con valore noto. 


// qui si calcola il valore del condensatore
// se C è incognito dovremo fissare R
double calcolaC(unsigned long tf){                                 
  double t = tf;
  return (t/prec) / (R * log(Vi/Vf));    
}

// qui si calcola il valore della resistenza di scarica
//  se R è incognito dovremo fissare C
double calcolaR(unsigned long tf){                                  
  double t = tf;
  return (t/prec) / (C * log(Vi/Vf));
}

// qui si calcola la Vf 
// controllo teorico con R e C conosciuti
double calcolaV(unsigned long tf){                                 
  double t = tf;
  return Vi * exp(-(t/prec)/(R*C));
}

void setup(){  
  Serial.begin(9600);
  pinMode(Control,INPUT); 
  pinMode(Carica,OUTPUT); //pronto per la carica
  pinMode(Scarica,INPUT); // (INPUT) blocca la scarica

  Serial.print("Soglia ADC: "); // valore scelto vicino allo zero.
  Serial.println(sogliaADC);
  Serial.print("Tempo di scarica teorico: ");
  Serial.println(tempoScaricaTeorico,3);
}
  
double Rcalc = 0.0;
double Ccalc = 0.0;
double Vcalc = 0.0;
double Tcalc = 0.0;

void loop(){
  //inizio carica
  pinMode(Carica, OUTPUT);  //abilita il pin alla carica
  Carica_t0 = millis();     // si registra il tempo di partenza
  digitalWrite(Carica, HIGH);  // si avvia la carica
  delay(tc);                  // tempo di carica (tc)
       
  Carica_t1 = (millis()-Carica_t0); //si conteggia il tempo di carica 
  digitalWrite(Carica, LOW);
  pinMode(Carica,INPUT);  // con questa si blocca l'eventuale scarica
                          // anche da questo pin. 
                            
  //fine carica ********************************************
           
  // inizio scarica 
  pinMode(Scarica, OUTPUT); // si abilita alla scarica
  Scarica_t0 = millis();   // si registra il tempo  inizio scarica
  digitalWrite(Scarica, LOW);  // inizia la scarica
        
  while( analogRead (Control) > sogliaADC){} 
  //  attende fino a quando il pin A0 non raggiunge il valore scelto di scarica ( Vf)            
  Scarica_t1 = ( millis () - Scarica_t0); 
  // conteggia il tempo di scarica
        
  pinMode (Scarica, INPUT);  //blocca la scarica
  
  // fine scarica *******************************************
       
  Rcalc = calcolaR(Scarica_t1);  // si fanno i calcoli
  Ccalc = calcolaC(Scarica_t1);
  Vcalc = calcolaV(Scarica_t1);
        
  // stampa i dati   lettura sul monitor
  Serial.println(" ");                
  Serial.print("Tempo Carica [secondi]: ");
  Serial.println( (Carica_t1/prec), 3);
  Serial.println(" ");                
  Serial.print("Tempo Scarica [secondi]: ");
  Serial.println(( Scarica_t1/prec), 3);
  Serial.print("Resistenza calcolata [Ohm] : ");
  Serial.println( Rcalc, 1);
  Serial.print("Capacita' calcolata [F] : ");
  Serial.println( Ccalc, 6);
  Serial.print("Tensione (finale) calcolata [Volt] : ");
  Serial.println( Vcalc, 3);

  delay (2000);  //attesa
          
  //ripristino le variabili
  Carica_t0 = 0;
  Carica_t1 = 0; 
  Scarica_t0 = 0;
  Scarica_t1 = 0;      
}
//end
  
// Fonte https://avventurarduino.blogspot.com/2013/05/arduino-partiamo-da-zero-n7-post.html
//       a cura di Sergio & Adriano Prenleloup e ispirato da Nicola Amatucci


*/
