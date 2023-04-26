bool puls = 0;  // Definizione di variabile booleana
int x = 0;

void setup(){
  pinMode(7, INPUT_PULLUP);  
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}


void loop(){
  x = analogRead(A0)/50;
  Serial.println(x);
  //puls = digitalRead(7);
  digitalWrite(13, !puls);   
  delay(x);                 
  digitalWrite(13, puls);    
  delay(x);  
}
