int CServerApp::PollThread( void* arg )
{
	CServerApp* pServApp = (CServerApp*)arg;
	ASSERT( pServApp!=NULL );

	//start the poll server and bind to specific port.
	SOCKET socksrv = Socket( PF_INET, SOCK_DGRAM, 0 );
	SOCKADDR_IN srvaddr;
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons( NCP_SERVER_PING_PORT );
	srvaddr.sin_addr.s_addr = INADDR_ANY;
	Bind( socksrv, (SOCKADDR*)&srvaddr, sizeof(SOCKADDR_IN) );
	socklen_t len = sizeof(SOCKADDR_IN);
	getsockname( socksrv, (SOCKADDR*)&srvaddr, &len );

#ifdef _WIN32
	SetUdpBlock( socksrv );
#endif

	CMessageHead msg;
	if( pServApp->IsProxy() ){
//		pServApp->DoPoll( socksrv );
		msg.Init( NCM_POLLSERVER, CSessionAddr(), CSessionAddr(), NCP_SERVER_PING_PORT );
	}else if( pServApp->IsServer() ){
		msg.Init( NCM_SERVERSTART, CSessionAddr(), CSessionAddr() );
//		msg.Init( NCM_POLLSERVER, CSessionAddr(), CSessionAddr() );
	}
	if( pServApp->IsProxy() || pServApp->IsServer() ){
		SOCKET sockbroad = Socket( PF_INET, SOCK_DGRAM, 0 );
//		msg.Broadcast( sockbroad, NCP_SERVER_PING_PORT );
		closesocket( sockbroad );
	}

	while( true ){
		fd_set rfds;
		FD_ZERO( &rfds );
		FD_SET( socksrv, &rfds );
		int maxfds = socksrv + 1;

		TIMEVAL tmout, *pto;
		if( pServApp->IsProxy() ){
			tmout.tv_sec = 10;
			tmout.tv_usec = 0;
			pto = &tmout;
		}else pto = NULL;

		int nRet = Select( maxfds, &rfds, NULL, NULL, pto );

		if( nRet==0 ){	//select timeout, should I do a poll for the remote hosts?
			if( pServApp->IsProxy() )pServApp->DoPoll( socksrv );
		}else if( FD_ISSET(socksrv, &rfds) ){
			SOCKADDR_IN srcaddr;
			CMessageHead* pMsg = RecvMsgFrom( socksrv, srcaddr );
			CMessageTrash trash(pMsg);
			cdump<<inet_ntoa(srcaddr.sin_addr)<<" with message id:"<<pMsg->GetMessage()<<endl;
			if( pMsg->GetMessage()==NCM_POLLSERVER ){
				unsigned short sPort = htons( (short)pMsg->GetResult() );
				if( !( (srcaddr.sin_addr==pServApp->GetAddr().m_addrHost)&&(sPort==srvaddr.sin_port) ) ){
					srcaddr.sin_port = htons( (short)pMsg->GetResult() );
					pServApp->AckPoll( socksrv, srcaddr );
				}
			}else if( pMsg->IsAcking(NCM_POLLSERVER) ){			//the server is acking our poll
				if( !(pServApp->GetAddr().m_addrHost==srcaddr.sin_addr) )pServApp->OnAckPoll( pMsg );
			}else if( pMsg->GetMessage()==NCM_SERVERSTART ){	//the server is starting, poll the server
				if( pServApp->IsProxy() && !(pServApp->GetAddr().m_addrHost==srcaddr.sin_addr) ){
					CMessageHead msg;
					msg.Init( NCM_POLLSERVER, CSessionAddr(), CSessionAddr(), NCP_SERVER_PING_PORT );
					srcaddr.sin_port = htons( NCP_SERVER_PING_PORT );
					msg.SendTo( socksrv, srcaddr );
				}
			}
		}
	}
	closesocket( socksrv );

	return 0;
}