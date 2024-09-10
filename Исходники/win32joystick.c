int
ui_joystick_init( void )
{
  int retval;
  JOYINFO joyinfo;

  retval = joyGetNumDevs();

  if( retval >= 2 ) {

    retval = 2;

    if( joyGetPos( JOYSTICKID2, &joyinfo ) == JOYERR_UNPLUGGED ) {
      ui_error( UI_ERROR_ERROR, "failed to initialise joystick 2" );
      return 0;
    }
  }

  if( retval > 0 ) {

    if( joyGetPos( JOYSTICKID1, &joyinfo ) == JOYERR_UNPLUGGED ) {
      ui_error( UI_ERROR_ERROR, "failed to initialise joystick 1" );
      return 0;
    }
  }

  return retval;
}