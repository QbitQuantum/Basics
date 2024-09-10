DWORD WINAPI RecvUDPPack(PVOID)
{
	DWORD dFlag, cbRet;
	int iLen;
	int nRet;
	char achInBuf [BUFSIZE]="";
	WSABUF stWSABuf;
	while(!g_bStop)
	{
		stWSABuf.buf = achInBuf;
		stWSABuf.len = BUFSIZE;
		cbRet = 0;
		iLen = sizeof(g_stSrcAddr);
		dFlag = 0;

		nRet = WSARecvFrom(g_hSock,&stWSABuf,1,&cbRet,&dFlag,(struct sockaddr *)&g_stSrcAddr,&iLen,NULL,NULL);
		if(nRet == SOCKET_ERROR)
		{
			printf("WSARecvFrom() failed, Err:%d\n", WSAGetLastError());
		}
		else 
		{
			g_poMem->InsertUDPData(*(UDP_PACK *)stWSABuf.buf);
        }
	}
	return 0;
}