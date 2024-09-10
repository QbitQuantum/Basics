sp_thread_result_t SP_THREAD_CALL SP_IocpServer :: acceptThread( void * arg )
{
	DWORD recvBytes = 0;

	SP_IocpAcceptArg_t * acceptArg = (SP_IocpAcceptArg_t*)arg;
	
	for( ; ; ) {
		acceptArg->mClientSocket = (HANDLE)WSASocket( AF_INET, SOCK_STREAM,
				IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED );
		if( INVALID_SOCKET == (int)acceptArg->mClientSocket ) {
			sp_syslog( LOG_ERR, "WSASocket fail, errno %d", WSAGetLastError() );
			Sleep( 50 );
			continue;
		}

		SP_IOUtils::setNonblock( (int)acceptArg->mClientSocket );
		memset( &( acceptArg->mOverlapped ), 0, sizeof( OVERLAPPED ) );

		BOOL ret = AcceptEx( (SOCKET)acceptArg->mListenSocket, (SOCKET)acceptArg->mClientSocket,
				acceptArg->mBuffer,	0, sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16,
				&recvBytes, &( acceptArg->mOverlapped ) );

		int lastError = WSAGetLastError();
		if( FALSE == ret && (ERROR_IO_PENDING != lastError) ) {
			sp_syslog( LOG_ERR, "AcceptEx() fail, errno %d", lastError );
			closesocket( (int)acceptArg->mClientSocket );
			if( WSAENOBUFS == lastError ) Sleep( 50 );
		} else {
			WaitForSingleObject( acceptArg->mAcceptEvent, INFINITE );
			ResetEvent( acceptArg->mAcceptEvent );
		}
	}

	return 0;
}