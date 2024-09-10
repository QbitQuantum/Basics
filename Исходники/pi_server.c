/*
 * Set up threadpool and listening socket for normal listening server.
 * Set up threadpool, commandcenter, and listening socket.
 */
static int init(int portnum, struct sockaddr * sock_addr) {
	
	char strportnum[10];
	sprintf(strportnum, "%d", portnum);

	int listening_fd = -1;
	struct addrinfo * it;

	//Setup and run getaddrinfo
	struct addrinfo hints, * ai;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	Getaddrinfo(NULL, strportnum, &hints, &ai);
	
	//iterate over results of getaddrinfo and bind ipvX address
	for (it = ai; it != NULL; it = it->ai_next) {

		//check if this addrinfo has the correct family
		if (it->ai_family == AF_INET) {

			//begin listening
			sock_addr = it->ai_addr;
			listening_fd = init_listen(sock_addr);
		}
	}

	freeaddrinfo(ai);

	return listening_fd;
}