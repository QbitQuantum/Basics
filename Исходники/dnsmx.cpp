BOOL GetMX (
			char *pszQuery,
			char *pszServer,
			OUT t_Ary_MXHostInfos &Ary_MXHostInfos
			)
{
	SOCKET                  hSocket;
	SOCKADDR_IN             stSockAddr;                     // socket address structures
	int                             nAddrLen = sizeof( SOCKADDR_IN );
	
	HOSTENT                 *pHostEnt;
	
	char                            achBufOut[ BUFSIZE ] = { 0 };
	char                            achBufIn[ BUFSIZE ] = { 0 };
	int                             nQueryLen = 0;
	int                             nRC;
	
	char *p, *np, name[128], *eom;
	int count, j, i, n;
	
	memset( &stSockAddr, ASCII_NULL, sizeof( stSockAddr ) );
	
	stSockAddr.sin_family      = AF_INET;
	stSockAddr.sin_port             = htons( 53);
	stSockAddr.sin_addr.s_addr = inet_addr( pszServer );
	if ( stSockAddr.sin_addr.s_addr == INADDR_NONE )
	{
		pHostEnt = gethostbyname( pszServer );
		if ( pHostEnt )
		{
			stSockAddr.sin_addr.s_addr = *((ULONG *)pHostEnt->h_addr_list[0]);
		}
		else
		{
			return FALSE;
		} // end if
	} // end if
	
	
	  /*------------------------------------------------------------
	  *  Get a DGRAM socket
	*/
	
	hSocket = socket( AF_INET, SOCK_DGRAM, 0 );
	
	if ( hSocket == INVALID_SOCKET )
	{
		return FALSE;
	} // end if

	  /*-----------------------------------------------------------
	  * Format DNS Query
	*/
	
	pDNShdr = (PDNS_HDR)&( achBufOut[ 0 ] );
	pDNShdr->dns_id         = htons( 0xDEAD );
	pDNShdr->dns_flags      = htons( DNS_FLAG_RD ); // do recurse
	pDNShdr->dns_q_count    = htons( 1 );           // one query
	pDNShdr->dns_rr_count   = 0;                  // none in query
	pDNShdr->dns_auth_count = 0;                  // none in query
	pDNShdr->dns_add_count  = 0;                  // none in query
	
	nQueryLen = PutQName( pszQuery, &(achBufOut[ DNS_HDR_LEN ] ) );
	nQueryLen += DNS_HDR_LEN;
	
	achBufOut[ nQueryLen++ ]        = 0;
	achBufOut[ nQueryLen++ ]        = 0;	
	achBufOut[ nQueryLen ]          = DNS_RRTYPE_MX;
	achBufOut[ nQueryLen + 1 ]      = 0;
	achBufOut[ nQueryLen + 2 ]      = DNS_RRCLASS_IN;
	achBufOut[ nQueryLen + 3 ]      = 0;
	
	nQueryLen += 4;
	
	/*-----------------------------------------------------------
	* Send DNS Query to server
	*/
	
	nRC = sendto( hSocket,
		achBufOut,
		nQueryLen,
		0,
		(LPSOCKADDR)&stSockAddr,
		sizeof( SOCKADDR_IN ) );
	
	if ( nRC == SOCKET_ERROR )
	{
		
		closesocket( hSocket );
		return FALSE;
	}
	else
	{
		
	}
	
//	VERIFY ( SetBlockingMode ( hSocket, TRUE ) );

	// 用 select 模型实现连接超时
	struct timeval timeout;
	fd_set r;
	FD_ZERO(&r);
	FD_SET(hSocket, &r);
	timeout.tv_sec = 5; //连接超时秒
	timeout.tv_usec =0;
	int ret = select(0, &r, 0, 0, &timeout);
	if ( ret == SOCKET_ERROR )
	{
		::closesocket(hSocket);
		hSocket = SOCKET_ERROR;
		return FALSE;
	}

	// 得到可读的数据长度
	long cmd = FIONREAD;
	u_long argp = 0;
	BOOL err = ioctlsocket ( hSocket, cmd, (u_long*)&argp );
	if ( err || argp < 1 )
	{
		::closesocket(hSocket);
		hSocket = SOCKET_ERROR;
		return FALSE;
	}

	nRC = recvfrom( hSocket,
		achBufIn,
		BUFSIZE,
		0,
		(LPSOCKADDR)&stSockAddr,
		&nAddrLen );
	
	if ( nRC == SOCKET_ERROR )
	{
		int nWSAErr = WSAGetLastError();
		
		if ( nWSAErr != WSAETIMEDOUT )
		{
			
			closesocket( hSocket );
			return FALSE;
		}
		else
		{
			
			closesocket( hSocket );
			return FALSE;
		}
	}
	else
	{
		pDNShdr = (PDNS_HDR)&( achBufIn[ 0 ] );
		p = (char *)&pDNShdr[0];
		p+=12;
		count = (int)*p;
		
		// Parse the Question...
		for (i = 0; i< ntohs(pDNShdr->dns_q_count); i++)
		{
			np = name;
			eom = (char *)pDNShdr+nRC;
			
			if ( (n = dn_expand((char *)pDNShdr, eom, p, name, 127)) < 0 )
			{
				return FALSE;
				
			}
			p += n + QFIXEDSZ;
		}		
		
		for (i = 0; i< ntohs(pDNShdr->dns_rr_count); i++)
		{
			
			// The Question Name appears Again...
			if ((n = dn_expand((char *)pDNShdr, eom, p, name, 127)) < 0)
			{
				return FALSE;
			}
			p+=n;
			
			
			j =  _getshort(p);;  //TYPE
			p+=2;
			//printf("%s\tType:%d", name, j);
			
			j = _getshort(p);  //CLASS
			p+=2;
			//	printf("\tClass:%d", j);
			
			j = _getlong(p);  //TTL
			p+=4;
			//	printf("\tTTL:%d", j);
			
			j = _getshort(p);  //RDLENGTH
			p+=2;
			//	printf("\tRDLENGTH:%d", j);
			
			j = _getshort(p);  //N??
			p+=2;
			
			// This should be an MX Name...
			if ( (n = dn_expand((char *)pDNShdr, eom, p, name, 127)) < 0 )
			{
				return FALSE;
			}

			t_MXHostInfo tMXHostInfo = {0};
			strncpy ( (char*)tMXHostInfo.szMXHost, name, _countof(tMXHostInfo.szMXHost));
			tMXHostInfo.N = j;
			Ary_MXHostInfos.Add ( tMXHostInfo );
			TRACE ( _T("%s\t%d\r\n"), name, j );
			p += n;
		}
		return TRUE;
		
		
	}
	
	
	closesocket( hSocket );
	return FALSE;
}