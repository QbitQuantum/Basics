void Menux::showMenuOption(LiquidCrystal &lcd) {
	// Se envía al display el título del grupo de MenuOptions	
	lcd.clear();
	if (presentMenuCode == 1) {
		titleMenuOption = "Menu General";
	}
	lcd.setCursor(0, 0);
	lcd.print(titleMenuOption);
	// Se envía al display la MenuOption actual
	lcd.setCursor(0, 1);
	lcd.print(menuOptionList[presentOption].getOptionText());
	return;
}