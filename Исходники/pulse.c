int main(int argc, char *argv[])
// arg1: controller number
{
	int nolog = 0;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
	int run = 1;		// set to 0 to stop main loop
	fd_set readfd; 
	int numfds;
	int interval = 60;
	int tmout = 90;	// seconds to wait in select()
	int saveInterval = 600;	// Save to NVRAM every 10 mins
	int logerror = 0;
	int option; 
	int delay = 1000;		// usec to sleep (but it rounds up to 20mSec anyway
	time_t update = 0, now;
	pthread_t tid;
	time_t nextSave;

	// Command line arguments
	
	opterr = 0;
	while ((option = getopt(argc, argv, "di:slVZ1:2:")) != -1) {
		switch (option) {
			case 's': noserver = 1; break;
			case 'l': nolog = 1; break;
			case '?': usage(); exit(1);
			case 'i': interval = atoi(optarg); break;
			case 'd': debug++; break;
			case '1': rate1 = rate2 = atof(optarg);	break;
			case '2': rate2 = atof(optarg);	break;
			case 'V': printf("Version %s %s\n", getversion(), id); exit(0);
			case 'Z': decode("(b+#Gjv~z`mcx-@ndd`rxbwcl9Vox=,/\x10\x17\x0e\x11\x14\x15\x11\x0b\x1a" 
							 "\x19\x1a\x13\x0cx@NEEZ\\F\\ER\\\x19YTLDWQ'a-1d()#!/#(-9' >q\"!;=?51-??r"); exit(0);
		}
	}
	
	DEBUG printf("Debug %d. optind %d argc %d\n", debug, optind, argc);
	
	if (optind < argc) controllernum = atoi(argv[optind]);	// get optional controller number: parameter 1
	
	sprintf(buffer, LOGFILE, controllernum);
	
	if (!nolog) if ((logfp = fopen(buffer, "a")) == NULL) logerror = errno;	
	
	// There is no point in logging the failure to open the logfile
	// to the logfile, and the socket is not yet open.

	sprintf(buffer, "STARTED %s as %d interval %d %s", argv[0], controllernum, interval, nolog ? "nolog" : "");
	logmsg(INFO, buffer);
	
	// Set up socket 
	if (!noserver) {
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) 
			logmsg(FATAL, "FATAL " PROGNAME " Creating socket");
		server = gethostbyname("localhost");
		if (server == NULL) {
			logmsg(FATAL, "FATAL " PROGNAME " Cannot resolve localhost");
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr, 
			 (char *)&serv_addr.sin_addr.s_addr,
			 server->h_length);
		serv_addr.sin_port = htons(PORTNO);
		if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
			sockfd = 0;
			logmsg(ERROR, "ERROR " PROGNAME " Connecting to socket");
		}	
		
		if (flock(fileno(logfp), LOCK_EX | LOCK_NB) == -1) {
			logmsg(FATAL, "FATAL " PROGNAME " is already running, cannot start another one");
		}
	
		// Logon to server as meter
		sprintf(buffer, "logon " progname " %s %d %d", getversion(), getpid(), controllernum);
		sockSend(buffer);
	}
	else	sockfd = 1;		// noserver: use stdout
	
	// If we failed to open the logfile and were NOT called with nolog, warn server
	// Obviously don't use logmsg!
	if (logfp == NULL && nolog == 0) {
		sprintf(buffer, "event WARN " PROGNAME " %d could not open logfile %s: %s", controllernum, LOGFILE, strerror(logerror));
		sockSend(buffer);
	}
		
	// Set up hardware
	
	int mem = open("/dev/mem", O_RDWR);
	unsigned char * start = mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, mem, 0x80840000);
	pbdata = (unsigned int*)(start + 0x04);
	pbddr = (unsigned int *)(start + 0x14);
	// All inputs
	*pbddr = DIO4 | DIO5;  // DIO 4/5 outputs.
	*pbdata = 0xff;		// set to all 1's

	numfds = sockfd + 1;		// nfds parameter to select. One more than highest descriptor

	// Main Loop
	count1 = count2 = 0;
	readCMOS();
	DEBUG fprintf(stderr, "Got values from NVRAM: %d %d (%f %f)\n",  
				  count1, count2, (count1 / rate1), (count2 / rate2));

	// Start count thread
	if (pthread_create(&tid, NULL, count_pulses, NULL) < 0)
		perror("count_pulse");
	DEBUG fprintf(stderr, "Thread started as %d (0x%x)\n", tid, tid);

	FD_ZERO(&readfd); 

	update = timeMod(interval);
	nextSave = timeMod(saveInterval);
	while(run) {
		struct timeval tv1;
		now = time(NULL);
		if (now > nextSave) {
			DEBUG fprintf(stderr, "Saving to NVRAM ");
			writeCMOS();
			nextSave = timeMod(saveInterval);
			DEBUG {
				struct tm * t;
				t = localtime(&nextSave);
				strftime(buffer, sizeof(buffer), "%F %T", t);
				fprintf(stderr, "Next save at %s\n", buffer);
			}
		}

		if (now > update) {	// message time.  Will always send out 0 0 at startup.
			int fd;
			sprintf(buffer, "meter 2 %.1f %.1f", (count1 / rate1), (count2 / rate2));
			sockSend(buffer);
			update = timeMod(interval);
			// Write to /tmp/pulse
			fd = open("/tmp/pulse", O_RDWR | O_CREAT | O_TRUNC);
			if (fd < 0) perror("/tmp/pulse");
			if (fd > 0) {
				strcat(buffer, "\n");
				write(fd, buffer, strlen(buffer));
				close(fd);
			}
		}
		
		FD_SET(sockfd, &readfd);
		tv1.tv_sec = 0;
		tv1.tv_usec = tmout;
		if (select(sockfd + 1, &readfd, NULL, NULL, &tv1) && sockfd > 1)	// anything from server?
			run = processSocket();	// the server may request a shutdown by setting run to 0
		usleep(delay);
	}