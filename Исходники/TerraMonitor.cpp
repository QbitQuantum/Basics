void loop()
{
    /* Runs the non RT controller */
    controller.run();

    // Serial.print(" Temperature milieu: ");
    // Serial.print(humidTempSensor.getTemp());
    // Serial.print(" Humidite milieu: ");
    // Serial.print(humidTempSensor.getHumidity());
    // Serial.print(" Temperature Bas: ");
    // Serial.println(lowSensor.getAverageValue());
    // Serial.println();

    // lcd.cursor();
    // lcd.clear();
    lcd.setCursor(7,0);
    digitalClockDisplay(now());
    lcd.setCursor(0,1);
    lcd.print("Up : ");
    lcd.print(highSensor.getTemp());
    lcd.print((char)223);
    lcd.print('C');
    // lcd.setCursor(0,2);
    // lcd.print("Mid : ");
    // lcd.print(humidTempSensor.getTemp());
    // lcd.print((char)223);
    // lcd.print('C');
    lcd.setCursor(0,2);
    lcd.print("Down : ");
    lcd.print(lowSensor.getTemp());
    lcd.print((char)223);
    lcd.print('C');

    // fogRelay.on();
    // lightRelay.on();
    // // heatRelay.on();
    // delay(5000);
    // fogRelay.off();
    // lightRelay.off();
    // // heatRelay.off();
    lcd.setCursor(0,1);
    Alarm.delay(1000);
}