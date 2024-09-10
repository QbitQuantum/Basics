bool PrinterSerial::RawConnect( string device, int baudrate ) {
#ifdef WIN32
  if ( IsConnected() || device_handle != INVALID_HANDLE_VALUE ) {
    Disconnect();
    if ( device_handle != INVALID_HANDLE_VALUE )
      return false;
  }

  device_handle = CreateFile( device.c_str(),
			      GENERIC_READ | GENERIC_WRITE,
			      0,
			      NULL,
			      OPEN_EXISTING,
			      FILE_ATTRIBUTE_NORMAL,
			      NULL );
  if ( device_handle == INVALID_HANDLE_VALUE ) {
    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error opening port %s"), device.c_str() );
    err_str[ 256 ] = '\0';

    ostringstream os;
    os << err_str << " (" << GetLastError() << ")"<< endl;
    LogError( os.str().c_str() );
    return false;
  }

  DCB dcb = { 0 };
  dcb.DCBlength = sizeof( dcb );

  if ( ! GetCommState( device_handle, &dcb ) ) {
    CloseHandle( device_handle );
    device_handle = INVALID_HANDLE_VALUE;
    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error getting port %s state"), device.c_str() );
    err_str[ 255 ] = '\0';

    ostringstream os;
    os << err_str << " (" << GetLastError() << ")"<< endl;
    LogError( os.str().c_str() );
    return false;
  }

  dcb.BaudRate = baudrate;
  dcb.fBinary = 1;
  dcb.fParity = 0;
  dcb.fOutxCtsFlow = 0;
  dcb.fOutxDsrFlow = 0;
  dcb.fDtrControl = DTR_CONTROL_ENABLE;
  dcb.fDsrSensitivity = 0;
  dcb.fOutX = 0;
  dcb.fInX = 0;
  dcb.fNull = 0;
  dcb.fRtsControl = RTS_CONTROL_ENABLE;
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
  dcb.StopBits = ONESTOPBIT;

  if ( ! SetCommState( device_handle, &dcb ) ) {
    CloseHandle( device_handle );
    device_handle = INVALID_HANDLE_VALUE;
    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error setting port %s state"), device.c_str() );
    err_str[ 255 ] = '\0';

    ostringstream os;
    os << err_str << " (" << GetLastError() << ")"<< endl;
    LogError( os.str().c_str() );
    return false;
  }

  COMMTIMEOUTS ct;

  if ( ! GetCommTimeouts( device_handle, &ct ) ) {
    CloseHandle( device_handle );
    device_handle = INVALID_HANDLE_VALUE;
    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error getting port %s timeouts"), device.c_str() );
    err_str[ 255 ] = '\0';

    ostringstream os;
    os << err_str << " (" << GetLastError() << ")"<< endl;
    LogError( os.str().c_str() );
    return false;
  }

  ct.ReadIntervalTimeout = 5;
  ct.ReadTotalTimeoutConstant = max_recv_block_ms;
  ct.ReadTotalTimeoutMultiplier = 0;
  ct.WriteTotalTimeoutConstant = max_recv_block_ms;
  ct.WriteTotalTimeoutMultiplier= 0;

  if ( ! SetCommTimeouts( device_handle, &ct ) ) {
    CloseHandle( device_handle );
    device_handle = INVALID_HANDLE_VALUE;
    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error setting port %s timeouts"), device.c_str() );
    err_str[ 255 ] = '\0';
    ostringstream os;
    os << err_str << " (" << GetLastError() << ")"<< endl;
    LogError( os.str().c_str() );
    return false;
  }

  *raw_recv = '\0';

#else
  // Verify speed is valid and convert to posix value
  speed_t speed = B0;
  bool custom_baud = false;

  switch ( baudrate ) {
  case 50: speed = B50; break;
  case 75: speed = B75; break;
  case 110: speed = B110; break;
  case 134: speed = B134; break;
  case 150: speed = B150; break;
  case 200: speed = B200; break;
  case 300: speed = B300; break;
  case 600: speed = B600; break;
  case 1200: speed = B1200; break;
  case 1800: speed = B1800; break;
  case 2400: speed = B2400; break;
  case 4800: speed = B4800; break;
  case 9600: speed = B9600; break;
  case 19200: speed = B19200; break;
  case 38400: speed = B38400; break;
  case 57600: speed = B57600; break;
  case 115200: speed = B115200; break;
  case 230400: speed = B230400; break;
  default:
    ostringstream ostr;
    ostr << "Nonstandard baudrate " << baudrate << endl;
    LogLine( ostr.str().c_str() );
    speed = baudrate;
    custom_baud = true;
    // char err_str[ 256 ];
    // snprintf( err_str, 256, _( %d\n"), baudrate );
    // if ( err_str[ 254 ] != '\0' )
    //   err_str[ 254 ] = '\n';
    // err_str[ 255 ] = '\0';
    //LogError( err_str );
    // return false;
  }

  if ( IsConnected() || device_fd >= 0 ) {
    Disconnect();
    if ( device_fd >= 0 )
      return false;
  }

  // Open file
  if ( ( device_fd = open( device.c_str(), O_RDWR | O_NOCTTY ) ) < 0 ) {
    int err = errno;
    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error opening port %s"), device.c_str() );
    err_str[ 255 ] = '\0';

    ostringstream os;
    os << err_str << ": " << strerror( err ) << endl;
    LogError( os.str().c_str() );
    return false;
  }

  // Configure port
  struct termios attribs;
  if ( tcgetattr( device_fd, &attribs ) < 0 ) {
    int err = errno;
    close( device_fd );
    device_fd = -1;

    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error getting port %s state"), device.c_str() );
    err_str[ 255 ] = '\0';

    ostringstream os;
    os << err_str << ": " << strerror( err ) << endl;
    LogError( os.str().c_str() );
    return false;
  }

  // Use RAW settings, except add ICANON.  ICANON makes the port line buffered
  // and read will return immediately when a newline is received.
  // HUPCL lowers the modem control lines (hang up) when the port is closed
  cfmakeraw( &attribs );
  attribs.c_lflag |= ICANON;
  attribs.c_cflag |= HUPCL;

  if( tcsetattr( device_fd, TCSANOW, &attribs ) < 0 ) {
    close( device_fd );
    device_fd = -1;

    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error enabling port %s raw mode\n"), device.c_str() );
    if ( err_str[ 254 ] != '\0' )
      err_str[ 254 ] = '\n';
    err_str[ 255 ] = '\0';

    LogError( err_str );
    return false;
  }

  // Set port speed
  bool baudrate_succeeded = false;

#if HAVE_ASM_TERMBITS_H
  if ( custom_baud ) {
    // non-standard baud rate
    baudrate_succeeded = set_custom_baudrate( device_fd, speed );
  } else {
    baudrate_succeeded = cfsetispeed( &attribs, speed ) >= 0 
                      && cfsetospeed( &attribs, speed ) >= 0
                      && tcsetattr( device_fd, TCSANOW, &attribs )  >= 0;
  }
#else
  baudrate_succeeded = cfsetispeed( &attribs, speed ) >= 0 
                    && cfsetospeed( &attribs, speed ) >= 0
                    && tcsetattr( device_fd, TCSANOW, &attribs )  >= 0;
#endif

  if ( ! baudrate_succeeded ) {
    close( device_fd );
    device_fd = -1;
    char err_str[ 256 ];
    snprintf( err_str, 256, _("Error setting port %s baudrate to %d\n"), device.c_str(), baudrate );
    if ( err_str[ 254 ] != '\0' )
      err_str[ 254 ] = '\n';
    err_str[ 255 ] = '\0';

    LogError( err_str );
    return false;
  }

#endif

  char msg[ 256 ];
  memcpy( msg, "--- ", 4 );
  snprintf( msg + 4, 256 - 4, _("Connected to port %s at %d baud\n"), device.c_str(), baudrate );
  if ( msg[ 254 ] != '\0' )
    msg[ 254 ] = '\n';
  msg[ 255 ] = '\0';
  LogLine( msg );

  // Reset line number
  prev_cmd_line_number = 0;

  return true;
}