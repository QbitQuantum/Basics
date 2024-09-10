//this function draws the boat dynamic on the LCD panel
void drawBoat(MI0283QT9 lcd, int x, int y) {
	uint8_t width = 15;
	uint8_t length = 25;
	//draw square
	lcd.drawRect(x, y, width, length, RGB(0, 0, 0));
	//draws line around the square
	lcd.fillRect(x + 1, y + 1, width - 2, length - 2, RGB(156, 102, 31));
	//can place the mast further backward on the boat
	int8_t mastPosition = -2;
	// draws mast
	lcd.fillCircle(x + width / 2, y + length / 2 + mastPosition, (width + length) / 12, RGB(82, 82, 82));
	//draws sail
	lcd.fillTriangle(x, y + length / 2 - (width + length) / 12 + mastPosition, x + width - 1, y + length / 2 - (width + length) / 12 + mastPosition, x + width / 2, y - 2 + length / 2 - (width + length) / 12 + mastPosition, RGB(255, 255, 255));
}