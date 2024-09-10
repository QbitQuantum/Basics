bool CServerSocket::AcceptCompleted( CSocketBuffer * pBuffer, DWORD dwReceiveByte )
{

	bool bRet ;
	// Accept 가 완료되면.
	if( pBuffer && pBuffer->IsConnected() )
	{
		pool_lock() ;
		try{
			pBuffer->m_bAccepted = true ;
		}
		catch (...) {
			::PrintConsole("[exception] %s, %d \n", __FILE__, __LINE__ ) ;
		}		
		pool_unlock() ;

		
		::InterlockedDecrement( &m_nCurPendingAccept ) ;
	
		//SetEvent( m_hAcceptPostEvent ) ;

		int nEstablishedSeconds = 0;		
		int bytes = sizeof(nEstablishedSeconds);		
		int err = ::getsockopt(pBuffer->socket, SOL_SOCKET, SO_CONNECT_TIME, (char*)&nEstablishedSeconds, &bytes);
		if (nEstablishedSeconds == 0xffffffff)
		{			
			//  현재 연결되지 않은 넘
			::PrintConsole( "[ERROR] Dissconnected socket \n") ;
			return false ;
		}		
		else			
		{
			// nEstablishedSeconds --> 커넥션 이루어진 때로부터 현재까지 경과한 초단위 시간			
		}


		if( SOCKET_ERROR == ::setsockopt( pBuffer->socket, SOL_SOCKET, 
			SO_UPDATE_ACCEPT_CONTEXT, (char*)&m_listensocket, sizeof(m_listensocket) ) ) 
		{
			::PrintConsole( "CServerSocket::AcceptCompleted setsockopt failed - Code %d\n", ::WSAGetLastError() ) ;
		}
		

		// 주소를 채우고, 
		//
		int sizeofLocal=0, sizeofRemote = 0 ;
		SOCKADDR * pLocal = NULL, * pRemote = NULL ;

		GetAcceptExSockaddrs( pBuffer->m_buf, 0, m_sizeofaddr, m_sizeofaddr, 
			&pLocal, &sizeofLocal, &pRemote, &sizeofRemote ) ;

		if( pRemote )
		{
			::CopyMemory( &pBuffer->addr, pRemote, sizeof(SOCKADDR) ) ;

			//printf( "Ip = %s\n", inet_ntoa( pBuffer->addr.sin_addr ) ) ;
		}

		tcp_keepalive keepAlive, outKeepAlive = {0};
		DWORD	outByte ;
		
		keepAlive.onoff = 1 ;
		keepAlive.keepaliveinterval = _KEEPALIVE_INTERVAL_ ;
		keepAlive.keepalivetime = _KEEPALIVE_TIME_ ;
		WSAIoctl( pBuffer->socket, SIO_KEEPALIVE_VALS, &keepAlive, sizeof(keepAlive), &outKeepAlive, sizeof(outKeepAlive), &outByte, NULL, NULL ) ;

		


		// completion port 와 연결한다..
		/*
		if( m_iocp.AssociateSocket( pBuffer ) == false )
		{
			int iError = WSAGetLastError() ;
			::PrintConsole( " m_iocp.AssociateSocket( pBuf ) == false (err_code :%d)\n", iError ) ;			
		}
		*/

		//OnConnectionEstablished( pBuffer ) ;
		bRet = true ;
	
	}
	else
	{
		::PrintConsole("[ERROR] if( pBuffer && pBuffer->IsConnected() == false ) \n" ) ;
		bRet = false ;
		
	}

	return bRet ;
}