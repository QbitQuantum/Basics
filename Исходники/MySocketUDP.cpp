BOOL MySocketUDP::Broadcast(CHAR * pData, UINT nLen, USHORT uPort)
{
	SOCKADDR_IN addrin = {0};
	addrin.sin_family = AF_INET;
	addrin.sin_port = htons(uPort);
	addrin.sin_addr.S_un.S_addr = ::htonl( INADDR_BROADCAST );

	//设置广播模式
	BOOL bBroadcast = TRUE;
	int iRet = ::setsockopt( m_uSocket, SOL_SOCKET, SO_BROADCAST,
		(char *)&bBroadcast,sizeof( bBroadcast ) );
	if(SOCKET_ERROR == iRet)
	{
		return FALSE;
	}

	BOOL bRet = SendTo(pData, nLen, &addrin);

	//设置非广播模式
	bBroadcast = FALSE;
	iRet = ::setsockopt( m_uSocket, SOL_SOCKET, SO_BROADCAST,
		(char *)&bBroadcast,sizeof( bBroadcast ) );
	if(SOCKET_ERROR == iRet)
	{
		//Create();
	}

	return bRet;
}