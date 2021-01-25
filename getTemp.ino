#include "Wire.h"
#define TMP102_I2C_ADDRESS 0x48

float getTemp()
{
  int temp_raw;
  float temp;

  Wire.beginTransmission(TMP102_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
  Wire.endTransmission();

  temp_raw = Wire.read() * 16 + Wire.read() / 16;
  temp = temp_raw * 0.0625;

  return temp;
}
