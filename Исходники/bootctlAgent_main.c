/*
	bootAgentNotice is used to notice the PM service that the boot Agent starts up. Also,
	the hostname and IP address is deliver to the PM service.
*/
static int bootAgentNotice(int dbg)
{
	int sock;
	char bsip[30];
	char myIP[30];
	char hostname[100];
	char sendbuf[1024];
	char recvbuf[1024];
	int socklen=0;
	fd_set rfds;
	int ret = 0;
	int retry = 0;
	struct timeval tv;
	struct sockaddr_in sendAddr;
	struct sockaddr_in recvaddr;
	if(dbg == 1)
		sprintf(bsip, "127.0.0.1\0");
	else
		bsDiscovery(bsip);
	getInterfaceIP("eth1", myIP, sizeof(myIP));
	if(getHostname(hostname, sizeof(hostname))==-1)
		return -1;
	printf("Hostname-->%s\n",hostname);
	sock=createUdpClient();
	if(sock==-1)
		return -1;
	memset(&sendAddr,0,sizeof(sendAddr));
	sendAddr.sin_family=AF_INET;
	sendAddr.sin_port=htons(POALPORT);
	sendAddr.sin_addr.s_addr=inet_addr(bsip);
	sprintf(sendbuf, "%s,%s\0", hostname, myIP);
	while(1)
	{
		if(sendto(sock, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&sendAddr, sizeof(sendAddr)) ==-1)
		{
			goto errexit;
		}
		socklen=1024;
		memset(recvbuf, 0, sizeof(recvbuf));
		memset(&tv, 0, sizeof(tv));	
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		ret = select(sock+1, &rfds, NULL, NULL, &tv);
		if(ret ==  -1)
		{
			printf("Select Error\n");
			goto errexit;
		}else if(ret)
		{
			if (recvfrom(sock, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&recvaddr, &socklen) > 0)
			{
				printf("%s\n", recvbuf);
				if(!strncmp(recvbuf, "OK", 2))
					break;
			}
		}else
		{
			printf("No Ack retry\n");
			if(retry > 5)
				break;
			retry++;
		}
			
	}
	close(sock);
	return 1;
errexit:
	close(sock);
	return -1;

}