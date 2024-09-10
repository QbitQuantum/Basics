void loop() {
  lcd.setCursor(0, 1);
  lcd.print(rotors[2]);
  lcd.setCursor(8, 1);
  lcd.print(rotors[1]);
  lcd.setCursor(15, 1);
  lcd.print(rotors[0]);
  delay(100);
}