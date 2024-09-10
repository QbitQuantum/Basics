int main(int argc, char **argv) {

	/* command line arguments variables */
	char *smewsBinaryPath = NULL;
	int nNodes = DEFAULT_NNODES;
	double nodeRange = DEFAULT_NODE_RANGE;
	double lossRate = DEFAULT_LOSS_RATE;

	/* misc. locals... */
	int i;
	int j;
	int ret;
	int nRead;
	int nfds;
	int tun_fd;
	int socket_fd;
	fd_set fdset;
	char tmpstr[64];
	char *cptr;
	struct sockaddr_in sockaddr;

	/* arguments parsing */
	if(argc == 1)
		usage();
	opterr = 0;
	while ((j = getopt (argc, argv, "hb:n:r:l:")) != -1) {
		switch (j) {
			case 'h':
				usage();
				break;
			case 'b':
				smewsBinaryPath = optarg;
				break;
			case 'n':
				nNodes = strtol(optarg, &cptr, 10);
				ensure(!*cptr && nNodes > 0,"Option -n requires a positive integer as argument.\n");
				break;
			case 'r':
				nodeRange = strtod(optarg, &cptr);
				ensure(!*cptr && nodeRange > 0 && nodeRange <=1,"Option -r requires a float in ]0-1] as argument.\n");
				break;
			case 'l':
				lossRate = strtod(optarg, &cptr);
				ensure(!*cptr && lossRate >= 0 && lossRate <=1,"Option -r requires a float in [0-1] as argument.\n");
				break;
			case '?':
				if(isprint (optopt))
					sprintf(tmpstr,"Unknown option `-%c'.\n", optopt);
				else
					sprintf(tmpstr,"Unknown option character `0x%x'.\n",optopt);
				ensure(0,tmpstr);
			default:
				ensure(0,"An error occured when parsing the arguments.\n");
		}
	}
	if(optind != argc) {
		sprintf(tmpstr,"Invalid argument `%s'\n", argv[optind]);
		ensure(0,tmpstr);
	}
	ensure(smewsBinaryPath != NULL,"Option -b is required.\n");

	/* print the current configuration */
	printf("Configuring the simulator...\n");
	printf("Smews binary path: %s\n",smewsBinaryPath);
	printf("Amount of nodes: %d\n",nNodes);
	printf("Nodes range: %f\n",nodeRange);
	printf("Loss rate: %f\n",lossRate);
	
	/* catch the 16 first signals signals */
	for(i=1; i<16; i++)
		signal(i, &cleanup);

	/* host socket creation */
	socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	check(socket_fd != -1,"socket() error");
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(1024);
	sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&sockaddr.sin_zero,0,8);
	ret=bind(socket_fd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
	check(ret != -1,"bind() error");

	/* Smews processes and nodes creation */
	nodes = (struct node_s *)malloc(nNodes*sizeof(struct node_s));
	check(nodes != NULL,"malloc() error");
	srand(time(NULL));
	for(i=0; i<nNodes; i++) {
		nodes[i].first_neighbour = NULL;
		nodes[i].nodeN = i;
		/* set coordinates for the node i */
		do {
			nodes[i].x = rand()/(float)RAND_MAX;
			nodes[i].y = rand()/(float)RAND_MAX;
			for(j=0; j<i; j++) {
				/* set neighbourhoud */
				if(ABS_DIST(nodes[i],nodes[j]) <= nodeRange) {
					add_neighbour(&nodes[i],&nodes[j]);
					add_neighbour(&nodes[j],&nodes[i]);
				}
			}
		/* ensures that the graph is connected */
		} while (i!=0 && !nodes[i].first_neighbour);
		/* new Smews process creation */
		sprintf(tmpstr,"%d",i);
		setenv("SMEWS_ID",tmpstr,1);
		if(!vfork()) { 
			execl(smewsBinaryPath,"",NULL);
			perror("execl() error");
			cleanup(2);
		}
	}

	/* TUN interface creation */
	struct ifreq ifr;
	tun_fd = open(DEVTUN, O_RDWR);
	check(tun_fd != -1,"tun open() error");
	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = IFF_TUN;
	ret = ioctl(tun_fd, TUNSETIFF, (void *) &ifr);
	check(ret >= 0,"tun ioctl error");
	/* TUN attachement to an IP address */
	snprintf((char*)tmpstr, BUFSIZE, "ifconfig %s 192.168.0.0 pointopoint 192.168.1.0 mtu 1500",ifr.ifr_name);
	ret = system((char*)tmpstr);
	check(ret != -1,"system() error when setting ifconfig");
	
	/* main loop */
	printf("Simulation is launched...\n");
	nfds = MAX(tun_fd,socket_fd)+1;
	FD_ZERO(&fdset);
	while(1) {
		FD_SET(tun_fd, &fdset);
		FD_SET(socket_fd, &fdset);
		ret = select(nfds, &fdset, NULL, NULL, NULL);
		check(ret != -1,"select() error");
		/* wait for something to read on tun_fd or socket_fd */
		if(ret) {
			if(FD_ISSET(tun_fd, &fdset)) {
				/* something has been received on tun_fd, we forward it to the reachable node */
				nRead = read(tun_fd, (void *)buffer, BUFSIZE);
				check(nRead != -1,"read() error");
				if(!loss_occurs(0,1,lossRate)) {
					sockaddr.sin_port = htons(1025);
					ret = sendto(socket_fd,buffer,nRead,0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
					check(ret != -1,"sendto() error");
				}
			}
			if(FD_ISSET(socket_fd, &fdset)) {
				/* something has been received on socket_fd */
				int addrLen;
				int emitterN;
				nRead = recvfrom(socket_fd,buffer,BUFSIZE,0,(struct sockaddr*)&sockaddr,&addrLen);
				check(nRead != -1,"recvfrom() error");
				emitterN = ntohs(sockaddr.sin_port) - (1025);
				if(emitterN >= 0 && emitterN < nNodes) {
					/* send the datagram to all the neighbours of the emitter */
					struct neighbour_s *curr_neighbour = nodes[emitterN].first_neighbour;
					while(curr_neighbour) {
						if(!loss_occurs(emitterN,curr_neighbour->node->nodeN,lossRate)) {
							sockaddr.sin_port = htons(1025 + curr_neighbour->node->nodeN);
							ret = sendto(socket_fd,buffer,nRead,0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
							check(ret != -1,"sendto() error");
						}
						curr_neighbour = curr_neighbour->next;
					}
					/* if the emitter is the reachable node, send the datagram on the TUN interface */
					if(emitterN == 0) {
						if(!loss_occurs(emitterN,0,lossRate)) {
							ret = write(tun_fd, buffer_shadow, nRead+4);
							check(ret != -1,"write() error");
						}
					}
				}
			}
		}
	}
	return 0;
}