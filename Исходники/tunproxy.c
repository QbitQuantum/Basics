int main(int argc, char *argv[])
{
	struct sockaddr_in sin, sout, from;
	struct ifreq ifr;
	int fd, s, port, PORT, l;
	unsigned int soutlen, fromlen;
	char c, *p, *ip;
	char buf[1500];
	fd_set fdset;
	
	

	int MODE = 0, TUNMODE = IFF_TUN, DEBUG = 0;

	while ((c = getopt(argc, argv, "s:c:ehd")) != -1) {
		switch (c) {
		case 'h':
			usage();
		case 'd':
			DEBUG++;
			break;
		case 's':
			MODE = 1;
			PORT = atoi(optarg);
			break;
		case 'c':
			MODE = 2;
			p = (char*)memchr(optarg,':',16);
			if (!p) ERROR("invalid argument : [%s]\n",optarg);
			*p = 0;
			ip = optarg;
			port = atoi(p+1);
			PORT = 0;
			break;
		case 'e':
			TUNMODE = IFF_TAP;
			break;
		default:
			usage();
		}
	}
	if (MODE == 0) usage();

/*
	if ( (fd = open("/dev/net/tun",O_RDWR)) < 0) PERROR("open");

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = TUNMODE;
	strncpy(ifr.ifr_name, "toto%d", IFNAMSIZ);
	if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) PERROR("ioctl");

	printf("Allocated interface %s. Configure and use it\n", ifr.ifr_name);
*/
	
	/*
	s = socket(AF_INET, SOCK_DGRAM, 0);
  bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY; // or  htonl(INADDR_ANY); TODO ?!
	sin.sin_port = htons(PORT);
	if ( bind(s,(struct sockaddr *)&sin, sizeof(sin)) < 0) PERROR("bind");
	*/

	printf("PORT=%d \n", PORT);

	// struct sockaddr_in sin;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) error(1, 1, "Opening socket");
	//length = sizeof(server);
	bzero(&sin, sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_port=htons(PORT); 
	// if (bind(sock,(struct sockaddr *)&server,length)<0)
	printf("Doing the bind\n");
	if (bind(s,(struct sockaddr *)&sin, sizeof(sin))<0) error(1, 1, "binding");
	printf("Doing the bind - DONE\n");
	// fromlen = sizeof(struct sockaddr_in);

	printf("After bind in line %d\n", __LINE__);

	fromlen = sizeof(from);

	if (MODE == 1) {
		printf("Will wait for the passwor packet now...%d\n", __LINE__);
		while(1) {
			printf("Trying to receive password...%d\n", __LINE__);
			l = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&from, &fromlen);
			printf("Read password packet len=%d in line %d\n", l, __LINE__);
			if (l < 0) PERROR("recvfrom");
			if (strncmp(MAGIC_WORD, buf, sizeof(MAGIC_WORD)) == 0)
				break;
			printf("Bad magic word from %s:%i\n", 
			       inet_ntoa(from.sin_addr), ntohs(from.sin_port));
		} 
		printf("Got correct password in line %d\n", __LINE__);
		printf("Sending reply line %d\n", __LINE__);
		l = sendto(s, MAGIC_WORD, sizeof(MAGIC_WORD), 0, (struct sockaddr *)&from, fromlen);
		printf("Sent reply line %d\n", __LINE__);
		if (l < 0) PERROR("sendto");
	} else {
		from.sin_family = AF_INET;
		from.sin_port = htons(port);
		inet_aton(ip, &from.sin_addr);
		l =sendto(s, MAGIC_WORD, sizeof(MAGIC_WORD), 0, (struct sockaddr *)&from, sizeof(from));
		if (l < 0) PERROR("sendto");
		l = recvfrom(s,buf, sizeof(buf), 0, (struct sockaddr *)&from, &fromlen);
		if (l < 0) PERROR("recvfrom");
		if (strncmp(MAGIC_WORD, buf, sizeof(MAGIC_WORD) != 0))
			ERROR("Bad magic word for peer\n");
	}
	printf("Connection with %s:%i established\n", 
	       inet_ntoa(from.sin_addr), ntohs(from.sin_port));

	while (1) {
		FD_ZERO(&fdset);
		FD_SET(fd, &fdset);
		FD_SET(s, &fdset);
		if (select(fd+s+1, &fdset,NULL,NULL,NULL) < 0) PERROR("select");
		if (FD_ISSET(fd, &fdset)) {
			if (DEBUG) write(1,">", 1);
			l = read(fd, buf, sizeof(buf));
			if (l < 0) PERROR("read");
			if (sendto(s, buf, l, 0, (struct sockaddr *)&from, fromlen) < 0) PERROR("sendto");
		} else {
			if (DEBUG) write(1,"<", 1);
			l = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&sout, &soutlen);
			if ((sout.sin_addr.s_addr != from.sin_addr.s_addr) || (sout.sin_port != from.sin_port))
				printf("Got packet from  %s:%i instead of %s:%i\n", 
				       inet_ntoa(sout.sin_addr), ntohs(sout.sin_port),
				       inet_ntoa(from.sin_addr), ntohs(from.sin_port));
			if (write(fd, buf, l) < 0) PERROR("write");
		}
	}
}