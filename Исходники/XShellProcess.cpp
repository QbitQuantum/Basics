void XShellProcess::run()
{
	//Receive buffer size must be large than 3
	assert(sizeof(m_RecvBuffer)>3);

	DWORD dwRere=0;

	while(TRUE)
	{
		if(m_hReadPipe1!=INVALID_HANDLE_VALUE&&m_bConsoleActivate)
		{
			PeekNamedPipe(m_hReadPipe1,m_RecvBuffer, sizeof(m_RecvBuffer),&m_lBytesRead,0,0);
			if(m_lBytesRead)
			{
			memset(m_RecvBuffer, 0, sizeof(m_RecvBuffer));  
			if(ReadFile(m_hReadPipe1,m_RecvBuffer,sizeof(m_RecvBuffer)-2,&m_lBytesRead,0))
			{
			if (m_RecvBuffer[sizeof(m_RecvBuffer)-3]&0x80)
			{
				if(!ReadFile(m_hReadPipe1,m_RecvBuffer+sizeof(m_RecvBuffer)-2,1,&dwRere,0))
					break;
			}
			XShellProcess_I In;
			In.Buffer=m_RecvBuffer;
			In.size=m_lBytesRead+dwRere;
			Recv(In);
			}
			}
			else
			{
			Sleep(300);
			}
		}
		else
		{
			Sleep(300);
		}
	}
}