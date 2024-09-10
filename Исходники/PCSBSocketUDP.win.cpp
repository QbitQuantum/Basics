long PCSBSocketUDP::ReadData(
				void * 				outBuf,
				long				outBufLength,
				unsigned long *		outSrcIP,
				unsigned short *	outSrcPort)
{
	SOCKADDR_IN remoteAddress;
	int fromlen = sizeof(remoteAddress);
	remoteAddress.sin_family = AF_INET;
	remoteAddress.sin_port = 0;
	remoteAddress.sin_addr.S_un.S_addr = 0;
	
	WSASetLastError(0);
	int result = recvfrom(mWinSocket, 
						 (char*)outBuf, 
						 outBufLength,
						 0,
						 (SOCKADDR*)&remoteAddress,
						 &fromlen);
		
	*outSrcIP = ntohl(remoteAddress.sin_addr.S_un.S_addr);
	*outSrcPort = ntohs(remoteAddress.sin_port);
	
	if (result == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return -1;
		}
	}
	else
	{
		return result;
	}
	return result;
}