void trigger() {
  lcd.clear();         // clears the screen and buffer
  lcd.setCursor(3,0);
  lcd.print("Time is up");
  
  lcd.setCursor(1, 1); // set timer position on lcd for end.
  lcd.print("END OF SHOWER");

  turnDownServo();
  delay(1000);
  lcd.display();
}