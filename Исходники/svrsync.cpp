UINT __stdcall CSvrSyncPlug::UdpThread(LPVOID lpVoid)
{
	CSvrSyncPlug* pThis = reinterpret_cast<CSvrSyncPlug*>(lpVoid);

	SOCKET sck = socket(AF_INET, SOCK_DGRAM, 0);
	if (sck == INVALID_SOCKET)
		return 0;
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port	= htons(5000);
	addr.sin_addr.s_addr = ADDR_ANY;
	if (SOCKET_ERROR == bind(sck, (PSOCKADDR)&addr, sizeof(addr)))
	{
		closesocket(sck);
		return 0;
	}
	int RecvBufSize = 0x10000;
	setsockopt(sck,SOL_SOCKET, SO_RCVBUF,	(char*)&RecvBufSize, sizeof(int) );
	setsockopt(sck,SOL_SOCKET, SO_SNDBUF,	(char*)&RecvBufSize, sizeof(int) );
	WSAEVENT hNetEvent = WSACreateEvent();
	if (hNetEvent == NULL || SOCKET_ERROR == WSAEventSelect(sck, hNetEvent, FD_READ))
	{
		closesocket(sck);
		return 0;
	}
	
	HANDLE hEvents[2] = {pThis->m_hExited, hNetEvent};
	while (1)
	{
		DWORD ret = WSAWaitForMultipleEvents(_countof(hEvents), hEvents, FALSE,WSA_INFINITE, FALSE);
		if (ret == WAIT_OBJECT_0)
			break;
		else if (ret == WAIT_OBJECT_0 + 1)
		{
			WSANETWORKEVENTS NetworkEvents;
			WSAEnumNetworkEvents(sck, hNetEvent, &NetworkEvents);
			if(NetworkEvents.lNetworkEvents == FD_READ && NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
			{
				char data[4096] = {0};
				pkgheader* pheader = (pkgheader*)data;
				int len = recvfrom(sck, data, sizeof(data), 0, NULL, NULL);
				if (len > 0 && pheader->Length == len)
				{
					data[len] = 0;
					try {  pThis->UdpProcess(data, len); }  catch (...) {}
				}
			}
		}
		else break;
	}
	closesocket(sck);
	WSACloseEvent(hNetEvent);
	return 0;
}