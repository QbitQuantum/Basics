int main(int argc, char **argv)
{
	struct msghdr  			*msg;
	struct hwa_info			*hwa, *hwahead;
	struct sockaddr_un 		su;
	struct sockaddr			*sa;
	socklen_t				addrlen;
	int 					i, j;
	int 					protocol, maxfdp1;
	fd_set					rset;
	char					address[16], name[16];
	char					rcvline[MAXLINE];
	struct hostent			*host;
	
	if(argc < 2)
	{
		printf("Usage: odr staleness\n");
		return -1;
	}
	
	staleness  = atoi(argv[1]);
	
	gethostname(name, 16);
	host = malloc(sizeof(struct hostent));
	host = gethostbyname(name);
	if(host == NULL)
		printf("host is NULL\n");
	strncpy(canonical, inet_ntoa( *( struct in_addr*)( host -> h_addr_list[0])), 16);
	printf("Local ODR on host %s\n", name);
	printf( "Canonical IP: %s\n", canonical);

	printf("Finding interfaces\n");
	for (i = 0, hwahead = hwa = Get_hw_addrs(); hwa != NULL && i < MAX_INTERFACES; hwa = hwa->hwa_next, i++)
	{
		if(strncmp(hwa->if_name, "eth0", 4) != 0 && strncmp(hwa->if_name, "lo", 2) != 0)
		{
			for(j = 0; j < 6; j++)
			{
				interfaces[i].if_haddr[j] = hwa->if_haddr[j];
			}
			interfaces[i].if_index = hwa->if_index;
			sa = hwa->ip_addr;
			strncpy(interfaces[i].ip_addr, sock_ntop_host(sa, sizeof(*sa)), 16);
			printf("IP Address: %s\n",  interfaces[i].ip_addr);
			printf("Hardware Address: ");
			printHW(interfaces[i].if_haddr);
			printf("\nIndex: %d\n\n", interfaces[i].if_index);
		}
		else
			i--;
	}
	
	if_nums = i;
	err_msg("%s",ODR_SUNPATH);

	printf("Found %d interfaces\n", if_nums);
	//Creating packet socket
	pfsock = socket(PF_PACKET, SOCK_RAW, htons(ODR_PROTOCOL));
	if(pfsock < 0)
	{
		printf("pfsock: %d %s\n", errno, strerror(errno));
		return -1;
	}
	
	//Creating application socket
	su.sun_family = AF_LOCAL;
	strcpy(su.sun_path, ODR_SUNPATH);
	//strcat(su.sun_path, "\0");
	
	appsock = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(appsock < 0)
	{
		printf("appsock: %d %s\n", errno, strerror(errno));
		return -1;
	}
	
	unlink(ODR_SUNPATH);

	if(Bind(appsock, (struct sockaddr*) &su, SUN_LEN(&su)) < 0)
	{
		printf("bind failed: %d %s\n", errno, strerror(errno));
		return -1;
	}

	printf("Bound appsock\n");
	for ( ; ; ) 
	{
		printf("in for\n");
		FD_ZERO(&rset);
		printf("zero\n");
		FD_SET(pfsock, &rset);
		printf("set1\n");
		FD_SET(appsock, &rset);
		printf("set2\n");
		maxfdp1 = max(pfsock, appsock) + 1;
		printf("max\n");
		select(maxfdp1, &rset, NULL, NULL, NULL);
		
		printf("Selecting...\n");
		if(FD_ISSET(appsock, &rset))
		{
			printf("appsock is ready\n");
			//msg_recv(appsock, message, address, port);
			addrlen = sizeof(sa);
			
			if(recvfrom(appsock, rcvline, MAXLINE, 0, sa, &addrlen) < 0)
			{
					printf("appsock recvfrom error: %d %s\n", errno, strerror(errno));
					return -1;
			}
			
			//su = (struct sockaddr_un*) sa;			
			processAPPmsg(rcvline);
		}
		if(FD_ISSET(pfsock, &rset))
		{
			printf("pfsock is ready\n");
			//msg_recv(pfsock, message, address, port);
			
			if(recvmsg(pfsock, msg, 0) < 0)
			{
					printf("pfsock recvmsg error: %d %s\n", errno, strerror(errno));
					return -1;
			}
			processODRmsg(msg);
		}
	}
}