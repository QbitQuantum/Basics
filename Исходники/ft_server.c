int		ft_create_server(int port, char *str)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sina;

	proto = getprotobyname("tcp");
	if (proto == NULL)
		ft_error(str, 1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sina.sin_family = AF_INET;
	sina.sin_port = htons(port);
	sina.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sina, sizeof(sina)) == -1)
		ft_error(str, 1);
	listen(sock, 42);
	return (sock);
}