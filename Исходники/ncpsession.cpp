int CClientSession::DoPutFile( const char* strSrc, const char* strDst, bool bOverwrite )
{
	char buf[MAXPATH+sizeof(CNcpMessage)];
	CNcpMessage* pMsg = (CNcpMessage*)buf;

	if( !IsFileExist( strSrc ) ){
		return E_NOENT;
	}

	//step 1. request passive mode to get the data channel address
	unsigned short dataport = 0;

	int nRet = DoPassive( (short*)&dataport );
	if( FAILED(nRet) )return nRet;

	//step 2. send the put file command.
	pMsg->Init( CM_PUTFILE );
	pMsg->m_nParamRet = bOverwrite;
	strcpy( pMsg->GetData(), strDst );
	pMsg->SetDataSize( strlen(strDst)+1 );

	pMsg->Send( m_sock );

	//wait for the return code and check it
	if( !pMsg->Recv( m_sock, ELEMENTS(buf) ) ){
		return E_BROKEN;		//broken connection
	}

	ASSERT( pMsg->IsAck() );
	if( pMsg->IsFailed() || pMsg->m_nParamRet==S_EXIST ){
		return pMsg->GetRet();
	}

	//step 3. now the server agrees on the file transfer, connect the data channel and send file
	SOCKADDR_IN addr;
	socklen_t nlen = sizeof(SOCKADDR_IN);
	GetPeerName( m_sock, (SOCKADDR*)&addr, &nlen );
	addr.sin_port = htons( dataport );

	SOCKET sockdata;
	//import, must retry the socket initilization a few times. 
	for( int i=0; i<MAXRETRY; i++ ){
		sockdata = Socket( PF_INET, SOCK_STREAM, 0 );
		ASSERT( sockdata!=INVALID_SOCKET );

		if( ::connect( sockdata, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN) )==0 )break;
		closesocket( sockdata );
	}
	if( i>=MAXRETRY )throw new CSockException();

/*	for( int i=0; i<5; i++ ){
		sockdata = Socket( PF_INET, SOCK_STREAM, 0 );
		ASSERT( sockdata!=INVALID_SOCKET );

		struct hostent * phent = gethostbyaddr( (char*)&addr.sin_addr, sizeof(IN_ADDR), AF_INET );
		cdump<<lock<<(int)sockdata<<" connecting data channel at "<<phent->h_name<<"("<<addr.sin_addr.S_un.S_addr<<","<<dataport<<"), "<<endl<<unlock;
		if( ::connect( sockdata, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN) )==0 ){
			break;
		}

		cdump<<lock<<phent->h_name<<" connect failed "<<i<<"\t error:"<<WSAGetLastError()<<endl<<unlock;
		closesocket( sockdata );
	}

	if( i<5 ){
		cdump<<lock<<"connected!"<<endl<<unlock;
	}else{
		throw new CSockException();
	}*/

/*	SOCKET sockdata;
	sockdata = Socket( PF_INET, SOCK_STREAM, 0 );
	ASSERT( sockdata!=INVALID_SOCKET );

	for( int i=0; i<5; i++ ){
		struct hostent * phent = gethostbyaddr( (char*)&addr.sin_addr, sizeof(IN_ADDR), AF_INET );
		cdump<<lock<<(int)sockdata<<" connecting data channel at "<<phent->h_name<<"("<<addr.sin_addr.S_un.S_addr<<","<<dataport<<"), "<<endl<<unlock;
		int nrt = 0;
		if( (nrt=::connect( sockdata, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN) ))==0 ){
			break;
		}
		cdump<<lock<<phent->h_name<<" connect failed "<<i<<"\t error:"<<nrt<<","<<WSAGetLastError()<<endl<<unlock;

		closesocket( sockdata );
		Sleep( 1000*10*(i+1) );

		sockdata = Socket( PF_INET, SOCK_STREAM, 0 );
		ASSERT( sockdata!=INVALID_SOCKET );
	}
	if( i>=5 ){
		struct hostent * phent = gethostbyaddr( (char*)&addr.sin_addr, sizeof(IN_ADDR), AF_INET );
		cdump<<lock<<"connecting data channel at "<<phent->h_name<<"("<<addr.sin_addr.S_un.S_addr<<","<<dataport<<"), "<<endl<<unlock;
		::Connect( sockdata, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN) );
	}
	cdump<<lock<<"connected!"<<endl<<unlock;*/

//	struct hostent * phent = gethostbyaddr( (char*)&addr.sin_addr, sizeof(IN_ADDR), AF_INET );
//	cdump<<lock<<"connecting data channel at "<<phent->h_name<<"("<<addr.sin_addr.S_un.S_addr<<","<<dataport<<"), "<<unlock;
//	::Connect( sockdata, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN) );
//	cdump<<lock<<"connected!"<<endl<<unlock;

	int nLen = SendFileEx( sockdata, strSrc, m_nFileMode );
	closesocket( sockdata );

	//step 4. exchange the error code.
	pMsg->Init( CM_ACK, nLen );
	pMsg->Send( m_sock );

	//wait for the return code and check it
	if( !pMsg->Recv( m_sock, ELEMENTS(buf) ) ){
		return E_BROKEN;		//broken connection
	}

	ASSERT( pMsg->IsAck() );
	return pMsg->GetRet();
}