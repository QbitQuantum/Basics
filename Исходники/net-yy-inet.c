int
main(void)
{
	skip_if_unavailable("/proc/self/fd/");

	const struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_LOOPBACK)
	};
	struct sockaddr * const listen_sa = tail_memdup(&addr, sizeof(addr));
	TAIL_ALLOC_OBJECT_CONST_PTR(socklen_t, len);
	*len = sizeof(addr);

	const int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
		perror_msg_and_skip("socket");
	const unsigned long listen_inode = inode_of_sockfd(listen_fd);
	printf("socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = %d<TCP:[%lu]>\n",
	       listen_fd, listen_inode);

	if (bind(listen_fd, listen_sa, *len))
		perror_msg_and_skip("bind");
	printf("bind(%d<TCP:[%lu]>, {sa_family=AF_INET, sin_port=htons(0)"
	       ", sin_addr=inet_addr(\"127.0.0.1\")}, %u) = 0\n",
	       listen_fd, listen_inode, (unsigned) *len);

	if (listen(listen_fd, 1))
		perror_msg_and_skip("listen");
	printf("listen(%d<TCP:[%lu]>, 1) = 0\n", listen_fd, listen_inode);

	memset(listen_sa, 0, sizeof(addr));
	*len = sizeof(addr);
	if (getsockname(listen_fd, listen_sa, len))
		perror_msg_and_fail("getsockname");
	const unsigned int listen_port =
		ntohs(((struct sockaddr_in *) listen_sa)->sin_port);
	printf("getsockname(%d<TCP:[127.0.0.1:%u]>, {sa_family=AF_INET"
	       ", sin_port=htons(%u), sin_addr=inet_addr(\"127.0.0.1\")}"
	       ", [%u]) = 0\n",
	       listen_fd, listen_port, listen_port, (unsigned) *len);

	TAIL_ALLOC_OBJECT_CONST_PTR(unsigned int, optval);
	*len = sizeof(*optval);
	if (getsockopt(listen_fd, SOL_TCP, TCP_MAXSEG, optval, len))
		perror_msg_and_fail("getsockopt");
	printf("getsockopt(%d<TCP:[127.0.0.1:%u]>, SOL_TCP, TCP_MAXSEG"
	       ", [%u], [%u]) = 0\n",
	       listen_fd, listen_port, *optval, (unsigned) *len);

	const int connect_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (connect_fd < 0)
		perror_msg_and_fail("socket");
	const unsigned long connect_inode = inode_of_sockfd(connect_fd);
	printf("socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = %d<TCP:[%lu]>\n",
	       connect_fd, connect_inode);

	*len = sizeof(addr);
	if (connect(connect_fd, listen_sa, *len))
		perror_msg_and_fail("connect");
	printf("connect(%d<TCP:[%lu]>, {sa_family=AF_INET, sin_port=htons(%u)"
	       ", sin_addr=inet_addr(\"127.0.0.1\")}, %u) = 0\n",
	       connect_fd, connect_inode, listen_port, (unsigned) *len);

	struct sockaddr * const accept_sa = tail_alloc(sizeof(addr));
	memset(accept_sa, 0, sizeof(addr));
	*len = sizeof(addr);
	const int accept_fd = accept(listen_fd, accept_sa, len);
	if (accept_fd < 0)
		perror_msg_and_fail("accept");
	const unsigned int connect_port =
		ntohs(((struct sockaddr_in *) accept_sa)->sin_port);
	printf("accept(%d<TCP:[127.0.0.1:%u]>, {sa_family=AF_INET"
	       ", sin_port=htons(%u), sin_addr=inet_addr(\"127.0.0.1\")}"
	       ", [%u]) = %d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>\n",
	       listen_fd, listen_port, connect_port, (unsigned) *len,
	       accept_fd, listen_port, connect_port);

	memset(accept_sa, 0, sizeof(addr));
	*len = sizeof(addr);
	if (getpeername(accept_fd, accept_sa, len))
		perror_msg_and_fail("getpeername");
	printf("getpeername(%d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>"
	       ", {sa_family=AF_INET, sin_port=htons(%u)"
	       ", sin_addr=inet_addr(\"127.0.0.1\")}, [%u]) = 0\n",
	       accept_fd, listen_port, connect_port, connect_port,
	       (unsigned) *len);

	memset(listen_sa, 0, sizeof(addr));
	*len = sizeof(addr);
	if (getpeername(connect_fd, listen_sa, len))
		perror_msg_and_fail("getpeername");
	printf("getpeername(%d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>"
	       ", {sa_family=AF_INET, sin_port=htons(%u)"
	       ", sin_addr=inet_addr(\"127.0.0.1\")}, [%u]) = 0\n",
	       connect_fd, connect_port, listen_port, listen_port,
	       (unsigned) *len);

	*len = sizeof(*optval);
	if (setsockopt(connect_fd, SOL_TCP, TCP_MAXSEG, optval, *len))
		perror_msg_and_fail("setsockopt");
	printf("setsockopt(%d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>"
	       ", SOL_TCP, TCP_MAXSEG, [%u], %u) = 0\n",
	       connect_fd, connect_port, listen_port, *optval,
	       (unsigned) *len);

	char text[] = "text";
	assert(sendto(connect_fd, text, sizeof(text) - 1,
	       MSG_DONTROUTE | MSG_DONTWAIT, NULL, 0) == sizeof(text) - 1);
	printf("sendto(%d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>, \"%s\", %u"
	       ", MSG_DONTROUTE|MSG_DONTWAIT, NULL, 0) = %u\n",
	       connect_fd, connect_port, listen_port, text,
	       (unsigned) sizeof(text) - 1, (unsigned) sizeof(text) - 1);

	assert(close(connect_fd) == 0);
	printf("close(%d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>) = 0\n",
	       connect_fd, connect_port, listen_port);

	assert(recvfrom(accept_fd, text, sizeof(text) - 1, MSG_WAITALL,
			NULL, NULL) == sizeof(text) - 1);
	printf("recvfrom(%d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>, \"%s\", %u"
	       ", MSG_WAITALL, NULL, NULL) = %u\n",
	       accept_fd, listen_port, connect_port, text,
	       (unsigned) sizeof(text) - 1, (unsigned) sizeof(text) - 1);

	assert(close(accept_fd) == 0);
	printf("close(%d<TCP:[127.0.0.1:%u->127.0.0.1:%u]>) = 0\n",
	       accept_fd, listen_port, connect_port);

	assert(close(listen_fd) == 0);
	printf("close(%d<TCP:[127.0.0.1:%u]>) = 0\n",
	       listen_fd, listen_port);

	puts("+++ exited with 0 +++");
	return 0;
}