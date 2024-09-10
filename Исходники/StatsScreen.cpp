void StatsScreen::drawScreen( LiquidCrystal &_lcd ) {
	_lcd.clear();

	_lcd.setCursor(0, 0);
	_lcd.print("Taken: ");
	_lcd.print(taken);

	_lcd.setCursor(0, 1);
	_lcd.print("Next: ");
}