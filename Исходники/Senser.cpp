void setTemperature() {
	float newTemperature = dht.readTemperature(false);
	lcd.clear();
	lcd.print("Temperature");
	lcd.setCursor(0, 1);
	lcd.print(newTemperature);
	lcd.print(" C");
}