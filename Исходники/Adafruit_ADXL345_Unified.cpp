bool Adafruit_ADXL345_Unified::begin() {
  Wire.begin();

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