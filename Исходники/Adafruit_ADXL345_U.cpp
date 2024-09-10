bool ADXL345::begin() {
  
  if (_i2c)
    Wire.begin();
  else {
    pinMode(_cs, OUTPUT);
    pinMode(_clk, OUTPUT);
    digitalWrite(_clk, HIGH);
    pinMode(_do, OUTPUT);
    pinMode(_di, INPUT);
  }

  /* Check connection */
  uint8_t deviceid = getDeviceID();
  if (deviceid != 0xE5)
  {
    /* No ADXL345 detected ... return false */
    Serial.println(deviceid, HEX);
    return false;
  }
  
  // Enable measurements
  writeRegister(ADXL345_REG_POWER_CTL, 0x08);  
    
  return true;
}