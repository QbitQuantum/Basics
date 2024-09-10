//----------------------------------------------------------------
bool ofSerial::setup(string portName, int baud){
	bInited = false;

	#if defined( TARGET_OSX ) || defined( TARGET_LINUX )

		//lets account for the name being passed in instead of the device path
		if(portName.size() > 5 && portName.substr(0, 5) != "/dev/"){
			portName = "/dev/" + portName;
		}

		ofLogNotice("ofSerial") << "opening " << portName << " @ " << baud << " bps";
		fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
		if(fd == -1){
			ofLogError("ofSerial") << "unable to open " << portName;
			return false;
		}

		struct termios options;
		tcgetattr(fd, &oldoptions);
		options = oldoptions;
		switch(baud){
			case 300:
			cfsetispeed(&options, B300);
				cfsetospeed(&options, B300);
				break;
		   case 1200:
			cfsetispeed(&options, B1200);
				cfsetospeed(&options, B1200);
				break;
		   case 2400:
			cfsetispeed(&options, B2400);
				cfsetospeed(&options, B2400);
				break;
		   case 4800:
			cfsetispeed(&options, B4800);
		cfsetospeed(&options, B4800);
		break;
		   case 9600:
			cfsetispeed(&options, B9600);
		cfsetospeed(&options, B9600);
		break;
		   case 14400:
			cfsetispeed(&options, B14400);
		cfsetospeed(&options, B14400);
		break;
		   case 19200:
			cfsetispeed(&options, B19200);
		cfsetospeed(&options, B19200);
		break;
		   case 28800:
			cfsetispeed(&options, B28800);
		cfsetospeed(&options, B28800);
		break;
		   case 38400:
			cfsetispeed(&options, B38400);
		cfsetospeed(&options, B38400);
		break;
		   case 57600:
			cfsetispeed(&options, B57600);
		cfsetospeed(&options, B57600);
		break;
		   case 115200:
			cfsetispeed(&options, B115200);
		cfsetospeed(&options, B115200);
		break;
		   case 230400:
			cfsetispeed(&options, B230400);
		cfsetospeed(&options, B230400);
		break;
		   default:
			cfsetispeed(&options, B9600);
		cfsetospeed(&options, B9600);
		ofLogError("ofSerial") << "setup(): cannot set " << baud << " bps, setting to 9600";
		break;
		}

		options.c_cflag |= (CLOCAL | CREAD);
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_iflag &= (tcflag_t) ~(INLCR | IGNCR | ICRNL | IGNBRK);
		options.c_oflag &= (tcflag_t) ~(OPOST);
		options.c_cflag |= CS8;
		tcsetattr(fd, TCSANOW, &options);

		bInited = true;
		ofLogNotice("ofSerial") << "opened " << portName << " sucessfully @ " << baud << " bps";

		return true;

	#elif defined( TARGET_WIN32 )

		char pn[sizeof(portName)];
		int num;
		if(sscanf(portName.c_str(), "COM%d", &num) == 1){
			// Microsoft KB115831 a.k.a if COM > COM9 you have to use a different
			// syntax
			sprintf(pn, "\\\\.\\COM%d", num);
		} else {
			strncpy(pn, (const char *)portName.c_str(), sizeof(portName)-1);
		}

		// open the serial port:
		// "COM4", etc...

		hComm = CreateFileA(pn, GENERIC_READ|GENERIC_WRITE, 0, 0,
							OPEN_EXISTING, 0, 0);

		if(hComm == INVALID_HANDLE_VALUE){
			ofLogError("ofSerial") << "setup(): unable to open " << portName;
			return false;
		}


		// now try the settings:
		COMMCONFIG cfg;
		DWORD cfgSize;
		WCHAR buf[80];

		cfgSize = sizeof(cfg);
		GetCommConfig(hComm, &cfg, &cfgSize);
		int bps = baud;
		swprintf(buf, L"baud=%d parity=N data=8 stop=1", bps);

		if(!BuildCommDCBW(buf, &cfg.dcb)){
			ofLogError("ofSerial") << "setup(): unable to build comm dcb, (" << buf << ")";
		}

		// Set baudrate and bits etc.
		// Note that BuildCommDCB() clears XON/XOFF and hardware control by default

		if(!SetCommState(hComm, &cfg.dcb)){
			ofLogError("ofSerial") << "setup(): couldn't set comm state: " << cfg.dcb.BaudRate << " bps, xio " << cfg.dcb.fInX << "/" << cfg.dcb.fOutX;
		}
		//ofLogNotice("ofSerial") << "bps=" << cfg.dcb.BaudRate << ", xio=" << cfg.dcb.fInX << "/" << cfg.dcb.fOutX;

		// Set communication timeouts (NT)
		COMMTIMEOUTS tOut;
		GetCommTimeouts(hComm, &oldTimeout);
		tOut = oldTimeout;
		// Make timeout so that:
		// - return immediately with buffered characters
		tOut.ReadIntervalTimeout = MAXDWORD;
		tOut.ReadTotalTimeoutMultiplier = 0;
		tOut.ReadTotalTimeoutConstant = 0;
		SetCommTimeouts(hComm, &tOut);

		bInited = true;
		return true;

	#else

		ofLogError("ofSerial") << "not implemented in this platform";
		return false;

	#endif
}