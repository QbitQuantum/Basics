//////////////////////////////////////////////////////////////////////
// CloseConnection
// return:   0  always
//
int CAsyncPort::CloseConnection()
{
	// not connected
	m_isConnected = FALSE;

	// disable event notification and wait for thread to halt
	SetCommMask(m_hCommDev, 0);

	// block until thread has been halted
	while (m_dwThreadID != 0) {
		Sleep(10);
	}

	// drop DTR
	EscapeCommFunction(m_hCommDev, CLRDTR);

	// purge any outstanding reads/writes and close device handle
	PurgeComm (
		m_hCommDev,
		PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR
	);

	// close device
	CloseHandle(m_hCommDev);

	// reset instance variables
	m_hCommDev = INVALID_HANDLE_VALUE;
	memset(m_szCommDevName, 0, sizeof (m_szCommDevName));
	memset(& m_commConfig, 0, sizeof (COMMCONFIG));;
	m_commConfig.dwSize = sizeof (COMMCONFIG);
	memset(& m_commProp, 0, sizeof (COMMPROP));
	memset(& m_commTimeOuts, 0, sizeof (COMMTIMEOUTS));
	memset(m_baInBuf, 0, sizeof (m_baInBuf));
	m_nInBufIndex = 0;
	m_nInBufSize = 0;

	return (0);
}