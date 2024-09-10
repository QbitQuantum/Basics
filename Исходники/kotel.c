void loop(){
  if(analogRead(0)<800)err=0;
  while(err!=1 && digitalRead(pinErr)!=HIGH){
    digitalWrite(pinR1, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("R1 ON");
    delay(5000);
    digitalWrite(pinR2, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("R2 ON");
    delay(5000);
    //if(analogRead(pinTemp)<=0 && analogRead(pinTemp)>=100) digitalWrite(pinR3, LOW);
    //else err=1;
    if(digitalRead(pinErr)==HIGH) {
      err=1;
      lcd.clear();
      lcd.print("Err R3");
      digitalWrite(pinR1, HIGH);
      digitalWrite(pinR2, HIGH);
      digitalWrite(pinR3, HIGH);
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Error!");
  digitalWrite(pinR1, HIGH);
  digitalWrite(pinR2, HIGH);
  digitalWrite(pinR3, HIGH);

}