static const char *port_name(unsigned port)
{
	struct servent *server;

	server = getservbyport(htons(port), NULL);
	if (server)
		return server->s_name;
	return "unknown";
}