void lcd_printMoisture(Moisture *moisture) {
	lcd.setCursor(4, 0);
	char pch[4];
	sprintf(pch, "%02d", moisture->proc);
	lcd.print(pch);

	lcd.setCursor(13, 0);
	sprintf(pch, "%02d", moisture->maxProc);
	lcd.print(pch);
}