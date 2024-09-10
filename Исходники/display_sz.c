void loop()
{
lcd.setCursor(3,1);
lcd.write(1); // desenha o coração
delay(500);
lcd.setCursor(3,1);
lcd.print(" Hello World! "); // Após 0.5s apaga o coração, assim ele
delay(500); // ficará piscando
}