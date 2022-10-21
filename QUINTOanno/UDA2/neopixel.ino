/*


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


*/














/*
// in sequenza

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






/*

// alba tramonto

// HUE Da 160 (blue) a 6 (giallo) https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors

#include <FastLED.h>

#define NUM_LEDS 16
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, 7, GRB>(leds, NUM_LEDS);
}

void loop() {
  
  int h = 0;
  int s = 255;
  //alba
  for (int i = 0; i < 100; i++) { 
    //Serial.println(h);
    h = map(i, 0, 100, 160, 200);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(100);
  }
  
  for (int i = 0; i < 100; i++) { 
    s = map(i, 0, 100, 255, 0);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(100);
  }
  //giorno
  delay(3000);  
  h = 64; //giallo
  s = 0;
  fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
  FastLED.show();
  //tramonto
  
  for (int i = 0; i < 100; i++) { 
    s = map(i, 0, 100, 0, 255);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(100);
  }
  for (int i = 0; i < 100; i++) { 
    //Serial.println(h);
    h = map(i, 0, 100, 64, 0);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < 100; i++) { 
    //Serial.println(h);
    h = map(i, 0, 100, 255, 160);   
    fill_solid(leds, NUM_LEDS, CHSV(h, s, 255));
    FastLED.show();
    delay(50);
  }
  //notte
  delay(5000);
  
}

// Fonte Aliverti https://www.youtube.com/watch?v=rSlzbtbnyeg
