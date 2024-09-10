void PIDControl::displayTemp(double currTemp, double setTempPoint)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cur Temp: ");
    lcd.print(currTemp);
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Set Temp: ");
    lcd.print(setTempPoint);
    lcd.print(" C");
    delay(2000);
}