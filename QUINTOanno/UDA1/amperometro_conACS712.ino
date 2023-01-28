// Sensore ACS712T 05B portata 5 A

void setup() {
  Serial.begin(9600);
}

void loop() {
  //campiono 10 valori e calcolo la media
  int val = 0;
  for (int i = 0; i < 150; i++) {
    val += analogRead(A0);
    delay(3);
  }
  val = val / 150;

  //ricavo la tensione sul pin A0. 4.88 = 5000 mV / 1024 campioni
  //float tensione = 4.88 * val;

  float corrente = 1000.0 * (4.88 * val / 1024.0 - 2.5) / 0.185 
                   + 11581.50 ;  // offset? Vedere caso per caso
                   // Per uno di essi bisogna togliere anche 25.76

  //Serial.print("I = ");
  Serial.println(corrente);
  
  delay(50);  
}

// Fonte Aliverti https://www.youtube.com/watch?v=lmfqcHGo85E
// Fonte https://www.engineersgarage.com/acs712-current-sensor-with-arduino/

// Test 2023 gennaio: 4 resistori in parallelo da 22 Ohm e 250 mW
//                    con generatore in CC regolabile
//                    1V esce 103 mA a fronte di 109 mA di amperometro
//                    2V esce 206 mA a fronte di 212 mA di amperometro
//                    3V esce 309 mA a fronte di 322 mA di amperometro
//                    4V esce 412 mA a fronte di 435 mA di amperometro
//                    (quest'ultimo a 1,74 W escono 435 mW per ogni resistore
//                    un po' troppo, son belli caldi ma tutto sommato ok)
