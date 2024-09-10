int						create_socket(t_serv *server)
{
	int					ret;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		return (-1);
	server->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(server->port);
	ret = bind(server->sock, (const struct sockaddr *)&sin, sizeof(sin));
	if (ret == -1)
		return (-1);
	listen(server->sock, 128);
	return (1);
}