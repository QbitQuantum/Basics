/**
 * @brief This function initializes the serial port for both directions (reading/writing) with fixed parameters:
 * \n baud=38400, parity=N, data=8, stop=1
 * @param *serialPort is a pointer to the name of the serial port
 * @return TRUE if success, FALSE in case of error.
 */
BOOL initSerial(CHAR *serialPort)
{
	COMMTIMEOUTS timeouts;
	int rc;
	DCB dcbStruct;
	CHAR msgTextBuf[256];

	// open the comm port.
	comPort = CreateFile(serialPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, NULL);
	if (comPort == INVALID_HANDLE_VALUE)
	{
		printf("Unable to open %s. \n", serialPort);
		return FALSE;
	}

	// get the current DCB, and adjust a few bits to our liking.
	memset(&dcbStruct, 0, sizeof(dcbStruct));

	dcbStruct.DCBlength = sizeof(dcbStruct);
	// printf("dcbStruct.DCBlength(): %ld \n", dcbStruct.DCBlength);

	rc = GetCommState(comPort, &dcbStruct);
	if (rc == 0)
	{
		printf("\nGetCommState(): ");
		printf(getLastErrorText(msgTextBuf, sizeof(msgTextBuf)));
		return FALSE;
	}

	// http://msdn.microsoft.com/en-us/library/windows/desktop/aa363143(v=vs.85).aspx
	BuildCommDCB("baud=38400 parity=N data=8 stop=1", &dcbStruct);

	rc = SetCommState(comPort, &dcbStruct);
	// If the function fails, the return value is zero.
	if (rc == 0)
	{
		printf("\nSetCommState(): ");
		printf(getLastErrorText(msgTextBuf, sizeof(msgTextBuf)));
		return FALSE;
	}

	// Retrieve the timeout parameters for all read and write operations on the port.
	GetCommTimeouts (comPort, &timeouts);

	timeouts.ReadIntervalTimeout = 250;
	timeouts.ReadTotalTimeoutMultiplier = 1;
	timeouts.ReadTotalTimeoutConstant = 500;
	timeouts.WriteTotalTimeoutMultiplier = 1;
	timeouts.WriteTotalTimeoutConstant = 2500;

	rc = SetCommTimeouts(comPort, &timeouts);          // If the function fails, the return value is zero.
	if (rc == 0)
	{
		printf("\nSetCommTimeouts(): ");
		printf(getLastErrorText(msgTextBuf, sizeof(msgTextBuf)));
		return FALSE;
	}

	return TRUE;
}