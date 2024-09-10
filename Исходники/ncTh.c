void client(char *host, char* port){
	int sockfd, numbytes;
	char buff[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	//This struct will be used to bind socket to port
	struct sockaddr_in popt;

	popt.sin_family = INADDR_ANY;
	popt.sin_port = htons(sourcePort);

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}
		if(pflag)
		{
			//Binds client to specific port
			 if (bind(sockfd, (struct sockaddr*)&popt, sizeof popt) == -1) {
			 	close(sockfd);
			 	perror("server: bind");
			 	continue;
		 	}
		}


		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		if(vflag){fprintf(stderr, "client: failed to connect\n");}
		exit(2);
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	/*If in debug mode print where we are connecting*/
	if(vflag){printf("client: connecting to %s\n", s);}

	freeaddrinfo(servinfo); // all done with this structure


	//Thread for sending messages
	struct Thread *send_thread = createThread(sending_thread, &sockfd);
	//Off it goes
	int threazy = runThread(send_thread, NULL);

	//Thread for reading messages
	struct Thread *receive_thread = createThread(receiving_thread, &sockfd);

	//off it goes
	int rthreazy = runThread(receive_thread, NULL);

	if(threazy == -10) {fprintf(stderr, "There was an error with the sending thread\n");}

	joinThread(send_thread, NULL);

}