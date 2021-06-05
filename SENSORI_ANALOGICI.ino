/*

// ANALOGREADRESOLUTION


void setup() {
  // open a serial connection
  Serial.begin(9600);
}


void loop() {
  // read the input on A0 at default resolution (10 bits)
  // and send it out the serial connection
  analogReadResolution(10);
  Serial.print("ADC 10-bit (default) : ");
  Serial.print(analogRead(A0));

  // change the resolution to 12 bits and read A0
  analogReadResolution(12);
  Serial.print(", 12-bit : ");
  Serial.print(analogRead(A0));

  // change the resolution to 16 bits and read A0
  analogReadResolution(16);
  Serial.print(", 16-bit : ");
  Serial.print(analogRead(A0));

  // change the resolution to 8 bits and read A0
  analogReadResolution(8);
  Serial.print(", 8-bit : ");
  Serial.println(analogRead(A0));

  // a little delay to not hog Serial Monitor
  delay(100);
}


// Fonte https://www.arduino.cc/reference/en/language/functions/zero-due-mkr-family/analogreadresolution/


*/















/*

// ESPERIMENTO INTRODUTTIVO ALL'USO DEL FOTORESISTORE
//
// La resistenza del resistore usato nel partitore può essere da 10 kOhm, ma anche meno.

// Utilizzo del pin per la lettura dei valori del fotoresistore.
int foto = 0;  
// Pin per l'utilizzo del LED interno
#define LED 13             
// Variable usata per memorizzare il valore letto dal fotoresistore
int x = 0;          

void setup() {
 Serial.begin(9600);         
 pinMode(LED,OUTPUT);    
}

void loop() {
  // Legge il valore dal fotoresistore
  x = analogRead(foto);       
  digitalWrite(LED , HIGH);                  // Accende il LED interno
  delay(x);                            // Interrompe il programma per un numero di millisecondi pari a quanto letto dal fotoresistore
  Serial.print("Lettura analogica = ");
  Serial.println(x);                 // Stampo nella seriale il valore letto dal fotoresistore (si noti che qui ho usato la println)
  digitalWrite(LED , LOW);               // Spegne il LED interno   
  delay(x);                        // Interrompe il programma per un numero di millisecondi pari a quanto letto dal fotoresistore
}

// Fonte: http://www.mcmajan.com/mcmajanwpr/blog/2012/08/18/arduino-e-gli-ingressi-analogici/



*/

















/*  MODIFICATO PER TESTARE DECODIFICA UART SU OSCILLOSCOPIO 
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
/*
int sensorValue = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while(sensorValue <= 8){
    //Serial.println(0);
    Serial.println(sensorValue);
    delay(5);        // delay in between reads for stability
    sensorValue = sensorValue + 1;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // print out the value you read:
  //Serial.println(sensorValue);
  //delay(10);        // delay in between reads for stability
  //sensorValue = sensorValue + 1;
  //if(sensorValue == 101){
  //  delay(1000);
  //  sensorValue = 0;
  //}
}


*/
