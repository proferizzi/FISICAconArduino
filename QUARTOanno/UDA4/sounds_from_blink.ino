// Buzzer in parallel with LED on pin 13

int t = 0;
int n = 0;
int x = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  delayMicroseconds(t);              
  digitalWrite(LED_BUILTIN, LOW);    
  delayMicroseconds(t + n);
  
  if(t < x){
    t = t + n;
  }else{
    t = t - x;
    x = x + 1; Serial.println(x);
    if(x > 100){
      x = 0;
      t = 0;
      n = 0;
    }
  }
  n = 1;//n = n + 1;
}
