int WAsyncSocket::Connect(char *host,unsigned int port)
{
	m_port=port;

	// Check to see if we need to get the ip address from the host address
	bool is_ip_string=false;
	unsigned int ip_int[4];
	if(sscanf(host,"%u.%u.%u.%u",&ip_int[0],&ip_int[1],&ip_int[2],&ip_int[3])==4)
	{
		is_ip_string=true;
	}
	
	// If this is not an ip string we are connecting to, then resolve the hosts ip address from the DNS
	if(is_ip_string==false)
	{
		WSAAsyncGetHostByName(m_hwnd,WM_GOT_HOST_BY_NAME_MESSAGE,host,m_hostent_buf,sizeof(m_hostent_buf));
	}
	else	// it is just an IP
	{
		unsigned long ip_addr=inet_addr(host);
		WSAAsyncGetHostByAddr(m_hwnd,WM_GOT_HOST_BY_ADDRESS_MESSAGE,(char *)&ip_addr,sizeof(unsigned long),AF_INET,
			m_hostent_buf,sizeof(m_hostent_buf));
	}

	return 0;
}