void GTcpClt_OnConnected(DWORD dwBytes, PGHND_DATA pClient, PGIO_DATA pIoData)
{
	setsockopt(pClient->Socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);
	pClient->hsState = GHND_STATE_CONNECTED;
	pClient->dwTickCountAcitve = GetTickCount();
	pClient->pfnOnIocpOper = &GTcpClt_OnReadWrite;
	pClient->pfnOnIocpError = &GTcpClt_OnReadWriteError;

	pfnOnGSockConnectClt((DWORD)pClient, pIoData->cData, dwBytes);

	ZeroMemory(pIoData, sizeof(WSAOVERLAPPED));
	DWORD dwCount = dwGSockNumberPostRecv;
	for(;;)
	{
		GIoDat_ResetIoDataOnRead(pIoData);
		pIoData->WSABuf.len = dwGSockRecvBytes;
		dwBytes = 0;
		DWORD dwFlag = 0;
		if((SOCKET_ERROR == WSARecv(pClient->Socket, &(pIoData->WSABuf), 1, &dwBytes, &dwFlag, LPWSAOVERLAPPED(pIoData), NULL)) &&
			(ERROR_IO_PENDING != WSAGetLastError()))
		{
			GTcpClt_OnReadWriteError(pClient, pIoData);
			return;
		}		
		dwCount--;
		if(!dwCount)
			return;
		pIoData = GIoDat_Alloc();
		if(!pIoData)
		{
			GLog_Write("GTcpClt_OnConnected：连接后，申请IoData失败");
			return;
		}
		pIoData->OperType = GIO_READ_COMPLETED;
		pIoData->pOwner = pClient;
	}
}