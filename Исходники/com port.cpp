int CComport::Open(int num)
{
	COMMTIMEOUTS timeouts;
	DCB          dcb;
	wchar_t port[64] = {NULL};
	// initialise the comm port
	// was TEXT("COM8")
	wsprintf(port, L"%s%d", L"\\\\.\\COM", num);
	hComm = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, NULL);
	// exit as a failure
	if(hComm == INVALID_HANDLE_VALUE)
	    return -1;
	// store the port name for closure
	wmemcpy(com_name, port, wcslen(port));
	// set com port params
	FillMemory(&dcb, sizeof(dcb), 0);
	dcb.DCBlength = sizeof(dcb);
	// change the port identity and parameters
	if(GetCommState(hComm, &dcb)){
		dcb.BaudRate = (CBR_57600);
		dcb.Parity   = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.ByteSize = 8;
		SetCommState(hComm, &dcb);
	}
	// set communication timeouts
	timeouts.ReadIntervalTimeout         = 0;
	timeouts.ReadTotalTimeoutMultiplier  = 0;
	timeouts.ReadTotalTimeoutConstant    = 1;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant   = 0;

	SetCommTimeouts(hComm, &timeouts);

	return 1;
}