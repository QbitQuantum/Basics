static void send_from(struct test_params p, uint16_t sport, char *buf,
		      size_t len)
{
	struct sockaddr * const saddr = new_any_sockaddr(p.send_family, sport);
	struct sockaddr * const daddr =
		new_loopback_sockaddr(p.send_family, p.recv_port);
	const int fd = socket(p.send_family, p.protocol, 0), one = 1;

	if (fd < 0)
		error(1, errno, "failed to create send socket");

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)))
		error(1, errno, "failed to set reuseaddr");

	if (bind(fd, saddr, sockaddr_size()))
		error(1, errno, "failed to bind send socket");

	if (sendto(fd, buf, len, MSG_FASTOPEN, daddr, sockaddr_size()) < 0)
		error(1, errno, "failed to send message");

	close(fd);
	free(saddr);
	free(daddr);
}