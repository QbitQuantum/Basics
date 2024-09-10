void loop() {

  //Smoothing of weight and level sensor values
  raw = ((raw+offset)*.8+.2*analogRead(11)-offset);
  weight = raw *171/27;
  if(weight <0) weight = 0;
  motion = .2*motion + .8*readDistance(motionTrig,motionEcho)/58;
  right = .9*right + .1*(readDistance(rightTrig,rightEcho)/58);

  //Sends weight over serial as 2 bytes
  Serial1.write((int)weight / 256);
  Serial1.write((int)weight % 256);
  delay(500);

  left = .9*left + .1*readDistance(leftTrig,leftEcho)/58;
  rfill = (raverage-right-2)/(raverage-2) * 100.0;
  lfill = (laverage-left-2)/(laverage-2) * 100.0;

    if(rfill <0) rfill = 0;
    if(lfill <0) lfill = 0;
    fill=(lfill+rfill)/2;

    if (motion<20 && pos == 0) {
      open();

    }
    else if (motion >20 && pos > 0){
      close();
    }

    //Sets position and text on LCD display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("W: ");
    lcd.print((int)weight);
    lcd.setCursor(8,0);
    lcd.print("M: ");
    lcd.print(motion);
    lcd.setCursor(0,1);
    lcd.print("L: ");
    lcd.print((int)lfill);
    lcd.print("%");
    lcd.setCursor(8,1);
    lcd.print("R: ");
    lcd.print((int)rfill);
    lcd.print("%");
    Serial.println(userselected);
}