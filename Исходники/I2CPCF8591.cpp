uint8_t I2CPCF8591::initPort(){
	// Set Inputs on PCF8591 from defined control byte
	// Initialize  analog output
	// I2C write operations to PCF8591
	Wire.beginTransmission(_address);
	Wire.write(_controlByte); //Chip configuration.
	//If analog output is enabled set to 0 analog output port.
	uint8_t analogOutput_Enebled = _controlByte & B01000000;
	if( analogOutput_Enebled)
		Wire.write(_analogOutput);// Send 0 default value on init
	Wire.endTransmission();

	//Initialize Analog inputs;
	readPort();

	return 0;
}