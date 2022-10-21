// NeoPixel Ring 
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

//pin a cui sono connessi 
#define PIN 6
//numero pixel
#define PIX      16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIX, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); 

  pixels.setPixelColor(0, pixels.Color(0,150,0));
  pixels.show();
  delay(1000); 

  //spengo tutto
}

void loop() {
  //BLINK
  for (int i = 0; i < PIX; i++) {
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();
  }
  delay(1000);
  for (int i = 0; i < PIX; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
  delay(1000);
}

// Fonte Aliverti https://www.youtube.com/watch?v=V_t4gCYLs9Y&t=49s

















/*

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define EL 16
#define PIN 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(EL, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();

  for (int i = 0; i < EL; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));  
  }
  pixels.show();
  delay(1000);
}

int c = 0;

void loop() {
  for (int i = 0; i < EL; i++) {
    int r = (c % EL);
    if (i == r) {
      pixels.setPixelColor(i, pixels.Color(0,120,120));  
    } else {
      pixels.setPixelColor(i, pixels.Color(0,0,0));    
    }    
  }
  pixels.show();
  delay(1000);
  c++;
}


// Fonte Aliverti https://www.youtube.com/watch?v=txRKpAqDEws


*/
