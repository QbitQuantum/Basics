int				ft_connect(char const *addr, char const *port)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct protoent	*proto;
	int				fd;

	if ((proto = getprotobyname("tcp")) == NULL)
		return (-1);
	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = proto->p_proto;
	if (getaddrinfo(addr, port, &hints, &res) != 0)
		return (-1);
	fd = try_connect(res);
	freeaddrinfo(res);
	return (fd);
}