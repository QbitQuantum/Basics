network_connect(struct scpi_instrument *scpi)
{
	struct sockaddr_in MyAddress, MyControlAddress;
	int status;
	struct timeval timeout;
	char buf[128];

	timeout.tv_sec = SOCKETS_TIMEOUT;
	timeout.tv_usec = 0;

	/* Create socket (allocate resources) - IPv4, TCP */
	scpi->main_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (scpi->main_socket == -1) {
		printf("Error: Unable to create socket (%i)...\n",errno);
		return -1;
	}

	/* set Recieve and Transmit Timeout, so connect doesn't take so long to fail */
	status = setsockopt(scpi->main_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	if (status < 0)
		perror("setsockopt failed\n");

	status = setsockopt(scpi->main_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout));
	if (status < 0)
		perror("setsockopt failed\n");

	/* Establish TCP connection */
	memset(&MyAddress,0,sizeof(struct sockaddr_in));
	MyAddress.sin_family = PF_INET;
	MyAddress.sin_port = htons(scpi->main_port);
	MyAddress.sin_addr.s_addr = inet_addr(scpi->ip_address);

	status = connect(scpi->main_socket, (struct sockaddr *)&MyAddress, sizeof(struct sockaddr_in));
	if(status == -1) {
		printf("Error: Unable to establish connection to ip:%s (%i)...\n",
				scpi->ip_address, errno);
		return -1;
	}

	/* Minimize latency by setting TCP_NODELAY option */
	network_setnodelay(scpi->main_socket);

	/* Ask for control port */
	sprintf(buf, "SYST:COMM:TCPIP:CONTROL?\n");
	status = send(scpi->main_socket, buf, strlen(buf), 0);
	if (status == -1)
		return -1;

	if (scpi_network_read((scpi)) == 0) {
		scpi->control_socket = scpi->main_socket;
		return 0;
	}

	sscanf(scpi->response, "%" SCNd16, &scpi->control_port);

	/* Create socket for control port */
	scpi->control_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(scpi->control_socket == -1) {
		printf("Error: Unable to create control port socket (%i)...\n",errno);
		return -1;
	}

	/* Establish TCP connection to control port */
	memset(&MyControlAddress, 0, sizeof(struct sockaddr_in));
	MyControlAddress.sin_family = PF_INET;
	MyControlAddress.sin_port = htons(scpi->control_port);
	MyControlAddress.sin_addr.s_addr = inet_addr(scpi->ip_address);

	status = connect(scpi->control_socket, (struct sockaddr *) &MyControlAddress, sizeof(struct sockaddr_in));
	if(status == -1) {
		printf("Error: Unable to establish connection to control port (%i)...\n",
			errno);
		return -1;
	}

	return 0;
}