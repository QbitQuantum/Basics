int receive_udp(char *bind_ip, char *bind_port)
{

	int sock;
	char *buf;
	struct sockaddr_in remote, local;
	int ret = -1;
	int select_return;

	fd_set read_set, err_set;
	struct timeval timeout;

	buf = (char *) malloc(255);
	memset(buf, '\0', 255);	
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Socket error: ");
		return(-1);
	}

	local.sin_family  = AF_INET;
	local.sin_port = htons(atoi(bind_port));
	inet_aton(bind_ip, &local.sin_addr);

	if (bind(sock, (struct sockaddr *) &local, sizeof(local)) < 0)
	{
		perror("Bind error: ");
		return(-1);
	}

	FD_ZERO(&read_set);
	FD_SET(sock, &read_set);
	FD_ZERO(&err_set);
	FD_SET(sock, &err_set);
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	select_return = select(sock + 1, &read_set, NULL, &err_set, &timeout);
	if (select_return < 0)
	{
		perror("Select error: ");
		ret = -1;
	}

	 

 	if ((select_return > 0) && (FD_ISSET(sock, &read_set)) && (!FD_ISSET(sock, &err_set)))
	{

		if (recvfrom(sock, buf, 255, 0, (struct sockaddr *)0, (int *)0) >= 1)
		{
			printf("MESSAGE: %s\n", buf);
			ret = 0;
		}
		else
		{
			printf("recvfrom failed\n");
			ret = -1;
		}
	}
	free(buf);
	return(ret);

}