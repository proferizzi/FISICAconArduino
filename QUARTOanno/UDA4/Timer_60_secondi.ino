// Timer di 60 secondi per lavare denti coi bimbi
// Con Shield Didattica per Arduino UNO

#include <TimerOne.h>
#include <MultiFuncShield.h>

int counter = 0 ;


void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);
  //MFS.write("Hi");delay(2000);MFS.write("123");delay(2000);
  //MFS.write(-203);delay(2000);MFS.write(3.141, 2);delay(2000); 

  pinMode(3, OUTPUT);  
  counter = 0;
}


void loop() {
  if(counter < 60){
    counter++;
    MFS.write(counter);
  }else{
    tone(3, 400, 2000);
    counter = 0;
  }
  delay(1000);
}

// Fonte Aliverti https://www.youtube.com/watch?v=HxjootD0ZOs
// https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
