void loop(){
  if(gameFinished == false){
    float time_to = random(1,2); //.. Aantal milliseconde om mee te beginnen
    int i;
    float current_multiplier = 0.98;
    float cashedOutMultiplier;
    int randomNumber = random(0,1000);
    if(randomNumber < 201){
      randomNumber = 0;
    }
    for(i = 0; i <= randomNumber; i++){
      switch (lcd_key){
        case btnSELECT:{
          cashedOut = true;
          cashedOutMultiplier = current_multiplier;
          break;
        }}
        lcd.clear();
        lcd.print("BustaDuino");  // print a simple message on the LCD
        lcd.setCursor(0, 1);
        if(randomNumber > 0){
          current_multiplier = current_multiplier + 0.01;
        }else{
          current_multiplier = 0;
        }
        
        lcd.print(String(current_multiplier) + "x");
        Serial.print(String(current_multiplier) + "x");
        lcd_key = read_LCD_buttons();   // read the buttons
        if(i <= randomNumber && cashedOut == true){
          lcd.clear();
          lcd.print("You Win!");
          lcd.setCursor(0, 1);
          lcd.print(String(cashedOutMultiplier) + "x");
          Serial.print(String(cashedOutMultiplier) + "x");
          gameFinished = true;
          break;
        }else if(i >= randomNumber && cashedOut == false){
          lcd.clear();
          lcd.print("BUSTED!");
          lcd.setCursor(0, 1);
          lcd.print(String(current_multiplier) + "x");
          Serial.print(String(current_multiplier) + "x");
          gameFinished = true;
        }
        delay((time_to/i) * 3000);
    }
  }
}