int createConnection(char * portNum)
{
	int sockfd, new_fd;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //use localhost as IP

	//List all available addresses to be bound in the next step
	if ((rv = getaddrinfo(NULL, portNum, &hints, &servinfo)) != 0)
		{
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			return 1;
		}

	//Bind on first viable result
	for(p = servinfo; p != NULL; p = p->ai_next)
	{
		if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
			{
				perror("server: socket");
				continue;
			}

		if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
			{
				perror("setsockopt");
				exit(1);
			}

		if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
			{
				close(sockfd);
				perror("server:bind");
				continue;
			}

		break;
	}

	freeaddrinfo(servinfo);

	if (p == NULL)
		{
			fprintf(stderr, "server: failed to bind socket\n");
			exit(1);
		}

	if (listen(sockfd, BACKLOG) == -1)
		{
			perror("listen");
			exit(1);
		}

	printf("Server: waiting for connections...\n");

		sin_size = sizeof their_addr;
		//Assigns request as new connected socket
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		

	close(sockfd);


		if (new_fd == -1)
		{
			perror("accept");
			exit(1);
		}

		inet_ntop(their_addr.ss_family,
		get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);

		return new_fd;
}