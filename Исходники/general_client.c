int main(int argc, char const *argv[])
{
	int family = AF_INET;

	if (!(argc ==3 || argc ==4))
		err_sys("input args: address port");
	if (argc == 4)
		family = AF_INET6;

	struct sockaddr *serv_addr;
	socklen_t serv_len;
	if (family == AF_INET){
		serv_addr = (struct sockaddr*)v4_addr(family, atoi(argv[2]), argv[1]);
		serv_len = sizeof(struct sockaddr_in);
	}
	else {
		serv_addr = (struct sockaddr*)v6_addr(family, atoi(argv[2]), argv[1]);
		serv_len = sizeof(struct sockaddr_in6);
	}
	
	int clientfd = Socket(family, SOCK_STREAM, IPPROTO_TCP);
	Connect(clientfd, serv_addr, serv_len);

	struct sockaddr local_addr;
	Getsockname(clientfd, &local_addr, &serv_len);
	print_ip_addr(family, &local_addr, "local address \n");

	select_do(clientfd);

	Close(clientfd);
	free(serv_addr);
	return 0;
}