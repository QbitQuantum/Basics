static int gry_open(CableHandle *h)
{
	DCB dcb;
	BOOL fSuccess;
	COMMTIMEOUTS cto;

	// Open device
	h->priv = (void *)CreateFile(h->device, GENERIC_READ | GENERIC_WRITE, 0,
		    NULL, OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED /*| FILE_FLAG_NO_BUFFERING*/,
			NULL);
	if (hCom == INVALID_HANDLE_VALUE) 
	{
		ticables_warning("CreateFile");
		return ERR_GRY_CREATEFILE;
	}
  
	// Setup buffer size
	fSuccess = SetupComm(hCom, 1024, 1024);
	if (!fSuccess) 
	{
		ticables_warning("SetupComm");
		return ERR_GRY_SETUPCOMM;
	}

	// Retrieve config structure
	fSuccess = GetCommState(hCom, &dcb);
	if (!fSuccess) 
	{
		ticables_warning("GetCommState");
		return ERR_GRY_GETCOMMSTATE;
	}

	// Fills the structure with config
	dcb.BaudRate = CBR_9600;	// 9600 bauds
    dcb.fBinary = TRUE;			// Binary mode
    dcb.fParity = FALSE;		// Parity checking disabled
    dcb.fOutxCtsFlow = FALSE;	// No output flow control
    dcb.fOutxDsrFlow = FALSE;	// Idem
    dcb.fDtrControl = DTR_CONTROL_DISABLE;	// Provide power supply
    dcb.fDsrSensitivity = FALSE;	// ignore DSR status
    dcb.fOutX = FALSE;			// no XON/XOFF flow control
    dcb.fInX = FALSE;			// idem
    dcb.fErrorChar = FALSE;		// no replacement
    dcb.fNull = FALSE;			// don't discard null chars
    dcb.fRtsControl = RTS_CONTROL_ENABLE;	// Provide power supply
    dcb.fAbortOnError = FALSE;	// do not report errors

    dcb.ByteSize = 8;			// 8 bits
    dcb.Parity = NOPARITY;		// no parity checking
    dcb.StopBits = ONESTOPBIT;	// 1 stop bit

    // Config COM port
    fSuccess = SetCommState(hCom, &dcb);
    if (!fSuccess) 
    {
		ticables_warning("SetCommState");
		return ERR_GRY_SETCOMMSTATE;
    }

	// Wait for GrayLink to be ready
	Sleep(250);
  
	// Set timeouts
    fSuccess = GetCommTimeouts(hCom, &cto);
    if (!fSuccess) 
    {
		ticables_warning("GetCommTimeouts");
		return ERR_GRY_GETCOMMTIMEOUT;
    }
  
    cto.ReadIntervalTimeout = 0;

    cto.ReadTotalTimeoutMultiplier = 0;
    cto.ReadTotalTimeoutConstant = 100 * h->timeout;  
    
    cto.WriteTotalTimeoutMultiplier = 0;
    cto.WriteTotalTimeoutConstant = 100 * h->timeout;
  
    fSuccess = SetCommTimeouts(hCom, &cto);
    if (!fSuccess) 
    {
		ticables_warning("SetCommTimeouts");
		return ERR_GRY_SETCOMMTIMEOUT;
    }

	// Monitor receiving of chars
	fSuccess = SetCommMask(hCom, EV_RXCHAR);
	if (!fSuccess)
    {
		ticables_warning("SetCommMask");
		return ERR_GRY_SETCOMMMASK;
    }

	// Flush/Dicard buffers
	fSuccess = PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	if (!fSuccess) 
	{
		ticables_warning("PurgeComm");
		return ERR_GRY_PURGECOMM;
	}

	return 0;
}