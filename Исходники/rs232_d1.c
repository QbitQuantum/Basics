int OpenComport(int comport_number, int baudrate)
{
  if((comport_number>MAX_COMPORT_NUM)||(comport_number<0))
  {
    printf("illegal comport number\n");
    return(1);
  }

  /*   ::: MODIFIED :::  [KPZ-09.01.2014] */
  snprintf(comports, MAX_COMPORT_LABEL_LENGTH,
           "\\\\.\\COM%d", comport_number);
  
  switch(baudrate)
  {
    case     110 : strcpy(baudr, "baud=110 data=8 parity=N stop=1");
                   break;
    case     300 : strcpy(baudr, "baud=300 data=8 parity=N stop=1");
                   break;
    case     600 : strcpy(baudr, "baud=600 data=8 parity=N stop=1");
                   break;
    case    1200 : strcpy(baudr, "baud=1200 data=8 parity=N stop=1");
                   break;
    case    2400 : strcpy(baudr, "baud=2400 data=8 parity=N stop=1");
                   break;
    case    4800 : strcpy(baudr, "baud=4800 data=8 parity=N stop=1");
                   break;
    case    9600 : strcpy(baudr, "baud=9600 data=8 parity=N stop=1");
                   break;
    case   19200 : strcpy(baudr, "baud=19200 data=8 parity=N stop=1");
                   break;
    case   38400 : strcpy(baudr, "baud=38400 data=8 parity=N stop=1");
                   break;
    case   57600 : strcpy(baudr, "baud=57600 data=8 parity=N stop=1");
                   break;
    case  115200 : strcpy(baudr, "baud=115200 data=8 parity=N stop=1");
                   break;
    case  128000 : strcpy(baudr, "baud=128000 data=8 parity=N stop=1");
                   break;
    case  256000 : strcpy(baudr, "baud=256000 data=8 parity=N stop=1");
                   break;
    default      : printf("invalid baudrate\n");
                   return(1);
                   break;
  }

  /*   ::: MODIFIED :::  [KPZ-09.01.2014] */
  Cport[comport_number] = CreateFileA(comports,
                      GENERIC_READ|GENERIC_WRITE,
                      0,                          /* no share  */
                      NULL,                       /* no security */
                      OPEN_EXISTING,
                      0,                          /* no threads */
                      NULL);                      /* no templates */

  if(Cport[comport_number]==INVALID_HANDLE_VALUE)
  {
    printf("unable to open comport\n");
    return(1);
  }

  DCB port_settings;
  memset(&port_settings, 0, sizeof(port_settings));  /* clear the new struct  */
  port_settings.DCBlength = sizeof(port_settings);

  if(!BuildCommDCBA(baudr, &port_settings))
  {
    printf("unable to set comport dcb settings\n");
    CloseHandle(Cport[comport_number]);
    return(1);
  }

  if(!SetCommState(Cport[comport_number], &port_settings))
  {
    printf("unable to set comport cfg settings\n");
    CloseHandle(Cport[comport_number]);
    return(1);
  }

  COMMTIMEOUTS Cptimeouts;

  Cptimeouts.ReadIntervalTimeout         = MAXDWORD;
  Cptimeouts.ReadTotalTimeoutMultiplier  = 0;
  Cptimeouts.ReadTotalTimeoutConstant    = 0;
  Cptimeouts.WriteTotalTimeoutMultiplier = 0;
  Cptimeouts.WriteTotalTimeoutConstant   = 0;

  if(!SetCommTimeouts(Cport[comport_number], &Cptimeouts))
  {
    printf("unable to set comport time-out settings\n");
    CloseHandle(Cport[comport_number]);
    return(1);
  }

  return(0);
}