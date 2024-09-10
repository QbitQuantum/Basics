void loop()                     // run over and over again
{
     
  ultoa( encoder0Pos, msg1, 10);
  //ultoa ( second, msg1, 10);
  digitalWrite(12, 0); //delay(1);
  lcd.print( msg1);
  digitalWrite(12, 1);
 
  delay(100);



/*  if (oldSecond != second) {
    Serial.print(second);
    Serial.print(". ->");
    Serial.print(millis() - starttime);
    Serial.println(".");

    delay(100);

    oldSecond = second;
  }
*/

}