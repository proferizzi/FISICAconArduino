// ESPERIMENTO PER MISURARE CON OSCILLOSCOPIO LA FREQUENZA DI UN EVENTO PERIODICO, 
// MISURARNE ANCHE IL PERIODO E LAVORARE CON LA FORMULA " f = 1 /T "

// Materiale: scheda Arduino con cavo USB legato a PC e software IDE; 
//            OSCILLOSCOPIO; cavetti di collegamento; calcolatrice

// Procedura DIDATTICA (FRONTALE basata su problem solving con tecnica del F.A.R.E.): 
// 1) FOCALIZZA - abbiamo un segnale elettrico che cambia nel tempo 
//                (grandezze fisiche "intervallo di tempo" e "voltaggio" o "differenza di potenziale"
// 3) ANALIZZA - il segnale è digitale ed è generato da scheda Arduino 
// 4) RISOLVI - usiamo l'oscilloscopio per la misura frequenza e periodo 
// 4) ESEGUI - eseguiamo frontalmente l'esperimento 

// APPLICAZIONE in meccanica: la velocità di un motorino in corrente continua cambia in base alla percentuale calcolata 
//                            vedere link qui https://t.me/esperimentopiubello/24 però ci vuole login a Telegram

// mappatura dell'hardware
#define pwmOut (1<<PD3)  // pin digitale 3             

// prototipo di funzioni
void setDuty_pin03(float valueD);
void setFreq(char option);

// variabile globale
char duc = 80;  // percentuale di duty cicle

// impostanzioni iniziali
void setup(){
  DDRD |= pwmOut;    
  PORTD &= ~pwmOut;   
  TCCR2A = 0xA3; 
  setFreq(2);  // numeri da 1 a 7
}

// parte esecutiva principale
void loop(){
  setDuty_pin03(duc);
}


// sviluppo delle funzioni
void setDuty_pin03(float valueD){
  int duty;
  valueD = valueD / 100;
  duty = (valueD * 256) - 1;
  OCR2B = duty;
}

void setFreq(char option){ // 1 ---> 62,5 kHz *** 2 ---> 7,81 kHz *** 3 ---> 1,95 kHz
                           // 4 ---> 976,56 Hz *** 5 ---> 488,28 Hz *** 6 ---> 244,14 Hz *** 7 ---> 61,03 Hz
  TCCR2B = option;
}


// Fonte WRKits https://www.youtube.com/watch?v=SOc1KOUvrgk

