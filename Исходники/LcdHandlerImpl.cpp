void LcdHandler::printHomeScreen()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Temp: ");
	lcd.print((int)*temp);
	lcd.print(" C");
	lcd.setCursor(0, 1);
	lcd.print("Hum: ");
	lcd.print((int)*hum);
	lcd.print(" %");
}