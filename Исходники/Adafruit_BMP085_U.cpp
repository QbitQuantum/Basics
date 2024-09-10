static void read16(byte reg, uint16_t *value)
{
  Wire1.beginTransmission((uint8_t)BMP085_ADDRESS);
  #if ARDUINO >= 100
    Wire1.write((uint8_t)reg);
  #else
    Wire1.send(reg);
  #endif
  Wire1.endTransmission();
  Wire1.requestFrom((uint8_t)BMP085_ADDRESS, (byte)2);
  #if ARDUINO >= 100
    *value = (Wire1.read() << 8) | Wire1.read();
  #else
    *value = (Wire1.receive() << 8) | Wire1.receive();
  #endif
  Wire1.endTransmission();
}