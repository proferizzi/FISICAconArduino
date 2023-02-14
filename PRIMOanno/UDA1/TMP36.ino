int val_Adc = 0;
float temp = 0;
const int Pin_TMP36 = A6; //variabile lettura sensore

void setup(){
  // inizializzazione porta seriale  
  Serial.begin(9600); 
}

void loop(){
  //Legge il valore dalla porta analogica
  val_Adc = analogRead(Pin_TMP36);
  // Converte il valore in temperatura
  float temp = ((val_Adc /1024.0) * 3.3 - .5) * 100;
  Serial.print(temp);  
  Serial.println(" °C");
  //Pausa di mezzo secondo tra le misure
  delay( 500 );
}

// Fonte Adrirobot http://win.adrirobot.it/sensori/tmp36/scheda_arduino_tmp36.htm#Listato_del_programma
