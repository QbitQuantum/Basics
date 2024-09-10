/** \brief Initialisation of MicroOLED Library.

    Setup IO pins for SPI port then send initialisation commands to the SSD1306 controller inside the OLED.
*/
void MicroOLED::begin()
{
	// default 5x7 font
	setFontType(0);
	setColor(WHITE);
	setDrawMode(NORM);
	setCursor(0,0);

	pinMode(dcPin, OUTPUT);
	pinMode(rstPin, OUTPUT);

	// Set up the selected interface:
	if (interface == MODE_SPI)
		spiSetup();
	else if (interface == MODE_I2C)
		i2cSetup();
	else if (interface == MODE_PARALLEL)
		parallelSetup();

	// Display reset routine
	pinMode(rstPin, OUTPUT);	// Set RST pin as OUTPUT
	digitalWrite(rstPin, HIGH);	// Initially set RST HIGH
	delay(5);	// VDD (3.3V) goes high at start, lets just chill for 5 ms
	digitalWrite(rstPin, LOW);	// Bring RST low, reset the display
	delay(10);	// wait 10ms
	digitalWrite(rstPin, HIGH);	// Set RST HIGH, bring out of reset

	// Display Init sequence for 64x48 OLED module
	command(DISPLAYOFF);			// 0xAE

	command(SETDISPLAYCLOCKDIV);	// 0xD5
	command(0x80);					// the suggested ratio 0x80

	command(SETMULTIPLEX);			// 0xA8
	command(0x2F);

	command(SETDISPLAYOFFSET);		// 0xD3
	command(0x0);					// no offset

	command(SETSTARTLINE | 0x0);	// line #0

	command(CHARGEPUMP);			// enable charge pump
	command(0x14);

	command(NORMALDISPLAY);			// 0xA6
	command(DISPLAYALLONRESUME);	// 0xA4

	command(SEGREMAP | 0x1);
	command(COMSCANDEC);

	command(SETCOMPINS);			// 0xDA
	command(0x12);

	command(SETCONTRAST);			// 0x81
	command(0x8F);

	command(SETPRECHARGE);			// 0xd9
	command(0xF1);

	command(SETVCOMDESELECT);			// 0xDB
	command(0x40);

	command(DISPLAYON);				//--turn on oled panel
	clear(ALL);						// Erase hardware memory inside the OLED controller to avoid random data in memory.
}