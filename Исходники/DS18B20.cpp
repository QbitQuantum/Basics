/**
 * Get a float representing the temperature from the DS18B20.
 *
 * @param ds OneWire instance configured for communication with the DS18B20.
 * @return The average temperature in Fahrenheit of all devices, or 0 if fail.
 */
float DS18B20::getTemperature(OneWire ds) {
    byte data[12];  // data buffer
    byte addr[8];   // address buffer
    byte deviceCount = 0;   // number of devices taken care of
    float avgTemp = 0.0;    // the average temperature to be returned

    // Search for a new device on the bus. If 1, a new device is available. If 0,
    // the bus may be in error, nothing may be connected, or all devices have been
    // read. This should allow for multiple sensors on the same bus (must remove
    // else block). The address of the next device will be stored in addr.
    ds.reset_search();
    while (ds.search(addr)) {
        // Count this device
        deviceCount++;

        // Verify the CRC of the address
        if ( OneWire::crc8( addr, 7) != addr[7]) {
            //Serial.println("CRC is not valid!");
            return 0.0;
        }

        // Verify the device is recognized by looking at the device ID in the
        // first byte of the address (=0x28).
        if (addr[0] != DS18B20_CODE) {
            //Serial.println("Device not recognized!");
            return 0.0;
        }

        // Begin a temperature conversion
        ds.reset();
        ds.select(addr);
        ds.write(CMD_CONVERT_TEMP);   // 0x44 = start conversion

        // Hard delay to get the most up-to-date reading. This gives the most time accurate reading
        // but locks the processor up from doing anything else. The existing method where we read
        // the *previous* reading every 1 second is suitable and increases utilization.
        //delay(1000);

        // Request to read the temperature sensor's scratchpad for the converted temperature
        ds.reset();
        ds.select(addr);
        ds.write(CMD_READ_SPAD);   // 0xBE = read scratchpad

        // Read data (9 bytes total in register, only the first two bytes contain the temperature)
        for (int i = 0; i < 9; i++) {
            data[i] = ds.read();
        }

        // Convert read data (16 bit signed integer) to a float
        int16_t temp_raw = (data[1] << 8) | data[0];
        float temp_celsius = (float)temp_raw/16.0;

        // Convert temperature to Fahrenheit and add it to our running average
        float temp_fahrenheit = temp_celsius * 1.8 + 32.0;
        avgTemp += temp_fahrenheit;
    }

    // If we didn't catch any devices, return 0.0
    if (deviceCount == 0)
        return 0.0;

    // Compute and return the average
    avgTemp /= deviceCount;
    return avgTemp;
}