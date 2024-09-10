int OmegaUdpCreate(char *HostDnsName, int UdpPort)
{
	struct hostent *host; 
	struct sockaddr_in sa; 
	char IpAddr[20];
	
	if ((host = (struct hostent *)S_GETHOSTBYNAME(HostDnsName)) == NULL) //根据域名获取相应的IP信息， host将包含@remote_host对应的IP信息 
	{ 
		//libc_printf("----S_GETHOSTBYNAME Host name %s error! ----\r\n",HostDnsName);
	  return -1; 
	} 
	MEMCPY(&sa.sin_addr, host->h_addr, host->h_length);
	MEMSET(IpAddr,0,20);
	STRCPY(IpAddr,inet_ntoa(sa.sin_addr));
	//libc_printf("--Found omega,RAW  address:%s\n",inet_ntoa(sa.sin_addr)); 
	//libc_printf("--Found omega,IpAddr  address:%s\n",IpAddr);
	sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(IpAddr);
	servaddr.sin_port = htons(UdpPort);
	return sock;
}