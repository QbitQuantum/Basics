bool QSerial::open( const QString &dev, int speed )
{
	isatend = false;
#if ( defined( __linux__ ) | defined( __APPLE__ ) )
#ifdef DEBUG_SERIAL
	logFile = new QFile( "/tmp/qserial.log", this );
	logFile->open( QIODevice::Append );
	QByteArray ba = "Open file:";
	ba += dev;
	ba += "\n";
	logFile->write( ba );
#endif
	io_port = ::open( dev.toUtf8(), O_RDWR|O_NOCTTY|O_NONBLOCK );
	if ( io_port == -1 ) {
		perror( "Failed to open serial" );
		return false;
	}
#if ( defined( __APPLE__ ) )
	if (ioctl(io_port, TIOCEXCL)==-1)
		qWarning( "Failed to set exclusiv open" );
	// Clear O_NONBLOCK flag.
	if (fcntl( io_port, F_SETFL,0)==-1)
		qWarning( "Failed to clear NONBLOCK flag" );
#endif
	tcgetattr( io_port, &oldtio );

	bzero( &newtio, sizeof( newtio ) );
	int s;
	switch( speed ) {
		case 4800:
			s = B4800; break;
		case 9600:
			s = B9600; break;
		case 19200:
			s = B19200; break;
		case 38400:
			s = B38400; break;
		case 57600:
			s = B57600; break;
		case 115200:
			s = B115200; break;
		default:
			s = B9600; break;
	}
	cfsetispeed( &newtio, s );
	cfsetospeed( &newtio, s );
	newtio.c_cflag |= CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNBRK | IGNPAR;

	newtio.c_cc[VTIME] = 10;
        newtio.c_cc[VMIN] = 1;

	tcflush( io_port, TCIFLUSH );

	tcsetattr( io_port, TCSANOW, &newtio );

	QIODevice::open( ReadWrite );
	setupSocketNotifiers();
	return true;
#else
	fh = CreateFileA( dev.toAscii(), GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL );
			//  OPEN_EXISTING, FILE_ATTRIUBTE_NORMAL, NULL );
	if ( fh == INVALID_HANDLE_VALUE ) {
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError(); 

		FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,
				0, NULL );
		
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
				(lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)"open")+40)*sizeof(TCHAR)); 
		lasterror = "";
		for( int i=0;i<(lstrlen((LPCTSTR)lpMsgBuf));i++ )
			lasterror += (((LPCTSTR)lpMsgBuf)[i]);
		//lasterror.sprintf( "%i: open failed with err %d: %s", (lstrlen((LPCTSTR)lpMsgBuf)), (int)dw, (const char *)(LPCTSTR)lpMsgBuf );
		return false;
	}
	int s;
	switch( speed ) {
		case 4800:
			s = CBR_4800; break;
		case 9600:
			s = CBR_9600; break;
		case 19200:
			s = CBR_19200; break;
		case 38400:
			s = CBR_38400; break;
		case 57600:
			s = CBR_57600; break;
		case 115200:
			s = CBR_115200; break;
		default:
			s = CBR_9600; break;
	}
	COMMCONFIG comcfg;
	if ( GetCommState(fh, &comcfg.dcb) ) {
		comcfg.dcb.BaudRate = s;
		comcfg.dcb.ByteSize = 8;
		comcfg.dcb.Parity = NOPARITY;
		comcfg.dcb.StopBits = ONESTOPBIT;
		comcfg.dcb.fAbortOnError = TRUE;
		comcfg.dcb.fOutxCtsFlow = FALSE;
		comcfg.dcb.fOutxDsrFlow = FALSE;
		comcfg.dcb.fDtrControl = DTR_CONTROL_DISABLE;
		comcfg.dcb.fRtsControl = RTS_CONTROL_DISABLE;
		comcfg.dcb.fDsrSensitivity = FALSE;
		comcfg.dcb.fTXContinueOnXoff = TRUE;
		comcfg.dcb.fOutX = FALSE;
		comcfg.dcb.fInX = FALSE;
		comcfg.dcb.fBinary = TRUE;
		comcfg.dcb.fParity = TRUE;
		SetCommState( fh, &comcfg.dcb);
		GetCommState( fh, &comcfg.dcb );
	}
	QIODevice::open( ReadWrite );
	setupSocketNotifiers();
	return true;
#endif
}