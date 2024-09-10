void test_COM1(void)
{
	char pressKey, *dev = "/dev/ttyS0", *s=NULL, *st;
	char *lf = strcat(dirname(gppath(getpid())), "/ppp.log");
	int l, m, n=0;
	FILE *com, *gprs, *pl;
	pthread_t ti, to;
	pid_t gid = 0;

	va_list ap;

	while (1)
	{
		printf("Press 'o' try to open COM1\n");
		printf("Press 'c' try to close COM1\n");
		printf("Press 'e' exit COM1 test\n");

		pressKey=getchar();

		printf("\n");

		switch (pressKey)
		{
			case 'o':
				com = fopen_sp(dev, B115200, 8, 0, 1, TTYS_TEXT_MODE);
				if (com != NULL)
					printf("Open COM1 OK! Pointer of COM: %p(address: %p)\n", com, &com);
				else
				{
					printf("Open COM1 error!\n");
					break;					
				}

				ti=to=0;
				
				if (pthread_create(&ti, NULL, send_to_com, (void *)com) != 0)
				{
					printf("Create send thread fail!\n");
					break;
				}
				if (pthread_create(&to, NULL, read_from_com, (void *)com) != 0)
				{
					printf("Create read thread fail!\n");
					break;
				}
				pthread_join(ti, NULL);

				char *arg[]={
					"pppd",
					"/dev/ttyS0",			//Serial device is ttyS0(COM1)
					"115200",				//Buad in 115200
					"modem",				//Waitting for CD signal
					"nocrtscts",			//Disabled hardware RTS & CTS
					"nodetach",				//Disable detach from terminal.
					"usepeerdns",			//Ask the peers for up to 2 DNS
					"noipdefault",			//Local ip supply by peers
					"defaultroute",			//Using the peers as gateway
					"user", "\"cmnet\"",
					"0.0.0.0:0.0.0.0",		//local ip:remote ip
					"ipcp-accept-local",	//Accept peer supply local IP
					"noccp",				//Disable CCP(Compression Control Protocol)
					"persist",				//hold connection
					"lcp-echo-interval", "5",	//Send LCP echo frame every 30 seconds
					"lcp-echo-failure", "5",	//Retry times when LCP echo fail
					"chap-interval", "5",		//rechallenge the peer every 5 seconds
					NULL};

				gprs = ppopen(&gid, "pppd", arg, "rn");
				if (NULL == gprs)
				{
					printf("Call pppd fail!\n");
					break;
				}
				pl = fopen(lf, "a");
				if (NULL == pl)
				{
					printf("Open log file fail!\n");
					break;
				}

				l = 0;
				time_t t;
				for (;;)
				{
					while (getline(&s, &n, gprs)<=0);
				
					t = time(NULL);
					st = sctime(&t);

					fprintf(pl, "%s>%s", st, s);
					fflush(pl);
					printf("%s>%s", st, s);

					if ((strstr(s, "terminated") != NULL) || (strstr(s, "failed") != NULL))
					{
						l = -1;
						printf("PPPD fail!\n");
						fprintf(pl, "\n%s>---PPPD fail!---\n", st);
						break;
					}

									switch (l)
					{
						case 0:
							if (strstr(s, PPPD_LOCAL_IP_STR) != NULL)
							{
								l++;
								printf("%d>>Got local IP\n", l);
							}
							break;
						case 1:
							if (strstr(s, PPPD_REMOTE_IP_STR) != NULL)
							{
								l++;
								printf("%d>>Got remote IP\n", l);
							}
							break;
						case 2:
							if (strstr(s, PPPD_PRIMARY_DNS_STR) != NULL)
							{
								l++;
								printf("%d>>Got primary dns\n", l);
							}
							break;
						case 3:
							if (strstr(s, PPPD_SECONDARY_DNS_STR) != NULL)
							{
								l++;
								printf("%d>>Got secondary dns\n", l);
							}
							break;
					}
					if (l == 4) 
					{
						printf("Got all str!\n");
						// break;
					}
				}

				if (l == -1)
				{
					printf("Close pipe file!\n");
					fclose(gprs);
					printf("Kill pppd! PID: %d\n", gid);
					kill(gid, SIGKILL);
					waitpid(gid, NULL, 0);
				}
				break;
			case 'c':
				fclose_sp(com);
		}
		if (pressKey=='e')
		{
			if (NULL != gprs) fclose(gprs);
			if (0 != gid)
			{
				kill(gid, SIGKILL);
				waitpid(gid, NULL, 0);
			}
			break;
		}
	}
}