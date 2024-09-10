void loop() {
  noLight=digitalRead(digitalSignal);//
  lightness=analogRead(analogSignal); // и о его количестве
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 0);
  //вывод сообщения
  Serial.print("There is ");
  
  lcd.clear();
  
  
  if (noLight) {
    Serial.println("1");
    lcd.print("1");
  }
  else { 
    Serial.println("0");
    lcd.print("0");
  }
  Serial.print("value: ");
  Serial.println(lightness);
   
  lcd.setCursor(0, 1);
   //clearLCD();
  lcd.print(lightness);
  
  delay(1000); //задержка 1 сек    
}