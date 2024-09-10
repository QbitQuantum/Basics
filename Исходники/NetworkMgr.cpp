DWORD WINAPI CNetworkMgr::AcceptThread( void *pParam )
{
	CNetworkMgr *pNetworkSrv = (CNetworkMgr *)pParam;

	HANDLE	hComPort = pNetworkSrv->m_hCompPort;	//完成端口
	SOCKET	sListen = pNetworkSrv->m_socket;		//监听套接字

	SOCKET	sAccept = INVALID_SOCKET;				//接受客户端连接的套接字
	//sockaddr_in	addrClient;		//客户端SOCKET地址

	while ( pNetworkSrv->m_bRunning )
	{
		DWORD dwRet;
		dwRet = WSAWaitForMultipleEvents( 1, &pNetworkSrv->m_hEvent, FALSE, 100, FALSE );	//等待网络事件

		if ( !pNetworkSrv->m_bRunning )				//服务器停止服务
		{
			break;
		}

		if ( dwRet == WSA_WAIT_TIMEOUT )			//函数调用超时
		{
			continue;
		}

		WSANETWORKEVENTS events;
		int nRet = WSAEnumNetworkEvents( pNetworkSrv->m_socket, pNetworkSrv->m_hEvent, &events );

		if ( SOCKET_ERROR == nRet )
		{
			pNetworkSrv->ShowErrorMsg( "WSAEnumNetworkEvents() failed!\n" );
			break;
		}

		if ( events.lNetworkEvents & FD_ACCEPT )
		{
			if ( events.iErrorCode[FD_ACCEPT_BIT] == 0 && pNetworkSrv->m_bRunning)
			{
				sockaddr_in addrClient;
				int addrClientLen = sizeof( addrClient );
				sAccept = WSAAccept( sListen, (LPSOCKADDR)&addrClient, &addrClientLen, NULL, 0 );
				if ( INVALID_SOCKET == sAccept )
				{
					pNetworkSrv->ShowErrorMsg( "WSAAccept() failed!\n" );
					break;
				}

				CConnect *pConnect = new CConnect( sAccept, addrClient );

				if ( CreateIoCompletionPort( (HANDLE)sAccept, hComPort, (DWORD)pConnect, 0 ) == NULL )
				{
					return -1;
				}

				//加入管理客户端链表
				CConnectMgr *pConnectMgr = CConnectMgr::GetInstance();
				pConnectMgr->AddConnect( pConnect );
				if ( !pConnect->AsyncRecvHead() )
				{
					pConnectMgr->DeleteConnect( pConnect );
				}

			}
		}
		
	}

	//释放资源
	CConnectMgr *pConnectMgr = CConnectMgr::GetInstance();
	pConnectMgr->DeleteAllConnect();
	pConnectMgr->Release();

	//Sleep( 10000 );
	printf( "AcceptThread return\n" );

	return 0;
}