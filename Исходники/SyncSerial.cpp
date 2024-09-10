DWORD __stdcall ConfigSerialPort(HANDLE h, DWORD dwBaudRate, DWORD dwTimeOutInSec)
{
	if (!SetupComm(h, 1024, 1024))
	{
		return ::GetLastError();
	}

	DCB dcbConfig;

	if (GetCommState(h, &dcbConfig)) /* Configuring Serial Port Settings */
	{
		dcbConfig.BaudRate = dwBaudRate;
		dcbConfig.ByteSize = 8;
		dcbConfig.Parity = NOPARITY;
		dcbConfig.StopBits = ONESTOPBIT;
		dcbConfig.fBinary = TRUE;
		dcbConfig.fParity = TRUE;
	}
	else
	{
		return ::GetLastError();
	}

	if (!SetCommState(h, &dcbConfig))
	{
		return ::GetLastError();
	}

	COMMTIMEOUTS commTimeout;

	if (GetCommTimeouts(h, &commTimeout)) /* Configuring Read & Write Time Outs */
	{
		commTimeout.ReadIntervalTimeout = 1000 * dwTimeOutInSec;
		commTimeout.ReadTotalTimeoutConstant = 1000 * dwTimeOutInSec;
		commTimeout.ReadTotalTimeoutMultiplier = 0;
		commTimeout.WriteTotalTimeoutConstant = 1000 * dwTimeOutInSec;
		commTimeout.WriteTotalTimeoutMultiplier = 0;
	}
	else
	{
		return ::GetLastError();
	}

	if (SetCommTimeouts(h, &commTimeout))
	{
		return ERROR_SUCCESS;
	}
	else
	{
		return ::GetLastError();
	}
}