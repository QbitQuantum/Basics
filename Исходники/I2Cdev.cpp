/** Read multiple words from a 16-bit device register.
 * @param useSPI  true : use SPI 
 * @param devAddr I2C slave device address or Slave Select pin if SPI
 * @param regAddr First register regAddr to read from
 * @param length Number of words to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Number of words read (0 indicates failure)
 */
int8_t I2Cdev::readWords(bool useSPI, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout) {
    #ifdef I2CDEV_SERIAL_DEBUG
        Serial.print(useSPI ? "SPI (0x" : "I2C (0x");
        Serial.print(devAddr, HEX);
        Serial.print(") reading ");
        Serial.print(length, DEC);
        Serial.print(" words from 0x");
        Serial.print(regAddr, HEX);
        Serial.print("...");
    #endif

    int8_t count = 0;

    Wire.beginTransmission(devAddr);
    #if ((I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO < 100) || I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_NBWIRE)
        Wire.send(regAddr);
    #elif (I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO >= 100)
        Wire.write(regAddr);
    #endif
	
	if (!useSPI) {
		Wire.endTransmission();

		Wire.beginTransmission(devAddr);
		Wire.requestFrom(devAddr, (uint8_t)(length * 2)); // length=words, this wants bytes

		uint32_t t1 = millis();
		bool msb = true; // starts with MSB, then LSB
		for (; Wire.available() && count < length && (timeout == 0 || millis() - t1 < timeout);) {
			if (msb) {
				// first byte is bits 15-8 (MSb=15)
				#if ((I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO < 100) || I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_NBWIRE)
					data[count] = Wire.receive() << 8;
				#elif (I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO >= 100)
					data[count] = Wire.read() << 8;
				#endif
			} else {
				// second byte is bits 7-0 (LSb=0)
				#if ((I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO < 100) || I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_NBWIRE)
					data[count] |= Wire.receive();
				#elif (I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO >= 100)
					data[count] |= Wire.read();
				#endif
				#ifdef I2CDEV_SERIAL_DEBUG
					Serial.print(data[count], HEX);
					if (count + 1 < length) Serial.print(" ");
				#endif
				count++;
			}
			msb = !msb;
		}
		if (timeout > 0 && millis() - t1 >= timeout && count < length) count = -1; // timeout

		Wire.endTransmission();
	} else {
		uint8_t _byteCnt = (uint8_t)(length * 2);
		byte Addr = regAddr | 0x80;	
		digitalWrite(devAddr, LOW);	
		SPI.transfer(Addr);
		bool msb = true;
		for (uint8_t cnt=0; cnt < _byteCnt; cnt++) {
			if (msb) {
				data[cnt] = SPI.transfer(0) << 8;
			}
			else
			{
				data[cnt] |= SPI.transfer(0);
				#ifdef I2CDEV_SERIAL_DEBUG
					Serial.print(data[count], HEX);
					if (count + 1 < length) Serial.print(" ");
				#endif
				count++;
			}
			msb = !msb;
		}
		digitalWrite(devAddr, HIGH);	
	}
	
    #ifdef I2CDEV_SERIAL_DEBUG
        Serial.print(". Done (");
        Serial.print(count, DEC);
        Serial.println(" read).");
    #endif
    
    return count;
}