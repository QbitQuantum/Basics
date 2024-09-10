// Prints curve choices on the LCD screen
void CurveInput::printCurveChoices()
{
	initLCD(&col, &row);
	lcd.print("A: Default Curve");
	lcd.setCursor(0, 1);
	lcd.print("B: User Curve");
	lcd.setCursor(0, 0);
}