// COMx for windows, returns NULL on error
tUartHandle UartOpen(char* szPortName)
{
	HANDLE serial_handle; 
	DCB  dcb;

	memset(&dcb,0,sizeof(dcb));

	/* -------------------------------------------------------------------- */
	// set DCB to configure the serial port
	dcb.DCBlength       = sizeof(dcb);

	dcb.fOutxCtsFlow    = 0;
	dcb.fOutxDsrFlow    = 0;
	dcb.fDtrControl     = DTR_CONTROL_ENABLE; // enable for power
	dcb.fDsrSensitivity = 0;
	dcb.fRtsControl     = RTS_CONTROL_ENABLE; // enable for power
	dcb.fOutX           = 0;
	dcb.fInX            = 0;

	/* ----------------- misc parameters ----- */
	dcb.fErrorChar      = 0;
	dcb.fBinary         = 1;
	dcb.fNull           = 0;
	dcb.fAbortOnError   = 0;
	dcb.wReserved       = 0;
	dcb.XonLim          = 2;
	dcb.XoffLim         = 4;
	dcb.XonChar         = 0x13;
	dcb.XoffChar        = 0x19;
	dcb.EvtChar         = 0;

	/* ----------------- defaults ----- */
	dcb.BaudRate = 4800;
	dcb.Parity   = NOPARITY;
	dcb.fParity  = 0;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 8;


	/* -------------------------------------------------------------------- */
	// opening serial port
	serial_handle = CreateFile(szPortName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);

	if (serial_handle == INVALID_HANDLE_VALUE)
	{
		//printf("Cannot open port \n");
		return NULL;
	}

	SetCommMask(serial_handle, 0);

	if(!SetCommState(serial_handle, &dcb))
	{
		//printf("Error setting up COM params\n");
		CloseHandle(serial_handle);
		return NULL;
	}

	return serial_handle;
}