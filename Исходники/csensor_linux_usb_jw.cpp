// tests the open joystick file descriptor to see if it's really a JW, and set to read rawdata
bool CSensorLinuxUSBJW::testJoystick()
{
   // if made it here, then we have opened a joystick file descriptor
   m_iNumAxes = 0;
   m_iNumButtons = 0;
   memset(m_strJoystick, 0x00, 80);

   ioctl(m_fdJoy, JSIOCGAXES, &m_iNumAxes);
   ioctl(m_fdJoy, JSIOCGBUTTONS, &m_iNumButtons);
   ioctl(m_fdJoy, JSIOCGNAME(80), m_strJoystick);

//fprintf(stdout, "joystick found = %s\n", m_strJoystick);
//fflush(stdout);

   // compare the name of device, and number of buttons & axes with valid JoyWarrior values
   if (strcmp(m_strJoystick, IDSTR_JW24F8)
     || m_iNumButtons != NUM_BUTTON_JW24F8
     || m_iNumAxes != NUM_AXES_JW24F8) {
         closePort();  // this far in, we need to close the port!
         return false;
   }

   m_piAxes = (int *) calloc( m_iNumAxes, sizeof( int ) );
   memset(m_piAxes, 0x00, sizeof(int) * m_iNumAxes);
   m_strButton = (char *) calloc( m_iNumButtons, sizeof( char ) );
   memset(m_strButton, 0x00, sizeof(char) * m_iNumButtons);
  
   fcntl( m_fdJoy, F_SETFL, O_NONBLOCK );   // use non-blocking mode

   // try a read
   float x,y,z;
   // "prime" the joystick reader
   if (! read_xyz(x,y,z)) {
      closePort();  // this far in, we need to close the port!
      return false;
   }

   // if made it here, then it's a joywarrior, set to raw data mode
   struct js_corr corr[NUM_AXES_JW24F8];

   // Zero correction coefficient structure and set all axes to Raw mode 
   for (int i=0; i<NUM_AXES_JW24F8; i++) {
     corr[i].type = JS_CORR_NONE;
     corr[i].prec = 0;
     for (int j=0; j<8; j++) {
        corr[i].coef[j] = 0;
     }
   }

   if (ioctl(m_fdJoy, JSIOCSCORR, &corr)) {
      fprintf(stderr, "CSensorLinuxUSBJW:: error setting correction for raw data reads\n");
   }

   setType(SENSOR_USB_JW24F8);
   setPort(getTypeEnum());
   
   return true; // if here we can return true, i.e Joywarrior found on Linux joystick port, and hopefully set to read raw data
}