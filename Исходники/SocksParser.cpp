BOOL SocksParser::GetRequest( SERVICE_INFO& svc )
{
	/*
	 +----+-----+-------+------+----------+----------+
	  |VER | CMD |  RSV  | ATYP | DST.ADDR | DST.gListenSocket |
	  +----+-----+-------+------+----------+----------+
	  | 1  |  1  | X'00' |  1   | Variable |    2     |
	  +----+-----+-------+------+----------+----------+
	*/
	char buffer[1024];
	sockaddr_in svr = {0};

	if(!RecvBuf(svc.socket,buffer,10))
		return FALSE;

	switch (buffer[1])
	{
		case 0x01:
			svc.type = SOCKS_CONNECT;
			break;
		case 0x02:
			svc.type = SOCKS_BIND;
			break;
		case 0x03:
			svc.type = SOCKS_UDP;
			break;
	}
		
	//需要连接一个IP
	if (buffer[3] == 0x01)
	{
		infoLog(_T("THE DESTINATION IP : %d.%d.%d.%d "),\
			buffer[4]&0xff,buffer[5]&0xff,buffer[6]&0xff,buffer[7]&0xff) ;

		infoLog(_T("THE DESTINATION PORT : %d"),((int)buffer[8])*256 + (unsigned char)buffer[9]);

		svr.sin_family = AF_INET;
		svr.sin_port = htons(((int)buffer[8])*256 + (unsigned char)buffer[9]);
		svr.sin_addr.s_addr =
			MAKELONG(MAKEWORD((buffer[4]&0xff),(buffer[5]&0xff)),
			MAKEWORD((buffer[6]&0xff),(buffer[7]&0xff))) ;
	}

		//需要连接一个域名
	else if (buffer[3] == 0x03)
	{
		int i = 0;
		int NameSize = buffer[4]&0xff;

		//接收域名
		if (NameSize >= 6)
			RecvBuf(svc.socket,&buffer[4]+6,NameSize-5);

		char szName[100];

		for (i = 0;i < NameSize;++i)
			szName[i] = buffer[i+5];

		szName[i] = 0;
		infoLog(_T("The disire DomainName : %s"),a2t(szName));

		svr.sin_family = AF_INET;


		//请求DNS
		svr.sin_addr = GetName(szName);

		//如果请求DNS失败
		if (svr.sin_addr.s_addr == 0)
		{
			errorLog(_T("QUERY DNS Error"));
			return FALSE;
		}

		i += 5;
		//接收端口号
		infoLog(_T("The disire IP :%s"),a2t(inet_ntoa(svr.sin_addr)));

		RecvBuf(svc.socket,&buffer[i],2);

		infoLog(_T("The destination port : %d"),(buffer[i]&0xff)*256 + (unsigned char)buffer[i+1]);

		svr.sin_port = htons((buffer[i]&0xff)*256 + (unsigned char)buffer[i+1]);
	}

	//设置sockaddr_in
	svc.saddr = svr;
	svc.slocal = svc.socket;

	if (svc.type == SOCKS_UDP)
	{
		svc.caddr = svr;

		sockaddr_in addr;
		socklen_t size = sizeof(addr);

		svc.usocket = Socket::Create(FALSE);

		getpeername(svc.socket,(sockaddr*)&addr,&size);
		svc.caddr.sin_addr = addr.sin_addr;

	}
	else if (svc.type == SOCKS_CONNECT)
	{
		svc.sremote = Create();
	}
	else if (svc.type == SOCKS_BIND)
	{
		svc.slocal = Create();

		if (!Socket::Bind(svc.slocal,svc.sq,svc.saddr))
		{
			return FALSE;
		}
	}
	return TRUE;
}