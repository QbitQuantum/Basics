int main(int argc, char* argv[])
{
	int family = AF_INET;
	if (argc == 2) {
		family = (atoi(argv[1]) == 6)? AF_INET6 : AF_INET;
	}

	int servfd = Socket(family, SOCK_STREAM, IPPROTO_TCP);
	Listen(servfd, 0);

	struct sockaddr local_addr;
	socklen_t len = (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

	Getsockname(servfd, &local_addr, &len);
	print_ip_addr(family, &local_addr, "local address:");

	select_do(servfd, family);

	Close(servfd);
}