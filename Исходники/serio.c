/*-------------------------------------------------------------------------
 Open a comm port and get ready for I/O
 Call with a pointer to an uninitizlized serio_t.
 If you call this, don't call serio_open_handle().
-------------------------------------------------------------------------*/
serio_res_t serio_open(serio_t *serio, long baud, const char *portname)
{
	COMMTIMEOUTS	CommTimeOuts ;
	DCB				dcb ;
	SECURITY_ATTRIBUTES SecurityAttributes;
	HANDLE h;

	/*--- Set up Win32 stuff ---*/

	if		(baud <= CBR_9600)	baud = CBR_9600;
	else if (baud <= CBR_19200)	baud = CBR_19200;
	else if (baud <= CBR_38400)	baud = CBR_38400;
	else						baud = CBR_57600;

	/* Let child processes inherit this handle. */
	memset(&SecurityAttributes, 0, sizeof(SECURITY_ATTRIBUTES));
	SecurityAttributes.nLength =				sizeof( SECURITY_ATTRIBUTES );
	SecurityAttributes.lpSecurityDescriptor =	NULL;
	SecurityAttributes.bInheritHandle =			TRUE;

	h = CreateFile(portname, GENERIC_READ | GENERIC_WRITE,
		0,                    // exclusive access
		&SecurityAttributes,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL
#ifdef USE_OVERLAP
		| FILE_FLAG_OVERLAPPED // overlapped I/O
#endif
		, NULL);

	if (INVALID_HANDLE_VALUE == h) {
		DPRINT(("serio_open: CreateFile(%s...) failed\n", portname));
		return serio_RES_BAD;
	}

	// Set the size of the input and output buffer.
	if (!SetupComm( h, 4096, 0 )) {
		DPRINT(("serio_open: SetupComm failed\n"));
		return serio_RES_BUG;
	}

	// purge any information in the buffer
	if (!PurgeComm( h, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR)) {
		DPRINT(("serio_open: PurgeComm failed\n"));
		return serio_RES_BUG;
	}

	// set the time-out parameters for all read and write operations
#if 1
	// Cause ReadFile to never wait.
	// Works OK in Win95.
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
	CommTimeOuts.ReadTotalTimeoutConstant = 0 ;
#elif 0
	// Cause ReadFile to wait 50 milliseconds, then time out unconditionally.
	// Fails sometimes in Win95; the overlapped read *never* completes.
	CommTimeOuts.ReadIntervalTimeout = 0 ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
	CommTimeOuts.ReadTotalTimeoutConstant = 50 ;
#elif 0
	// Cause ReadFile to wait 100 milliseconds for traffic to start, but
	// wait only 10 milliseconds for traffic to resume if it goes silent
	// after starting.
	// Fails sometimes in Win95; the overlapped read *never* completes.
	CommTimeOuts.ReadIntervalTimeout = 10 ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
	CommTimeOuts.ReadTotalTimeoutConstant = 100 ;
#endif
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0 ;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000 ;	/* will writes timeout? */

	if (!SetCommTimeouts( h, &CommTimeOuts )) {
		DPRINT(("serio_open: SetCommTimeouts failed\n"));
		return serio_RES_BUG;
	}

	dcb.DCBlength = sizeof( DCB ) ;

	if (!GetCommState( h, &dcb)) {
		DPRINT(("serio_open: GetCommState failed\n"));
		return serio_RES_BUG;
	}

	dcb.BaudRate = baud;
	dcb.Parity = FALSE ;
	dcb.fBinary = TRUE ;
	dcb.fOutxCtsFlow = FALSE ;
	dcb.fOutxDsrFlow = FALSE ;
	dcb.Parity = NOPARITY ;
	dcb.ByteSize = 8 ;
	dcb.StopBits = ONESTOPBIT ;

	if (!SetCommState( h, &dcb)) {
		DPRINT(("serio_open: SetCommState failed\n"));
		return serio_RES_BUG;
	}

	return serio_open_handle(serio, h);
}