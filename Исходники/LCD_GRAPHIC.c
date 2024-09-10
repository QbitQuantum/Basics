//==============================================================================
void ICACHE_FLASH_ATTR tft_drawFastHLine(unsigned int x, unsigned int y, unsigned int w, unsigned long color)
{
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) return;
	if((x+w-1) >= _width)  w = _width-x;
	//SPI.beginTransaction(SPISettings(SPICLOCK, MSBFIRST, SPI_MODE0));
	LCD_setAddr(x, y, x+w-1, y);
	lcdWrite(COMMAND, RAMWR);//writecommand_cont(ILI9341_RAMWR);
	while (w-- > 0) {
		setPixel(color);//writedata16_cont(color);
	}
//	writedata16_last(color);
//	SPI.endTransaction();
}