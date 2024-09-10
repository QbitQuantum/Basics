void LCDScreen::printError( int mess )
{
  lcd.clear();
  lcd.home();
  
  String message;
  if ( mess == 1 ) { message = "ERR: Overheating"; }
  else if ( mess < 1 ) { message = "ERR: Not ramping"; }
  else { message = "ERR: wrap failed"; }

  lcd.print( message );

  lcd.setCursor( 0, 1 );
  lcd.print( "Check hardware" );
}