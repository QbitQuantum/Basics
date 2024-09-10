int SerialPortWrite(char *szBuffer, int count)
{
	// TODO: Add your control notification handler code here
#if 0
	DWORD wCount = 0;
	WriteFile(hCom, szBuffer, count, &wCount, NULL);//发送数据
	return (int)wCount;
#else
	//char buffer[1024];
	//DWORD dwBytesWritten = 1024;
	DWORD dwErrorFlags;
	COMSTAT ComStat;
	OVERLAPPED m_osWrite;
	BOOL bWriteStat;
	DWORD dwRealSend = 0;

	strcat(szBuffer, "\r\n");
	count = count + 2;
	
	ZeroMemory(&m_osWrite, sizeof(m_osWrite));
	if (m_osWrite.hEvent != NULL)
	{
		ResetEvent(m_osWrite.hEvent);
		m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	if (ClearCommError(hCom, &dwErrorFlags, NULL))
	{
		PurgeComm(hCom, PURGE_TXABORT | PURGE_TXCLEAR);
		bWriteStat = WriteFile(hCom, szBuffer, count, &dwRealSend, &m_osWrite);
		if (!bWriteStat)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult(hCom, &m_osWrite, &dwRealSend, FALSE))
				{

					if (GetLastError() == ERROR_IO_INCOMPLETE)
					{
						//cout<<"写未完成，继续!"<     
						continue;
					}
				}
				//WaitForSingleObject(m_osWrite.hEvent, 1000);
				//GetOverlappedResult(hCom, &m_osWrite, (DWORD*)(&count), TRUE);
				return count;
			}
			return 0;
		}
	}
	return count;
#endif
}