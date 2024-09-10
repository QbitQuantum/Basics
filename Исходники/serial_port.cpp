bool serial_port::open(int comport_number, int baud) {
  if((comport_number>15)||(comport_number<0)) {
    printf("illegal comport number\n");
    return(false);
  }

  sprintf(_baud_str, "baud=%d data=8 parity=N stop=1", baud);
  _baudrate = baud;

  _port_handle = CreateFileA(comports[comport_number],
                      GENERIC_READ|GENERIC_WRITE,
                      0,                          /* no share  */
                      NULL,                       /* no security */
                      OPEN_EXISTING,
                      0,                          /* no threads */
                      NULL);                      /* no templates */

  if(_port_handle == INVALID_HANDLE_VALUE) {
    printf("unable to open comport\n");
    return(false);
  }

  DCB port_settings;
  memset(&port_settings, 0, sizeof(port_settings));  /* clear the new struct  */
  port_settings.DCBlength = sizeof(port_settings);

  if(!BuildCommDCBA(_baud_str, &port_settings)) {
    printf("unable to set comport dcb settings\n");
    CloseHandle(_port_handle);
    _port_handle = INVALID_HANDLE_VALUE;
    return(false);
  }

  if(!SetCommState(_port_handle, &port_settings)) {
    printf("unable to set comport cfg settings\n");
    CloseHandle(_port_handle);
    _port_handle = INVALID_HANDLE_VALUE; //not sure this is required
    return(false);
  }

  COMMTIMEOUTS Cptimeouts;

  Cptimeouts.ReadIntervalTimeout         = MAXDWORD;
  Cptimeouts.ReadTotalTimeoutMultiplier  = 0;
  Cptimeouts.ReadTotalTimeoutConstant    = 0;
  Cptimeouts.WriteTotalTimeoutMultiplier = 0;
  Cptimeouts.WriteTotalTimeoutConstant   = 0;

  if(!SetCommTimeouts(_port_handle, &Cptimeouts)) {
    printf("unable to set comport time-out settings\n");
    CloseHandle(_port_handle);
    return(false);
  }

  _port_name = comports[_port_number];
  return(true);
}