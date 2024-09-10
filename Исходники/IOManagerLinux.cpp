int Manager::Report_TCP( Target_Spec *tcp_spec )
{
	int c, scanCount, i, skfd, count = 0;
	char ifname[32];
	FILE *netInfo;
	struct ifreq ifr;

	cout << "Reporting TCP network information..." << endl;
	
	netInfo = fopen("/proc/net/dev", "r");
	assert(netInfo != NULL);
	skfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (skfd < 0) {
		cerr << "Can not create socket in Manager::Report_TCP" << endl;
		return -1;
	}

	// Pull out the first two lines of the file. These two lines contain
	// labels for the columns.
	for (i = 0; i < 2; ++i) {
		do {
			c = getc(netInfo);
		} while ((c != '\n') && (c != EOF));
	}

	for (i = 0; i < MAX_NUM_INTERFACES; ++i) {
		// grab the interface names (if there are leading blanks,
		// then they are removed using the Strip() function)
		scanCount = fscanf(netInfo, "%[^:]: %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", ifname);
		if (scanCount == EOF) {
			break;
		}
		assert(scanCount == 1);
		Strip(ifname);

		// get ip address for the interface
		strcpy(ifr.ifr_name, ifname);
		ifr.ifr_addr.sa_family = AF_INET;
		if (ioctl(skfd, SIOCGIFADDR, &ifr) == 0) {
			strncpy ( tcp_spec[count].name, inet_ntoa(((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr), 
					sizeof(tcp_spec[count].name) - 1 );
			tcp_spec[count].type = TCPClientType;	// interface to access a client

			#if _DEBUG
				cout << "   Found " << tcp_spec[count].name << "." << endl;
			#endif
			count++;
		}
		else {
#if _DEBUG
			cerr << "ioctl fail in Manager::Report_TCP()" << endl;
#endif
		}
		// Skip to the next line.
		do {
			c = getc(netInfo);
		} while ((c != '\n') && (c != EOF));
	}
	fclose(netInfo);
	close(skfd);
	// All done.
	cout << "   done." << endl;
	return count;
}