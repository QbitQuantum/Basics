static int
make_tcp_socket(void)
{
	struct protoent *protop;
	int sockfd;

	protop = getprotobyname("tcp");
	if (protop == NULL) {
		warnx("protocol not found: \"tcp\"");
		return (-1);
	}

	sockfd = socket(PF_INET, SOCK_STREAM, protop->p_proto);
	if (sockfd < 0) {
		warn("socket");
	}

	return (sockfd);
}