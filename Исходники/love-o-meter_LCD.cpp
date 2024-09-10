void loop()
{  
  // reads the value of the analog sensor
  int sensorVal = analogRead(sensorPin);
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  
  // converts the measure from the ADC (analog to digital converter) to volts
  float voltage = (sensorVal/1024.0)*5.0;
  
  Serial.print(", Volts: ");
  Serial.print(voltage);
  
  // turn volts into temperature in Celsius (C)
  float temperature = (voltage - 0.5)*100;
  
  Serial.print(", degrees C: ");
  Serial.println(temperature);
  
  if(temperature < baselineTemp)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if(temperature >= baselineTemp+2 && temperature < baselineTemp+4)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if(temperature >= baselineTemp+4 && temperature < baselineTemp+6)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
  else if(temperature >= baselineTemp+6)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  
  delay(750);
  
  // enumeration of th positions in the LCD start at 0
  
  lcd.setCursor(0, 0); // set the cursor of the LCD in the first position of the first row
  lcd.print(temperature); // print the value of the variable temperature in Celsius (C)
  lcd.print(" C");
  
  lcd.setCursor(0, 1);  // set the cursor of the LCD in the first position of the second row
  lcd.print(1.8*temperature + 32); // print the value of the variable temperature in Farenheit (F)
  lcd.print(" F");
  
}