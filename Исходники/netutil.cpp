int KSGNetUtil::GetMacByIP(const std::string ip, std::string &mac)
{
	char mac_str[30] = "";
	int nRemoteAddr = inet_addr( ip.c_str() );
	hostent host;
	hostent * remoteHostent= &host;
	struct in_addr sa;
	memset(&host,0,sizeof(host));
	//获取远程机器名
	sa.s_addr = nRemoteAddr;
	remoteHostent = gethostbyaddr( (char*)&nRemoteAddr,4, AF_INET );
	if ( NULL == remoteHostent )
		return -1;
	//发送ARP查询包获得远程MAC地址

	unsigned char macAddress[6];
	ULONG macAddLen = 6;
	DWORD iRet=SendARP(nRemoteAddr, (unsigned long)NULL,(PULONG)&macAddress, &macAddLen);
	if ( NO_ERROR == iRet )
	{
		int i =0;
		int j = 0;
		for( ; i<5; i++ )
		{
			j += sprintf(mac_str+j,"%.2X-", macAddress[i] );
		}
		sprintf(mac_str+j,"%.2X",macAddress[i]);
		mac = mac_str;
	}
	else
		return -1;
	return 0;
}