int OnDoorRequest(char *host_name, int host_port, char *pData, int nDataSize)
{
	/*
	SOCKADDR_IN		saServer;
	LPHOSTENT		lphostent;
	WSADATA			wsadata;
	SOCKET			hsocket;
	*/
	char             		ipaddr[16];
    int                     rsocket = -1;
    struct sockaddr_in      daddr;
    struct timeval          TimeOut;
    int 					nFlag;

	int						nRet;

	memset( ipaddr, 0x00, 16 );


#if	1
    //nRet = GetDnsIp( host_name, ipaddr );
	//Textout("Server = [%s], IPADDR = [%s]", host_name, ipaddr);
	
	//ipaddr[0] = 0;
#else
	strcpy(ipaddr, "183.232.25.234");
#endif

	if(jpush_address[0] != 0){
		strcpy(ipaddr, jpush_address);
	}
	else
	{
		strcpy(ipaddr, "183.232.25.234");
	}
	Textout("jpush ipaddr:%s",ipaddr);
	
    rsocket = InitSocket( 0, 1, NULL );             //tcp
    nFlag = 1;
    setsockopt( rsocket, IPPROTO_TCP, TCP_NODELAY, ( void* )&nFlag, sizeof( int ) );
    TimeOut.tv_sec = 30;
    TimeOut.tv_usec = 0;
    setsockopt( rsocket, SOL_SOCKET, SO_RCVTIMEO, ( char* )&TimeOut, sizeof( TimeOut ) );
    TimeOut.tv_sec = 30;
    TimeOut.tv_usec = 0;
    setsockopt( rsocket, SOL_SOCKET, SO_SNDTIMEO, ( char* )&TimeOut, sizeof( TimeOut ) );
    bzero( &daddr, sizeof( struct sockaddr_in ) );

	daddr.sin_family        = AF_INET;
    daddr.sin_port          = htons(host_port);
    daddr.sin_addr.s_addr   = inet_addr( ipaddr );


	nRet = connect( rsocket, ( struct sockaddr* )&daddr, sizeof( struct sockaddr ) );
	if(nRet == -1)	//SOCKET_ERROR)
	{
		Textout( "Can't connect %s",host_name);
        CloseSocket( rsocket );
		return -1;
	}
	else
	{

		Textout("connected   with host %s",host_name);
	}

	nRet = send(rsocket, pData, nDataSize, 0);
	if(nRet == -1)	//SOCKET_ERROR)
	{
		Textout( "Can't Send");
        CloseSocket( rsocket );
		return -1;
	}
	else
	{
		Textout("send() OK");
		//Textout("pData:%s",pData);
	}

	char   dest[1024];
	nRet=0;
	
	nRet=recv(rsocket,(char *)dest,sizeof(dest),0);
	
	if(nRet>0)
	{
		dest[nRet]=0;

		

		if(strstr(dest,"Succeed") == NULL )
		{
			nRet = -1;
			Textout("Received bytes:%d",nRet);
			printf("Result:%s\n",dest);
		}
		else
		{
			printf("jPush send Succeed!\n");
			nRet = 0;
		}
	}
	else
	{
		printf("jPush not recv data! ");
		dest[0]=0;
		nRet = -1;
	}

	CloseSocket(rsocket);
	return nRet;
}