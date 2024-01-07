// ONDA QUADRA CON "tone" CONTROLLABILE DA UN ENCODER ROTATIVO
// PIN 8 PER OUT CASSA AUDIO - PIN 3 E 4 PER IN DA ENCODER

int valore = 0;
int letturaPrecedente = HIGH;

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {
  int n = digitalRead(3);
  if((letturaPrecedente == HIGH)&&(n == LOW)){
    if(digitalRead(4)){
      valore--;
    }else{
      valore++;
    }
    Serial.println(valore);
  }
  letturaPrecedente = n;

  tone(8, valore*100 + 440);
}


// Fonte: Aliverti https://www.youtube.com/watch?v=yVd80UIR6OM
