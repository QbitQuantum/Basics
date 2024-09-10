void Personality_3::ChangeButton(BT *bt, int mode, bool button)
{ 
  extern sound beeper;
  extern ChapREEPROM myEEPROM;

  if (button){
    if (buttonToggle){
      if (myEEPROM.getMode() == 0){ // if a USB is put in with the mode set to 0, meaning autonomous
	cmd = AUTO_ON;
      } else {
	cmd = TELE_ON;
      }
      beeper.beep();
    } else {
      cmd = TELE_OFF;
      beeper.boop();
    }
      buttonToggle = !buttonToggle;
  }
}