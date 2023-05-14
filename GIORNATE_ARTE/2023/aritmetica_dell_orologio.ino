int i = 0;

void setup() {
 Serial.begin(9600);
 pinMode(13,OUTPUT);
}

void loop() {
 if((i%12) == 0) {
  Serial.println("suona le campane, din don dan");
  digitalWrite(13,HIGH);
 }
 Serial.println(i);
 i++; 
 delay(10);
 digitalWrite(13,LOW);
}
