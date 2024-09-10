bool SERIAL_open(const char* portname, COMPORT* port) {
	// allocate COMPORT structure
	COMPORT cp = (_COMPORT*)malloc(sizeof(_COMPORT));
	if(cp == NULL) return false;
	
	cp->breakstatus=false;

	// open the port in NT object space (recommended by Microsoft)
	// allows the user to open COM10+ and custom port names.
	int len = strlen(portname);
	if(len > 240) {
		SetLastError(ERROR_BUFFER_OVERFLOW);
		free(cp);
		return false;
	}
	char extended_portname[256] = "\\\\.\\";
	memcpy(extended_portname+4,portname,len+1);
	
	cp->porthandle = CreateFile (extended_portname,
					   GENERIC_READ | GENERIC_WRITE, 0,
									  // must be opened with exclusive-access
	                   NULL,          // no security attributes
	                   OPEN_EXISTING, // must use OPEN_EXISTING
	                   0,             // non overlapped I/O
	                   NULL           // hTemplate must be NULL for comm devices
	                  );

	if (cp->porthandle == INVALID_HANDLE_VALUE) goto cleanup_error;
	
	cp->orig_dcb.DCBlength=sizeof(DCB);

	if(!GetCommState(cp->porthandle, &cp->orig_dcb)) {
		goto cleanup_error;
	}

	// configure the port for polling
	DCB newdcb;
	memcpy(&newdcb,&cp->orig_dcb,sizeof(DCB));

	newdcb.fBinary=true;
	newdcb.fParity=true;
	newdcb.fOutxCtsFlow=false;
	newdcb.fOutxDsrFlow=false;
	newdcb.fDtrControl=DTR_CONTROL_DISABLE;
	newdcb.fDsrSensitivity=false;
	
	newdcb.fOutX=false;
	newdcb.fInX=false;
	newdcb.fErrorChar=0;
	newdcb.fNull=false;
	newdcb.fRtsControl=RTS_CONTROL_DISABLE;
	newdcb.fAbortOnError=false;

	if(!SetCommState(cp->porthandle, &newdcb)) {
		goto cleanup_error;
	}

	// Configure timeouts to effectively use polling
	COMMTIMEOUTS ct;
	ct.ReadIntervalTimeout = MAXDWORD;
	ct.ReadTotalTimeoutConstant = 0;
	ct.ReadTotalTimeoutMultiplier = 0;
	ct.WriteTotalTimeoutConstant = 0;
	ct.WriteTotalTimeoutMultiplier = 0;
	if(!SetCommTimeouts(cp->porthandle, &ct)) {
		goto cleanup_error;
	}
	if(!ClearCommBreak(cp->porthandle)) {
		// Bluetooth Bluesoleil seems to not implement it
		//goto cleanup_error;
	}
	DWORD errors;
	if(!ClearCommError(cp->porthandle, &errors, NULL)) {
		goto cleanup_error;
	}
	*port = cp;
	return true;

cleanup_error:
	if (cp->porthandle != INVALID_HANDLE_VALUE) CloseHandle(cp->porthandle);
	free(cp);
	return false;
}