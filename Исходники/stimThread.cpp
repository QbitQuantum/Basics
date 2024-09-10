bool StimThread::connectCOM(){
	//Connect to serial port for stage
	hCom = CreateFile(comName.utf16(),GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,0); //Zaber Stage Control
	if (hCom == INVALID_HANDLE_VALUE) {
		qDebug("Can't Connect to Stim");
		return false;
	}
	//Configure Ports
	DCB cfg;
	GetCommState(hCom,&cfg);
	//cfg.BaudRate = 1200000;
	//cfg.BaudRate = 115200; //for magnus' board
	cfg.BaudRate = 460800; //Lakshmi's system
	//cfg.BaudRate = 230400; //Lakshmi's system
	cfg.ByteSize = 8;
	cfg.StopBits = ONESTOPBIT;
	cfg.Parity = NOPARITY;
	cfg.fDtrControl = DTR_CONTROL_DISABLE;
	cfg.fRtsControl = RTS_CONTROL_DISABLE;
	if(!SetCommState(hCom, &cfg )){
		qDebug("Serial SetCommState Error %d - Stim ",GetLastError());
		return false;
	}
	
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = 0;
	timeouts.ReadTotalTimeoutMultiplier = 100;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 100;
	timeouts.WriteTotalTimeoutConstant = 100;
	if (!SetCommTimeouts(hCom,&timeouts)) {
		qDebug("SetCommTimeouts Error 1 - Stim");
		return false;
	}

	if (!SetupComm(hCom,2048,2048)){
		qDebug("SetupComm Error 1 - Stim"); 
		return false;
	}

	return true;
};