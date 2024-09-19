#include <Wire.h>
#include <BMx280I2C.h>

BMx280I2C bmx280(0x76);

void setup() { 
  Serial.begin(9600);
  Wire.begin();

  bmx280.begin();
  bmx280.resetToDefaults();

  bmx280.writeOversamplingPressure(BMx280I2C::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280I2C::OSRS_T_x16);
  bmx280.writeOversamplingHumidity(BMx280I2C::OSRS_H_x16);
}

void loop() {
  bmx280.measure();

  do{
    delay(100);
  } while(!bmx280.hasValue());

  Serial.print(bmx280.getPressure());
  Serial.println(" Pa");

}

// Fonte Aliverti https://www.youtube.com/watch?v=bkV9ZIvX5w4&t=158s
