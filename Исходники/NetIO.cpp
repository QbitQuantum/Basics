DWORD	tcp_connect(
						char *host, 

						WORD port)
{	
	DWORD	SockFD = 0;

	DWORD	nb_io = 1;

	DWORD	option = 0;

	struct	linger lin;

	struct	sockaddr_in DstSAin;

	BOOL	disable_nagle;

	
	DstSAin.sin_family = AF_INET;

	DstSAin.sin_port = htons(port);

	DstSAin.sin_addr.s_addr= inet_addr(host);	

	if((SockFD = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,0)) == INVALID_SOCKET)
	{

		if(NETIO_DEBUG)
		fprintf(stderr,

			"[%08X] Error: Unable to allocate socket\n"

		,WSAGetLastError());
	
		return(-1);
	}

	if((WSAConnect(SockFD,(struct sockaddr *)&DstSAin, sizeof(DstSAin),NULL,NULL,NULL,NULL)) == SOCKET_ERROR)
	{
		if(NETIO_DEBUG)
		fprintf(stderr,

			"[%08X] Error: Unable to connect to %s:%d\n"
		
		,WSAGetLastError(),host,port);

		closesocket(SockFD);
	
		return(-1);
	}

	if((ioctlsocket(SockFD,FIONBIO,&nb_io)) == SOCKET_ERROR)
	{
		if(NETIO_DEBUG)
		fprintf(stderr,
			
			"[%08X] Error: Unable to set IO mode of socket %d\n"
		
		,WSAGetLastError(),SockFD);
	
		closesocket(SockFD);

		return(-1);
	}

	lin.l_onoff = 1;

	lin.l_linger = 0;

	if((setsockopt(SockFD,SOL_SOCKET,SO_LINGER,(const char *)&lin,sizeof(lin))) == SOCKET_ERROR)
	{
		if(NETIO_DEBUG)
		fprintf(stderr,
			
			"[%08X] Error: Unable to set socket option SO_LINGER on socket %d\n"
		
		,WSAGetLastError(),SockFD);
		
		closesocket(SockFD);

		return(-1);
	}

	disable_nagle = TRUE;
		
	if((setsockopt(SockFD,IPPROTO_TCP,TCP_NODELAY,(const char *)&disable_nagle,sizeof(disable_nagle))) == SOCKET_ERROR)
	{
		if(NETIO_DEBUG)
		fprintf(stderr,
			
			"[%08X] Error: Unable to set socket option TCP_NODELAY on socket %d\n"
		
		,WSAGetLastError(),SockFD);
		
		closesocket(SockFD);
		
		return(-1);
	}

	return(SockFD);
}