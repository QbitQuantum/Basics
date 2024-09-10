//nTimeOut 单位S
int Connect( SOCKET sk, char* remote, int port, int nTimeOut )
{	
	//设置非阻塞方式连接
	unsigned long ul = 1;  //“无符号长整形“非零值， 启用非锁定模式
	
	//ioctlsocket 控制套接口的模式。  FIONBIO：允许或禁止套接口的非阻塞模式。
	if ( ioctlsocket(sk, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR )
		return SOCKET_ERROR;
	
	//SOCKADDR_IN dvr;
	//dvr.sin_family		= AF_INET;
	//dvr.sin_port		= htons((unsigned short)port);
	
	//dvr.sin_addr.s_addr	= inet_addr(addr);
	
	SOCKADDR_IN saServer;
	memset( &saServer, 0x00, sizeof(saServer) );
	saServer.sin_family		= AF_INET;
	LONG lIPAddress = 0;
	if( isalpha(remote[0]) )
	{
		hostent *hostEnt = gethostbyname( remote );	
		if( hostEnt != NULL )
		{
			lIPAddress = ((in_addr*)hostEnt->h_addr)->s_addr;
			saServer.sin_addr.s_addr = lIPAddress;
		}
	}	
    else
    {
		saServer.sin_addr.s_addr = inet_addr( remote );
    }
	saServer.sin_port		= htons((unsigned short)port);
	
	if ( connect( sk, (SOCKADDR*)&saServer, sizeof( saServer ) ) == SOCKET_ERROR )
	{
		DWORD dwError = WSAGetLastError();
		
		if ( dwError != WSAEWOULDBLOCK )
			return SOCKET_ERROR;
	}
	
	//检索套接字是否接受到数据.若无,则ret<=0,即自动在fdconn中删除了该套接字
	
	struct timeval tv ;	
	fd_set fdconn;	
	FD_ZERO(&fdconn);  //初始化为空集合	
	FD_SET(sk, &fdconn);  //将套接字句柄传入fdconn	
	tv.tv_sec = nTimeOut;   //等待时间， 秒	
	tv.tv_usec = 0;     //毫秒
	
	int ret = select(0, 0, &fdconn, 0, &tv);	
	if ( ret <= 0 )
	{
		//closesocket(sk);
		return SOCKET_ERROR;
	}
	
	//设回阻塞模式
	ul = 0 ; //0为阻塞模式
	
	ret = ioctlsocket( sk, FIONBIO, (unsigned long*) & ul );
	
	if ( ret == SOCKET_ERROR )
	{
		closesocket(sk);
		return SOCKET_ERROR;
	}
	return 0;
}