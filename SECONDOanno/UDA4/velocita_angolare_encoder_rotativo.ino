// Lettura velocità angolare con Encoder Rotativo


#define encoderPinA  2
#define encoderPinB  3
volatile long pos = 0;
unsigned long dt, t1;


void setup(){
  Serial.begin(9600);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);  
}


void loop(){
  dt = millis() - t1;
  
  if(dt > 100){
    Serial.println(pos);  
    pos = 0;
    t1 = millis();
  }
}




// FUNZIONI AUSULIARIE 
void doEncoderA(){
  // look for a low-to-high on channel A
  if (digitalRead(encoderPinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == LOW) {
      pos = pos + 1;         // CW
    } else {
      pos = pos - 1;         // CCW
    }
  } else {// look for a high-to-low on channel A
    if (digitalRead(encoderPinB) == HIGH) {// check channel B to see which way encoder is turning
      pos = pos + 1;          // CW
    } else {
      pos = pos - 1;          // CCW
    }
  }  
}

void doEncoderB(){
  // look for a low-to-high on channel B
  if (digitalRead(encoderPinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoderPinA) == HIGH) {
      pos = pos + 1;         // CW
    } else {
      pos = pos - 1;         // CCW
    }
  } else { // Look for a high-to-low on channel B
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinA) == LOW) {
      pos = pos + 1;          // CW
    } else {
      pos = pos - 1;          // CCW
    }
  }
}


// Fonte https://www.youtube.com/watch?v=5_-h6o30fDI
