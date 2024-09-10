bool WinSerialPort::connect(const char *portName, const int baudRate, const size_t inQueueSize, const size_t outQueueSize)
#endif
{
	hComPort_ = CreateFile(
		portName,
		GENERIC_READ | GENERIC_WRITE,
		0,    // exclusive access 
		NULL, // default security attributes 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL 
	);
	if (INVALID_HANDLE_VALUE == hComPort_)
	{
		// Handle the error. 
		std::cerr << "CreateFile failed with error, " << GetLastError() << ": Port:" << portName << ", BaudRate:" << baudRate << ", Parity:None, Stop bits:1" << std::endl;
		//::CloseHandle(hComPort_);
		return false;
	}

	// Set the event mask. 
	//if (!SetCommMask(hComPort_, EV_CTS | EV_DSR))
	if (!SetCommMask(hComPort_, EV_RXCHAR))
	{
		// Handle the error. 
		std::cerr << "SetCommMask failed with error: " << GetLastError() << std::endl;
		return false;
	}
	
	// set sizes of inqueue & outqueue
	SetupComm(hComPort_, (DWORD)inQueueSize, (DWORD)outQueueSize);	
	
	// purse port
	PurgeComm(hComPort_, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	
	// set timeouts
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2 * CBR_9600 / baudRate;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(hComPort_, &timeouts);
	
	// set dcb
	DCB dcb;
	dcb.DCBlength = sizeof(DCB);
	GetCommState(hComPort_, &dcb);
	//dcb.fBinary = TRUE;  // Windows does not support nonbinary mode transfers, so this member must be TRUE
	dcb.BaudRate = baudRate;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;  // no parity
	dcb.StopBits = ONESTOPBIT;  // 1 stop bit
	//dcb.fInX = dcb.fOutX = TRUE;  // use Xon & Xoff
	//dcb.XonChar = SWL_SERIAL_PROTOCOL__ASCII_XON;
	//dcb.XoffChar = SWL_SERIAL_PROTOCOL__ASCII_XOFF;
	//dcb.XonLim = 100;
	//dcb.XoffLim = 100;
	if (!::SetCommState(hComPort_, &dcb))
	{
		std::cerr << "SetCommState failed with error: " << GetLastError() << std::endl;
		return false;
	}

	return true;
}