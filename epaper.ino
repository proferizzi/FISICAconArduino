#include <GxEPD.h>
#include <GxGDEH0213B72/GxGDEH0213B72.h>  // 2.13" b/w new panel
#include <Fonts/FreeMonoBold9pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI, 10, 9, 8); // CS - DC - RST
GxEPD_Class display(io, 8, 7);  // RST - BUSY

int soglia = 0;
int x = 0;


void setup() {
  Serial.begin(115200);
  
  display.init(115200); 
  display.eraseDisplay();
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  
  soglia = analogRead(A0) + 100 ;
  Serial.print("Soglia = "); Serial.println(soglia);
}


void loop() { 
  x = analogRead(A0);
  Serial.println(x);
  
  if (x > soglia) {
    display.drawPaged(letture);  
  }
}


void letture() {
  //display.setCursor(0,15);
  //display.print(F("per riga"));
  int i = 15; 
  while (i < 151) {
    display.setCursor(0, i);
    x = analogRead(A0);
    display.print(x);
    delay(30);
    display.setCursor(70, i);
    display.print(x);
    delay(30);
    i = i + 15; 
  }
}














// fromDARKtoLIGHT con display e-paper

#include <GxEPD.h>                        // | Librerie per gestire display                |
#include <GxGDEH0213B72/GxGDEH0213B72.h>  // | dimensioni schermo 2.13" bianco/nero nuovo. |
#include <Fonts/FreeMonoBold9pt7b.h>      
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include GxEPD_BitmapExamples

GxIO_Class io(SPI, 10, 9, 8);       // CS - DC - RST
GxEPD_Class display(io, 8, 7);      // RST - BUSY

int soglia = 0;

uint32_t x = 0;


void setup() {
  Serial.begin(115200);
  
  display.init(115200);     // enable diagnostic output on Serial
  display.eraseDisplay();
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  
  soglia = analogRead(A0) + 100 ;
  //Serial.print("Soglia = "); Serial.println(soglia);
}


void loop() { 
  x = analogRead(A0);
  //Serial.println(x);
  
  if (x > soglia) {
    showPartialUpdatePaged();
  }
  //delay(500);
}


void showPartialUpdatePaged() {
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setRotation(0);
  
  uint16_t i = 20; 
  
  while (i < 201) {
    uint16_t box_x = 0;  
    uint16_t box_y = i;
    uint16_t box_w = 100;  
    uint16_t box_h = 19;
    uint16_t cursor_y = box_y + box_h - 10;
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    display.setCursor(box_x, cursor_y);
    x = analogRead(A0);  //Serial.println(x);
    display.drawPagedToWindow(showValueBoxCallback, box_x, box_y, box_w, box_h, x);
    //display.setCursor(box_x + 50, cursor_y);
    x = analogRead(A0);  //Serial.println(x);
    display.drawPagedToWindow(showValueBoxCallback, box_x, box_y, box_w, box_h, x);
    //delay(30);
    //display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    //display.setCursor(box_x, cursor_y);
    //display.print(x);
    
    
    i = i + 20; 
  }
  display.powerDown(); 
}


//void showBlackBoxCallback(uint32_t v) {
  //uint16_t box_x = 10;  uint16_t box_y = 15;
  //uint16_t box_w = 70;  uint16_t box_h = 20;
  //display.fillRect(box_x, box_y, box_w, box_h, v);
//}


void showValueBoxCallback(uint32_t x) {
  display.print(x);
  //delay(30);
}
