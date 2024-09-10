/**
@SYMTestCaseID          SYSLIB-STDLIB-CT-1073
@SYMTestCaseDesc	    Tests for ARPA net functions
@SYMTestPriority 	    High
@SYMTestActions  	    Tests for get host by name and host by address functions
@SYMTestExpectedResults Test must not fail
@SYMREQ                 REQ0000
*/
void testNetDB()
	{
	char hostname[128];
	struct in_addr addr, *addrp;
	int err, i;
	struct hostent *hp;

	test_Next("Get Host Name");

	err=gethostname(hostname,sizeof(hostname));
	test(err==0);
	printf("  hostname = >%s<\n", hostname);

	test_Next("Get Host By Name");

	for (i=0; i<N_NAMES; i++)
		{
		hp=gethostbyname(names[i][0]);
		test_ok(hp!=0);
		addrp=(struct in_addr*)(hp->h_addr_list[0]);
		printf("  %-30s => address %-15s\n", hp->h_name, inet_ntoa(*addrp));
		test(strcasecmp(hp->h_name,names[i][0])==0);
		test(addrp->s_addr==inet_addr(names[i][1]));
		}

	hp=gethostbyname("nosuchname.symbian.com");
	test_errno(hp==0,ENOENT);
	test(errno==HOST_NOT_FOUND);

	test_Next("Get Address of \"\"");
	hp=gethostbyname("");
	test_ok(hp!=0);
	addrp=(struct in_addr*)(hp->h_addr_list[0]);
	printf("  %-30s => address %-15s\n", hp->h_name, inet_ntoa(*addrp));

	test_Next("Get Host By Addr");

	for (i=0; i<N_NAMES; i++)
		{
		addr.s_addr=inet_addr(names[i][1]);
		hp=gethostbyaddr((const char *)&addr,sizeof(addr),AF_INET);
		test_ok(hp!=0);
		addrp=(struct in_addr*)(hp->h_addr_list[0]);
		printf("  address %-15s => %s\n", inet_ntoa(*addrp), hp->h_name);
		test(addrp->s_addr==addr.s_addr);
		test(strcasecmp(hp->h_name,names[i][2])==0);
		}

	addr.s_addr=inet_addr("10.11.199.255");
	hp=gethostbyaddr((const char *)&addr,sizeof(addr),AF_INET);
	test_errno(hp==0,ENOENT);
	test(errno==HOST_NOT_FOUND);
	
/*
	struct sockaddr_in testaddr;
	int fd;
	test_Next("Connect to the Imperial College Echo server");

	fd=socket(AF_INET, SOCK_STREAM, 0);
	test_ok(fd>=0);
	testaddr.sin_family=AF_INET;
	testaddr.sin_addr.s_addr=inet_addr("193.63.255.1");
	testaddr.sin_port=htons(7);	// echo
	err=connect(fd,(struct sockaddr*)&testaddr, sizeof(testaddr));
	test(err==0);
	close(fd);
*/

	test_Next("Get Address of roundrobin.test.intra which has multiple address");
	hp=gethostbyname("roundrobin.test.intra");	
	test_ok(hp!=0);

	if (hp)
		{
		if (hp->h_addr_list)
			{
			int Index = 0;
			while (hp->h_addr_list[Index])
				{
				addrp = (struct in_addr*)(hp->h_addr_list[Index]);
				printf("  %-30s => address %-15s\n", hp->h_name, inet_ntoa(*addrp));
				Index++;
				}
			}
		}

	test_Next("Get Host name of 192.168.255.4 which has multiple host name");
	addr.s_addr=inet_addr("192.168.255.4");
	hp=gethostbyaddr((const char *)&addr,sizeof(addr),AF_INET);
	test_ok(hp!=0);

	if (hp)
		{
		addrp=(struct in_addr*)(hp->h_addr_list[0]);
		printf("  address %-15s => %s\n", inet_ntoa(*addrp), hp->h_name);

		if (hp->h_aliases)
			{
			int Index = 0;
			while (hp->h_aliases[Index])
				{
				printf("  address %-15s => %s\n", inet_ntoa(*addrp), hp->h_aliases[Index]);
				Index++;
				}
			}
		}

	if (close_console)
		{
		test_Close();
		close(0);
		close(1);
		close(2);
		}
	}