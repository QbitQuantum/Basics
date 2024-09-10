int send_nblk( SOCKET s, char *buf, int len, int flags, unsigned int timeout, CTCPIPSystemDrvr* pTCPIPSystem)
{
	unsigned long sflags = 0;
	int nLeft = len;
	int idx = 0;
	int retcode;
	long lastResult; 

	DWORD written = 0;
	WSABUF wsabuf;
	WSAOVERLAPPED overlapped;

	SEND_INFO si;
	si.hEvent = pTCPIPSystem->m_hEvents[1];
	si.s = s;
	si.timeout = timeout;

	overlapped.hEvent = pTCPIPSystem->m_hEvents[1];

	while (nLeft > 0)
	{
		wsabuf.buf = &buf[idx];
		wsabuf.len = nLeft;
		if (WSASend(s, &wsabuf, 1, &written, 0, &overlapped, NULL) == 0)
		{
			lastResult = written;
		}
		else
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				(fpTCPIPSET_ERROR)((long)pTCPIPSystem, PC, TCPIP, pTCPIPSystem->odbcAPI, E_DRIVER, pTCPIPSystem->m_object_ref, O_DO_WRITE_READ, F_SEND, WSAGetLastError(), (int)0);
				return false;
			}
			retcode = wait_for_event(&si, FD_WRITE, pTCPIPSystem);
			if (retcode == 0)
				return false;
			if (FALSE==WSAGetOverlappedResult(s, &overlapped, &written, false, &sflags))
			{
				(fpTCPIPSET_ERROR)((long)pTCPIPSystem, PC, TCPIP, pTCPIPSystem->odbcAPI, E_DRIVER, pTCPIPSystem->m_object_ref, O_DO_WRITE_READ, F_SEND_GETOVERLAPPEDRESULTS, WSAGetLastError(), (int)0);
				return false;
			}
			lastResult = written;
		}

		nLeft -= lastResult;
		idx += lastResult;
	}
	return idx;
}