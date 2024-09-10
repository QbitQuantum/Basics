/*---------------------------------------------------
	send SNTP data
---------------------------------------------------*/
void SNTPSend(HWND hwnd, unsigned long serveraddr)
{
	struct sockaddr_in serversockaddr;
	struct NTP_Packet NTP_Send;
	unsigned int sntpver;
	unsigned int Control_Word;

	// request notification of events
	if(WSAAsyncSelect(g_socket, hwnd, WSOCK_SELECT, FD_READ) == SOCKET_ERROR)
	{
		SocketClose(hwnd, "WSAAsyncSelect() failed");
		return;
	}

	// set IP address and port
	serversockaddr.sin_family = AF_INET;
	serversockaddr.sin_addr.s_addr = serveraddr;
	serversockaddr.sin_port = htons((unsigned short)g_port);
	memset(serversockaddr.sin_zero,(int)0,sizeof(serversockaddr.sin_zero));


	// init a packet
	memset(&NTP_Send, 0, sizeof(struct NTP_Packet));
	// NTP/SNTP version number = 4
	// Mode = 3 (client)
	// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	// |LI | VN  |Mode |    Stratum    |     Poll      |   Precision   |
	// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	sntpver = GetMyRegLong("SNTP", "SNTPVer", 4);
	Control_Word = (sntpver << 27) | (3 << 24);
	NTP_Send.Control_Word = htonl(Control_Word);

	// send a packet
	if(sendto(g_socket, (const char *)&NTP_Send, sizeof(NTP_Send), 0,
		(struct sockaddr *)&serversockaddr,
		sizeof(serversockaddr)) == SOCKET_ERROR)
	{
		SocketClose(hwnd, "sendto() failed");
		return;
	}


	// save tickcount
	dwTickCountOnSend = GetTickCount();
	bSendingData = TRUE;
}