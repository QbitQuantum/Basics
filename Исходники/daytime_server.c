int
main(int argc, char** argv)
{
	int fd, optval, cfd;
	struct sockaddr_in6 server_addr, client_addr;
	socklen_t addr_len, client_addr_len;
	time_t ticks;
	char buf[BUFFER_SIZE];

	fd = Socket(AF_INET6, SOCK_STREAM, 0);
	optval = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
	optval = 0;
	setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &optval, sizeof optval);
	memset((void *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin6_family = AF_INET6;
#ifdef HAVE_SIN_LEN
	server_addr.sin6_len = sizeof(struct sockaddr_in6);
#endif
	server_addr.sin6_addr = in6addr_any;
	server_addr.sin6_port = htons(atoi(argv[1]));
	
	Bind(fd, (const struct sockaddr *) &server_addr, sizeof(server_addr));
	Listen(fd, 1);
	for (;;) {
		memset((void *) buf, '\0', sizeof(buf));
		addr_len = (socklen_t) sizeof(client_addr);
		memset((void *) &client_addr, 0, sizeof(client_addr));
		client_addr_len = (socklen_t) sizeof(client_addr);
		cfd = Accept(fd, (struct sockaddr *) &client_addr, &client_addr_len);
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		printf("%ld\r\n", strlen(buf));
		Sendto(cfd, (void *) buf, strlen(buf), 0, (struct sockaddr *)&client_addr, client_addr_len);
		Close(cfd);
	}
	Close(fd);

	return(0);
}