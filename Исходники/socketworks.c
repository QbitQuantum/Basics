int udp_bind_connect(char *src, int sport, char *dest, int dport,
		struct sockaddr_in *serv)
{
	int sock;
	sock = udp_bind(src, sport);
	if (sock < 0)
		return sock;
	fill_sockaddr(serv, dest, dport);
	if (connect(sock, (struct sockaddr *) serv, sizeof(*serv)) < 0)
	{
		LOGL(0, "udp_bind_connect: failed: bind(): %s", strerror(errno));
		return -1;
	}
	LOG("New UDP socket %d connected to %s:%d", sock, inet_ntoa(serv->sin_addr),
			ntohs(serv->sin_port));

	return sock;
}