void loop() {
   lcd.clear();
  lcd.print("http://powerpacks." );
  lcd.setCursor( 0,1 );
  lcd.print("ArcolaEnergy.com");
  lcd.setCursor( 0,3 );

 lcd.print(RTC.get(DS1307_HR,true)); //read the hour and also update all the values by pushing in true
  lcd.print(":");
  lcd.print(RTC.get(DS1307_MIN,false));//read minutes without update (false)
  lcd.print(":");
  lcd.print(RTC.get(DS1307_SEC,false));//read seconds
  lcd.print("      ");                 // some space for a more happy life
  lcd.print(RTC.get(DS1307_DATE,false));//read date
  lcd.print("/");
  lcd.print(RTC.get(DS1307_MTH,false));//read month
  lcd.print("/");
  lcd.print(RTC.get(DS1307_YR,false)); //read year 
 

digitalWrite( STATUS_OK, HIGH);
digitalWrite( STATUS_BAD, LOW );
  delay( 100 );
  digitalWrite( STATUS_OK, LOW);
digitalWrite( STATUS_BAD, HIGH );
delay( 100 );
}