int main(int argc, char** argv) {

	SOCKET s, s_acceptor;  			  		// socket and acceptor socket
	struct sockaddr_in saddr, caddr;  // server and client address structures
	uint16_t lport_n, lport_h; 				// server port number by htons()
	int backlog = 2;									// pending requests queue length
	socklen_t caddr_len;							// client address length
	int retValue;											// service() returning status
	int i;
	
	/* Check number of arguments */
	checkArg(argc, 3);
	
	/* The number of children */
	n_children = atoi(argv[2]);
	if (n_children > 10) {
		fprintf(stderr, "- ERROR. Children must be at most 10.\n");
		return -1;
	}
	
	/* Alloc memory for pids */
	pids = (pid_t*)malloc(n_children*sizeof(pid_t));
	if (pids == NULL) {
		fprintf(stderr, "- ERROR allocating pids.\n");
		return -1;
	}
	
	/* Instantiate a signal handler for SIGINT */
	Signal(SIGINT, sigintHandler);

	/* Initialize the socket API (only for Windows) */
	SockStartup();

	/* Set port number  */
	lport_n = setPortarg(argv[1], &lport_h);

	/* Create the socket */
	fprintf(stdout, "Creating the socket...\n");
	s = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	fprintf(stdout, "- OK. Socket fd: %d\n", s);
	
	/* Prepare server address structure */
	saddr.sin_family = AF_INET;
	saddr.sin_port = lport_n;
	saddr.sin_addr.s_addr = INADDR_ANY;

	/* Bind the socket to a local network address */
	fprintf(stdout, "Binding the socket...\n");
	Bind(s, (struct sockaddr*) &saddr, sizeof(saddr));
	fprintf(stdout, "- OK. Socket bound.\n");

	/* Listen to connection requests */
	fprintf(stdout, "Listen at socket %d with backlog = %d...\n", s, backlog);
	Listen(s, backlog);
	fprintf(stdout, "- OK. Socket is listening on ");
	showAddress(&saddr);
	
	for (i=0; i<n_children; i++) {
		
		if ((pids[i] = fork()) < 0) {
			fprintf(stderr, "- ERROR. fork() failed.\n");
		} else if ((pids[i]) > 0) {
			// The parent
		} else {
			// The child
			while(1) {
				/* Accept connection requests */
				br();
				caddr_len = sizeof(struct sockaddr_in);
				s_acceptor = Accept(s, (struct sockaddr*) &caddr, &caddr_len);
				fprintf(stdout, "- New connection from client ");
				showAddress(&caddr);
				
				retValue = service(s_acceptor);
				
				closesocket(s_acceptor);
				fprintf(stdout, "--- Connection closed by %s", (retValue == 0) ? "client\n" : "server\n");
				br();
			}
		}
		
	}
	
	while(1) {
		pause();
	}
	
	return 0;
}