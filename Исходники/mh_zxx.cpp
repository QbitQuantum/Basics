/*****************************************************************************************************************************
*
*   Read specified metric's value of the Winsen MH-Zxx CO2 sensor via UART, put it to output buffer on success. 
*
*   Returns: 
*     - RESULT_IS_BUFFERED on success
*     - DEVICE_ERROR_TIMEOUT if device stop talking
*
*****************************************************************************************************************************/
int8_t getMHZxxMetricUART(const uint8_t _rxPin, const uint8_t _txPin, uint8_t* _dst, int32_t* _value, const uint8_t _wantsNumber) {
  uint8_t len, rc = DEVICE_ERROR_TIMEOUT;

  SoftwareSerial swSerial(_rxPin, _txPin);

  // Send query only if sensor heated
  if (millis() > MH_ZXX_PREHEAT_TIMEOUT) {
  
     swSerial.begin(MH_ZXX_UART_SPEED);

     _dst[MH_ZXX_STARTING_BYTE] = 0xFF;                           // Starting byte
     _dst[MH_ZXX_SENSOR_NUMBER] = 0x01;                           // Sensor No.
     _dst[MH_ZXX_CMD] = MH_ZXX_CMD_GAS_CONCENTRATION;             // Command
     _dst[3] = _dst[4] = _dst[5] = _dst[6] = _dst[7] = 0x00;      // Stub bytes
     _dst[MH_ZXX_CRC] = 0x79;                                     // Check value

     // Flush all device's transmitted data to avoid get excess data in recieve buffer
     //serialRXFlush(&swSerial, !UART_SLOW_MODE);
     flushStreamRXBuffer(&swSerial, MH_ZXX_DEFAULT_READ_TIMEOUT, !UART_SLOW_MODE);


     // The serial stream can get out of sync. The response starts with 0xff, try to resync : https://github.com/jehy/arduino-esp8266-mh-z19-serial/blob/master/arduino-esp8266-mhz-19-serial.ino
     //  Send command to MH-Zxx
     serialSend(&swSerial, _dst, MH_ZXX_PACKET_SIZE, !UART_SLOW_MODE);

     
     //  Recieve from MH-Zxx
     //  It actually do not use '\r', '\n', '\0' to terminate string
     len = serialRecive(&swSerial, _dst, MH_ZXX_PACKET_SIZE, MH_ZXX_DEFAULT_READ_TIMEOUT, !UART_STOP_ON_CHAR, '\r', !UART_SLOW_MODE);
     
     // Connection timeout occurs
     if (len < MH_ZXX_PACKET_SIZE) { rc = DEVICE_ERROR_TIMEOUT; goto finish; }
     
     // Wrong answer. buffer[0] must contain 0xFF
     if (0xFF != _dst[MH_ZXX_STARTING_BYTE]) { rc = DEVICE_ERROR_WRONG_ANSWER; goto finish; }
     
     // Bad CRC
     // CRC calculate for bytes #1..#9 (byte #0 excluded)
     if (_dst[MH_ZXX_CRC] != crcMHZxx(_dst)) { rc = DEVICE_ERROR_CHECKSUM; goto finish; }
     
     *_value = 256 * _dst[MH_ZXX_GAS_CONCENTRATION_HIGH_BYTE];
     *_value += _dst[MH_ZXX_GAS_CONCENTRATION_LOW_BYTE];
  } else {  // if (millis() > MH_ZXX_PREHEAT_TIMEOUT)
     // Return 'good concentracion' while sensor heated
     *_value = MH_ZXX_PREHEAT_GAS_CONCENTRATION;
  } // if (millis() > MH_ZXX_PREHEAT_TIMEOUT)

  if (!_wantsNumber) {
     ultoa(*_value, (char*) _dst, 10);
  }

  rc = RESULT_IS_BUFFERED;

  finish:
  gatherSystemMetrics(); // Measure memory consumption
  swSerial.~SoftwareSerial(); 
  return rc;

}