WindowsSimPort::WindowsSimPort(const char *port) {
	portname = NULL;

	if(NULL == port || 0 == strlen(port)) {
		return;
	}

	portname = strdup(port);

	char fullportname[512];
	_snprintf(fullportname, sizeof(fullportname), "\\\\.\\%s", portname);
	portHandle=CreateFileA(fullportname, GENERIC_READ|GENERIC_WRITE,0, NULL, OPEN_EXISTING, 0, NULL);
	if (portHandle == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Invalid handle returned by CreateFileA [port \"%s\"]\n", fullportname);
		return;
	}
	COMMCONFIG Win_CommConfig;
	COMMTIMEOUTS Win_CommTimeouts;
	unsigned long confSize = sizeof(COMMCONFIG);
	Win_CommConfig.dwSize = confSize;
	GetCommConfig(portHandle, &Win_CommConfig, &confSize);
	Win_CommConfig.dcb.Parity = 0;
	Win_CommConfig.dcb.fRtsControl = RTS_CONTROL_DISABLE;
	Win_CommConfig.dcb.fOutxCtsFlow = FALSE;
	Win_CommConfig.dcb.fOutxDsrFlow = FALSE;
	Win_CommConfig.dcb.fDtrControl = DTR_CONTROL_DISABLE;
	Win_CommConfig.dcb.fDsrSensitivity = FALSE;
	Win_CommConfig.dcb.fNull=FALSE;
	Win_CommConfig.dcb.fTXContinueOnXoff = FALSE;
	Win_CommConfig.dcb.fInX=FALSE;
	Win_CommConfig.dcb.fOutX=FALSE;
	Win_CommConfig.dcb.fBinary=TRUE;
	Win_CommConfig.dcb.DCBlength = sizeof(DCB);
	Win_CommConfig.dcb.BaudRate = 9600;
	Win_CommConfig.dcb.ByteSize = 8;
	Win_CommTimeouts.ReadIntervalTimeout = 50;
	Win_CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	Win_CommTimeouts.ReadTotalTimeoutConstant = 110;
	Win_CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	Win_CommTimeouts.WriteTotalTimeoutConstant = 110;
	SetCommConfig(portHandle, &Win_CommConfig, sizeof(COMMCONFIG));
	SetCommTimeouts(portHandle,&Win_CommTimeouts);

	readbuf_pos = 0;
	memset(readbuf, '\0', sizeof(readbuf));
	memset(lastread, '\0', sizeof(lastread));

	setUsable(1);
}