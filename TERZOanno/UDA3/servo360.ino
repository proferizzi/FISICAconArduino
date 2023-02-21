#include <Servo.h>

Servo servo;


void setup() {
  servo.attach(6); 
}


void loop() {
  for(int i = 90; i < 180; i++){   // cambiare a piacere -90 0 ecc.
    servo.write(i);
    delay(50);    
  }
  delay(5000);
  for(int i = 180; i > 90; i--){   // cambiare a piacere -90 0 ecc.
    servo.write(i);
    delay(50);    
  }
  delay(5000);
}


// Fonte Aliverti https://www.youtube.com/watch?v=LtnKzVlk_P4
