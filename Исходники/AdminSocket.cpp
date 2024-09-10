BOOL CAdminSocket::Init()
{
	char *buffer=new char[100];
	char *p=buffer;
	strcpy(buffer, "FZS");
	p+=3;

	*p++=0;
	*p++=4;
	memcpy(p, &SERVER_VERSION, 4);
	p+=4;
	
	*p++=0;
	*p++=4;

	memcpy(p, &PROTOCOL_VERSION, 4);
	p+=4;

	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	int nSockAddrLen = sizeof(sockAddr);
	
	if (GetPeerName((SOCKADDR*)&sockAddr, &nSockAddrLen) && sockAddr.sin_addr.S_un.S_addr == 0x0100007f)
	{
		BOOL res=Send(buffer, p-buffer) == p-buffer;
		delete [] buffer;
		if (!res)
		{
			Close();
			return FALSE;
		}
		return FinishLogon();		
	}
	else
	{
		*p++=0;
		
		DWORD len = 20;
		memcpy(p, &len, 4);
		p+=4;

		*p++=0;
		*p++=8;
		
		int i;
		for (i=0;i<8; i++)
		{
			m_Nonce1[i]=(rand()*256)/(RAND_MAX+1);
			*p++=m_Nonce1[i];
		}
		
		*p++=0;
		*p++=8;
		
		for (i=0;i<8; i++)
		{
			m_Nonce2[i]=(rand()*256)/(RAND_MAX+1);
			*p++=m_Nonce2[i];
		}
	}

	int res=Send(buffer, p-buffer) == p-buffer;
	delete [] buffer;
	return res;
}