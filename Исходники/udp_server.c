int main(void)
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int s_fd;
	int port = 8000;
	socklen_t addr_len;
	char buf[MAX_LINE];
	char addr_p[INET_ADDRSTRLEN];
	int n;

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;	/* Using IPv4 */
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == s_fd)
	{
		perror("fail to create socket");
		exit(1);
	}

	if (-1 == bind(s_fd, (struct sockaddr_t *)&sin, sizeof(sin)))
	{
		perror("fail to bind");
		exit(1);
	}

	while (1)
	{
		addr_len = sizeof(cin);
		n = recvfrom(s_fd, buf, MAX_LINE, 0, (struct sockaddr_t *)&cin, &addr_len);
		if (-1 == n)
		{
			perror("fail to receive");
			exit(1);
		}

		inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));

		printf("client IP is %s, prot is %d\n", addr_p, ntohs(cin.sin_port));

		my_func(buf);

		n = sendto(s_fd, buf, n, 0, (struct sockaddr_in *)&cin, addr_len);
		if (-1 == n)
		{
			perror("fail to send");
			exit(1);
		}
	}

	if (-1 == close(s_fd))
	{
		perror("fail to close");
		exit(1);
	}
	return 0;

}