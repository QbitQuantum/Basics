int main(int argc, char *argv[]) {
	int sock, intfsock;
	int opt;
	struct sockaddr_in addr, foreignaddr;
	socklen_t foreignaddrlen;
	int len;
	char addrtext[32], addrtext2[32], *paddrtext;
	struct ip_mreqn mreq;
	char *miface, *mifacename;
#define MAX_IFS 20
	struct ifreq ifaces[MAX_IFS];
	int mifaceind;
	u_int8_t mifacehwaddr[IFHWADDRLEN];
	struct in_addr mifaceaddr;
	char servername[64] = MSGKEY;
	int server;
	//int serverport = 49152;
	//int clientport = 49153;
	int serverport = 23058;
	int clientport = 23059;
	bootp_packet bp, br;
	struct pumpNetIntf bi;
	int vendorlen;
	time_t time0;

	/*
	 * See ftp://ftp.microsoft.com/bussys/winsock/ms-ext/multcast.txt
	 * on the use of multicast addresses
	 */
	char *multiaddr = "225.0.0.1";
	int multittl = 31;
	char *filename = NULL;

	char ident[8], recvalue[BUFLEN];
	int result;
	char command[BUFLEN];
	char netinfo[BUFLEN];
	int bonding = 0;

	//miface = NULL;
	miface = "eth0";
	mifacename = NULL;
	mifaceind = 0;
	memset(&mifaceaddr, 0, sizeof(mifaceaddr));
	mifaceaddr.s_addr = htonl(INADDR_ANY);
	memset(&mifacehwaddr, 0, sizeof(mifacehwaddr));

	server = 0;
	debug = 0;
	while ((opt=getopt(argc,argv,"si:g:t:o:S:C:I:d:v")) != EOF) {
		switch(opt) {
		case 's':
			server = 1;
			break;

		case 'i':
			miface = optarg;
			break;

		case 'g':
			multiaddr = strdup(optarg);
			break;

		case 't':
			multittl = strtol(optarg, NULL, 0);
			if (errno)
				error("TTL must be a number");
			break;

		case 'S':
			serverport = strtol(optarg, NULL, 0);
			if (errno)
				error("SERVER_PORT must be a number");
			break;

		case 'C':
			clientport = strtol(optarg, NULL, 0);
			if (errno)
				error("CLIENT_PORT must be a number");
			break;

		case 'I':
			strcat(servername,strdup(optarg));
			break;

		case 'd':
			debug = 1;
			break;

		case 'v':
			printf("Version:%s\n", VERSION);
			exit(0);

		default:
			usage();
		}
	}

	openlog("fagent+", LOG_PID | LOG_NDELAY | (debug ? LOG_PERROR : 0),
	        LOG_DAEMON);

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0)
		error("socket");

	if (miface != NULL) {
		if (!if_readlist_proc(miface)) {
			mifacename = miface;
			struct ifreq ifr;
			intfsock = socket(AF_INET, SOCK_DGRAM, 0);
			//intfsock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
			strncpy(ifr.ifr_name, miface, sizeof(ifr.ifr_name));
			if (ioctl(intfsock, SIOCGIFHWADDR, &ifr) < 0) {
				error("ioctl SIOCGIFHWADDR");
			}
			memcpy(&mifacehwaddr, &ifr.ifr_hwaddr.sa_data, IFHWADDRLEN);
			//unsigned char *s = &mifacehwaddr;
			//printf("%x %x %x %x %x %x\n", s[0],s[1],s[2],s[3],s[4],s[5]);
			ifr.ifr_addr.sa_family = AF_INET;
			if (ioctl(intfsock, SIOCGIFADDR, &ifr) < 0) {
				char bondip_file[16] = {0};
				strcat(bondip_file, "/tmp/bondip_");
				strcat(bondip_file, miface);
				//printf("not ip!!it is bond slave get ip from perl script\n");
				sprintf(command, _PATH_PERL_GETNETDEVIP" %s > %s", miface, bondip_file);
				system(command);
				FILE *fp = fopen(bondip_file, "r");
				if (fp) {
					unsigned char *i = &mifaceaddr;
					while ( !feof(fp) ) {
						fscanf(fp,"%d.%d.%d.%d", &i[0], &i[1], &i[2], &i[3]);
					}
					fclose(fp);
					unlink(bondip_file);
				} else {
					error("error get ip\n");
				}

				//error("ioctl SIOCGIFADDR");
			} else {
				mifaceaddr = ((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr;
			}
			//s = &mifaceaddr;
			//printf("%d %d %d %d\n", s[0],s[1],s[2],s[3]);
			close(intfsock);
		}
	}

#if 0
again:
	if (miface != NULL) {
		struct ifconf ifconfig;
		int i;

		ifconfig.ifc_len = sizeof(ifaces);
		ifconfig.ifc_req = (struct ifreq *)&ifaces;

		if (ioctl(sock, SIOCGIFCONF, &ifconfig) < 0)
			error("ioctl SIOCGIFCONF");

		for (i = 0; i < ifconfig.ifc_len / sizeof(struct ifreq); i++) {
			printf("ifname %s\n", ifaces[i].ifr_name);
			ifaces[i].ifr_addr.sa_family = AF_INET;
			if (ioctl(sock, SIOCGIFADDR, &ifaces[i]) < 0)
				error("ioctl SIOCGIFADDR");
		}

		if (strchr(miface, '.') != NULL) {
			if (!inet_aton(miface, &addr.sin_addr))
				error("inet_aton: multicast interface address");
			for (i = 0; i < ifconfig.ifc_len / sizeof(struct ifreq); i++)
				if (((struct sockaddr_in *)
				        &(ifaces[i].ifr_addr))->sin_addr.s_addr
				        == addr.sin_addr.s_addr)
					mifaceind = i + 1;
		} else {
			for (i = 0; i < ifconfig.ifc_len / sizeof(struct ifreq); i++)
				if (!strcmp(ifaces[i].ifr_name, miface))
					mifaceind = i + 1;
		}

		if (mifaceind) {
			struct ifreq ifr;
			mifaceaddr = ((struct sockaddr_in *)
			              &(ifaces[mifaceind - 1].ifr_addr))->sin_addr;
			mifacename = ifaces[mifaceind - 1].ifr_name;

			strncpy(ifr.ifr_name, mifacename, sizeof(ifr.ifr_name));
			ifr.ifr_addr.sa_family = AF_INET;
			if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0)
				error("ioctl SIOCGIFHWADDR");

			memcpy(&mifacehwaddr, &ifr.ifr_hwaddr.sa_data, IFHWADDRLEN);
			unsigned char *s = &mifacehwaddr;
			//printf("%x %x %x %x %x %x\n", s[0],s[1],s[2],s[3],s[4],s[5]);
		} else {
			miface = "bond0";
			bonding = 1;
			goto again;
		}
	}

	if (bonding)
		mifaceind = 0;
#endif
	if (mifacename == NULL)
		mifacename = "default";

	memset(&bp, 0, sizeof(bp));
	bp.opcode = (server ? 2 : 1); // client will request first
	bp.hw = 1;                    // ethernet
	bp.hwlength = IFHWADDRLEN;    // length of the hardware address
	bp.hopcount = 255;            // can be used by a proxy server,
	// shouldn't affect multicast
	bp.xid = htonl(0x12345678);
	bp.secs = htons(0);
	bp.flags = htons(0);
	if (server) {
		memset(&bp.ciaddr, 0, 4);
		memcpy(&bp.yiaddr, &your_ip, 4);
		memcpy(&bp.server_ip, &mifaceaddr, 4);
	} else {
		memcpy(&bp.ciaddr, &mifaceaddr, 4);
		memset(&bp.yiaddr, 0, 4);
		memset(&bp.server_ip, 0, 4);
	}

	memset(&bp.bootp_gw_ip, 0, 4);
	memcpy(&bp.hwaddr, &mifacehwaddr, sizeof(mifacehwaddr));
	strncpy((char *)&bp.servername, servername, sizeof(bp.servername));

#if 0
	memcpy(&bp.vendor, &magic_cookie, 4);
	vendorlen = 4;
	if (server) {
		memcpy(((void *)&bp.vendor) + 4, &test_server_data,
		       sizeof(test_server_data));
		vendorlen += sizeof(test_server_data);
	};
#else
	vendorlen = 0;
#endif
	bp.vendor[vendorlen++] = 0xFF;

// Print
//	fprintf(stdout, "Server Name = %s\n", servername);
//	fprintf(stdout, "bp.hwaddr = %d %d %d %d %d %d\n",
//			bp.hwaddr[0], bp.hwaddr[1], bp.hwaddr[2], bp.hwaddr[3], bp.hwaddr[4], bp.hwaddr[5]);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	/* 67 -- server, 68 -- client */
	if (server)
		addr.sin_port = htons(serverport);
	else
		addr.sin_port = htons(clientport);

	// addr.sin_addr = mifaceaddr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((paddrtext = (char *)inet_ntop(AF_INET, &addr.sin_addr,
	                                   addrtext, sizeof(addrtext))) == NULL)
		error("inet_ntop");

	//syslog(LOG_INFO, "Local address %s, port %d\n",
	//       paddrtext, ntohs(addr.sin_port));

	opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		error("setsockopt SO_REUSEADDR");

#if 0
	// see "man 4 ip", "man 7 socket" on SO_BROADCAST -- the option is discouraged
	if (server) {
		opt = 1;
		if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
		               &opt, sizeof(opt)) < 0)
			error("setsockopt SO_BROADCAST");
	}
#endif

	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
		error("bind");

	if (!inet_aton(multiaddr, &mreq.imr_multiaddr))
		error("inet_aton");

#if 1
	mreq.imr_address = mifaceaddr;
	mreq.imr_ifindex = mifaceind;
#elif 0
	mreq.imr_address = mifaceaddr;
	mreq.imr_ifindex = 0;
#else
	mreq.imr_address.s_addr = htonl(INADDR_ANY);
	mreq.imr_ifindex = 0;
	mifacename = "default";
#endif

	if (setsockopt(sock, SOL_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
		error("setsockopt IP_ADD_MEMBERSHIP");

	if (setsockopt(sock, SOL_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq)) < 0)
		error("setsockopt IP_MULTICAST_IF");

	opt = multittl;
	if (setsockopt(sock, SOL_IP, IP_MULTICAST_TTL, &opt, sizeof(opt)) < 0)
		error("setsockopt IP_MULTI_TTL");

	opt = 0;
	if (setsockopt(sock, SOL_IP, IP_MULTICAST_LOOP, &opt, sizeof(opt)) < 0)
		error("setsockopt IP_MULTI_LOOP");

	if (inet_ntop(AF_INET, &mreq.imr_multiaddr, addrtext, sizeof(addrtext))
	        == NULL)
		error("inet_ntop mreq.imr_multiaddr");
	if (inet_ntop(AF_INET, &mreq.imr_address, addrtext2, sizeof(addrtext2))
	        == NULL)
		error("inet_ntop mreq.imr_address");
	//syslog(LOG_INFO, "Joined multicast group %s on %s (interface %s)\n",
	//	       addrtext, addrtext2, mifacename);

	time0 = time(NULL);

	// Get Net Info, do here will speed up the response packet for the "NAV+"
	//unlink(_PATH_TMP_NETINFO);

//    sprintf(command, "killall net_util_getnet.pl >/dev/null 2>/dev/null"); system(command); //kill the last net_util_getnet.pl to prevent some error.
//    sprintf(command, _PATH_PERL_GETNETINFO" >/dev/null 2>/dev/null"); system(command); //call the perl before run fagent+
//	getnetinfo(netinfo, miface);
	
	while (1) {
		//crond_chk();//Minging.Tsai. 2014/5/1. Add a walk around to make sure the crond always on.
		struct timeval tv;
		fd_set fdset;
		int retcode;

		//sprintf(command, "killall net_util_getnet.pl >/dev/null 2>/dev/null"); system(command); //kill the last net_util_getnet.pl to prevent some error.
		//sprintf(command, _PATH_PERL_GETNETINFO" >/dev/null 2>/dev/null"); system(command); //call the perl before run fagent+
		getnetinfo(netinfo, miface);
		FD_ZERO(&fdset);
		FD_SET(sock, &fdset);
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		// linux specifics: tv gets updated automatically
		while (((retcode = select(sock + 1, &fdset, NULL, NULL, &tv)) < 0)
		        && (errno == EINTR));
		if (retcode < 0)
			error("select");
		else if (!retcode) {
			//if (debug)
				//syslog(LOG_INFO, "timeout waiting for input");
		} else {
			if ((len = recvfrom(sock, &br, sizeof(br), 0,
			                    (struct sockaddr *) &foreignaddr, &foreignaddrlen)) < 0)
				error("recvfrom");

			inet_ntop(AF_INET, &foreignaddr.sin_addr,
			          addrtext, sizeof(addrtext));
			/*syslog(LOG_INFO, "From %s:%d \"%s\"\n", addrtext,
			       ntohs(foreignaddr.sin_port),
			       len >= sizeof(br) - sizeof(br.bootfile)
			       - sizeof(br.vendor) ? (char *)&br.servername :
			       "(BOOTP packet too small)");*/
			process_bootp_packet(&br, len, &bi);

// Print
//			fprintf(stdout, "IP = %d.%d.%d.%d\n",
//					br.yiaddr[0], br.yiaddr[1], br.yiaddr[2], br.yiaddr[3]);
//			fprintf(stdout, "HWADDR = %d %d %d %d %d %d\n",
//					br.hwaddr[0], br.hwaddr[1], br.hwaddr[2], br.hwaddr[3], br.hwaddr[4], br.hwaddr[5]);

			if (br.hwaddr[0] == 0 && br.hwaddr[1] == 0 && br.hwaddr[2] == 0 &&
			        br.hwaddr[3] == 0 && br.hwaddr[4] == 0 && br.hwaddr[5] == 0 ) {

				if ( br.yiaddr[0] == 0 && br.yiaddr[1] == 0 && br.yiaddr[2] == 0 && br.yiaddr[3] == 0 ) {
					//syslog (LOG_DEBUG, "%s", br.bootfile);
					strncpy( ident, br.bootfile, 4);

					ident[4] = '\0';
					if ( ! strcmp(ident,"NAV+") ) {
//						printf("Got NAV+ from %s\n", miface);
						sprintf(command, "echo \"receive nasfinder NAV+ `date -u`\">/tmp/fagent+"); system(command); //kill the last net_util_getnet.pl to prevent some error.
//						sprintf(command, _PATH_PERL_GETNETINFO" >/dev/null 2>/dev/null"); system(command); //call the perl before run fagent+
						//Minging.Tsai. 2013/10/25.
						//char recv_helios_sn[19];
						//strncpy( recv_helios_sn, br.bootfile + 4, 19);
						//recv_helios_sn[18] = '\0';
						//printf("recv_helios_sn=\"%s\"\n", recv_helios_sn);

						//char recv_helios_ip[INET_ADDRSTRLEN];
						//inet_ntop(AF_INET, &(foreignaddr.sin_addr), recv_helios_ip, INET_ADDRSTRLEN);
						//printf("recv_helios_ip=\"%s\"\n", recv_helios_ip);

						//char cmd[128];
						//memset(cmd, 0, 128);
						//sprintf(cmd, "/nasapp/perl/util/net_util_chkjoininfo.pl \"%s\" \"%s\" &", recv_helios_ip, recv_helios_sn);
						//system(cmd);

						memset(&bp.bootfile, 0, sizeof(bp.bootfile));
						
						//unlink(_PATH_TMP_NETINFO);//Minging.Tsai. 2013/8/13. For nasfinder can get lastest information.
						//sprintf(command, _PATH_PERL_GETNETINFO" >/dev/null 2>/dev/null");		system(command);
						//sleep(3);
						getnetinfo(netinfo, miface);
	
						strncpy((char *)&bp.bootfile, netinfo, sizeof(bp.bootfile));
						memset(&foreignaddr, 0, sizeof(foreignaddr));
						foreignaddr.sin_family = AF_INET;
						foreignaddrlen = sizeof(foreignaddr);

						if (!server) {
							foreignaddr.sin_addr = mreq.imr_multiaddr;
							foreignaddr.sin_port = htons(serverport);

							//printf("bp.bootfile=%s\n", (char *)&bp.bootfile);
							bp.secs = htons((u_int16_t)(time(NULL) - time0));
							int error_count = 0;
							while ((len = sendto(sock, &bp, sizeof(bp), 0, (struct sockaddr *) &foreignaddr, foreignaddrlen)) < 0) {
								//printf("sendto error?\n");
								sleep(2);
								if(error_count > 10) {
									break;
								}
								error_count++;
								perror("client sendto request");
								//error("client sendto request");	//error() will call exit() to terminate the program
							}
							//printf("len =%d\n",len);
							sprintf(command, "echo \"reply nasfinder len=%d, error_count=%d\">>/tmp/fagent+", len, error_count); system(command); //kill the last net_util_getnet.pl to prevent some error.

						}
						//fprintf(stdout, "Say Hello\n");
					}
				}
			}
			else if(br.hwaddr[0] == bp.hwaddr[0] && br.hwaddr[1] == bp.hwaddr[1] && br.hwaddr[2] == bp.hwaddr[2] &&
			        br.hwaddr[3] == bp.hwaddr[3] && br.hwaddr[4] == bp.hwaddr[4] && br.hwaddr[5] == bp.hwaddr[5] ) {
				
				//printf("Get something!!\n");
				
				//syslog (LOG_DEBUG, "%s", br.bootfile);

				strncpy( ident, br.bootfile, 4);
				ident[4] = '\0';
				strcpy(recvalue,br.bootfile+5);

				if ( ! strcmp(ident,"AUTH") ) {
					//syslog (LOG_DEBUG, "AUTH: %s %s", ident, recvalue);
					result = login(recvalue);
					//syslog (LOG_DEBUG, "AUTH: RESULT %d", result);

					if ( result == 0 ) {
						strncpy((char *)&bp.bootfile, "AUTH&OK&", sizeof(bp.bootfile));
					}
					else {
						strncpy((char *)&bp.bootfile, "AUTH&FAIL&", sizeof(bp.bootfile));
					}

					memset(&foreignaddr, 0, sizeof(foreignaddr));
					foreignaddr.sin_family = AF_INET;
					foreignaddrlen = sizeof(foreignaddr);

					if (!server) {
						foreignaddr.sin_addr = mreq.imr_multiaddr;
						foreignaddr.sin_port = htons(serverport);

						bp.secs = htons((u_int16_t)(time(NULL) - time0));
						if ((len = sendto(sock, &bp,
						                  sizeof(bp) - sizeof(bp.vendor) + vendorlen,
						                  0 , (struct sockaddr *) &foreignaddr, foreignaddrlen)) < 0)
							error("client sendto request");
					}
				}
				else if ( ! strcmp(ident,"SNET") ) {
					//printf("SNET!!\n");
					/* it will receive the same packet three times */
					//printf("Got SNET from %s\n", miface);
					if (strncmp(br.servername, servername, sizeof(br.servername))) {
						sprintf(command, _PATH_PERL_SETHOSTNAME" \"/tmp/null\" \"%s\" >/dev/null 2>/dev/null", br.servername+8/*promise&*/);
						system(command);
					}
					//sprintf( command, "/bin/echo \"%s\" > /tmp/fagent+", recvalue );
					sprintf(command, _PATH_SH_SETNET" \"%s\" >/dev/null 2>/dev/null", recvalue);
					system(command);
				}
				else {
					sprintf( command, "/bin/echo \"%s\" > /tmp/fagent+", br.bootfile );
					system(command);
				}
			}
			//if (!strncmp(br.servername, servername, sizeof(br.servername)))
			//	break;
		}
	}

	if (setsockopt(sock, SOL_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
		error("setsockopt IP_DROP_MEMBERSHIP");
	close(sock);

	exit(EXIT_SUCCESS);
}