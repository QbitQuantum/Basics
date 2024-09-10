//----------------------------------------------------------------
bool ofSerial::setup(std::string portName, int baud){

	std::cout << "setup serial" << "\r\n";
	bInited = false;

	char pn[sizeof(portName)];
	int num;
	if (sscanf(portName.c_str(), "COM%d", &num) == 1) {
		// Microsoft KB115831 a.k.a if COM > COM9 you have to use a different
		// syntax
		sprintf(pn, "\\\\.\\COM%d", num);
	} else {
		strncpy(pn, (const char *)portName.c_str(), sizeof(portName)-1);
	}

	// open the serial port:
	// "COM4", etc...

	hComm=CreateFileA(pn,GENERIC_READ|GENERIC_WRITE,0,0,
					OPEN_EXISTING,0,0);

	if(hComm==INVALID_HANDLE_VALUE){
		std::cout << "setup(): unable to open " << portName << "\r\n";
		return false;
	}


	// now try the settings:
	COMMCONFIG cfg;
	DWORD cfgSize;
	char  buf[80];

	cfgSize=sizeof(cfg);
	GetCommConfig(hComm,&cfg,&cfgSize);
	int bps = baud;
	sprintf(buf,"baud=%d parity=N data=8 stop=1",bps);

	#if (_MSC_VER)       // microsoft visual studio
		// msvc doesn't like BuildCommDCB,
		//so we need to use this version: BuildCommDCBA
		if(!BuildCommDCBA(buf,&cfg.dcb)){
			std::cout << "setup(): unable to build comm dcb, (" << buf << ")" << "\r\n";
		}
	#else
		if(!BuildCommDCB(buf,&cfg.dcb)){
			std::cout << "setup(): unable to build comm dcb, (" << buf << ")" << "\r\n";
		}
	#endif


	// Set baudrate and bits etc.
	// Note that BuildCommDCB() clears XON/XOFF and hardware control by default

	if(!SetCommState(hComm,&cfg.dcb)){
		std::cout << "setup(): couldn't set comm state: " << cfg.dcb.BaudRate << " bps, xio " << cfg.dcb.fInX << "/" << cfg.dcb.fOutX << "\r\n";
	}
	//std::cout << "bps=" << cfg.dcb.BaudRate << ", xio=" << cfg.dcb.fInX << "/" << cfg.dcb.fOutX << "\r\n";

	// Set communication timeouts (NT)
	COMMTIMEOUTS tOut;
	GetCommTimeouts(hComm,&oldTimeout);
	tOut = oldTimeout;
	// Make timeout so that:
	// - return immediately with buffered characters
	tOut.ReadIntervalTimeout=MAXDWORD;
	tOut.ReadTotalTimeoutMultiplier=0;
	tOut.ReadTotalTimeoutConstant=0;
	SetCommTimeouts(hComm,&tOut);

	bInited = true;
	return true;
}