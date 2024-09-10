int main(int argc, char* argv[]){

	int family = AF_INET6;

	int servfd=Socket(family, SOCK_STREAM, IPPROTO_TCP);
	
	Listen(servfd, 0);

	struct sockaddr_in6 cliaddr;
	socklen_t len = sizeof(cliaddr);
	int clientfd;
	char buf[MAXLINE];

	struct sockaddr_in6  servaddr;
	socklen_t slen = sizeof(servaddr);
	char buf1[MAXLINE];

	Getsockname(servfd, (struct sockaddr*)&servaddr, &slen);
	printf("server bind address: %s, port %d\n",
		inet_ntop(family, &servaddr.sin6_addr, buf1, sizeof(buf1)),
		ntohs(servaddr.sin6_port));

	for ( ; ;)
	{
		clientfd = Accept(servfd, (struct sockaddr*)&cliaddr, &len);
		printf("connect from %s, port %d\n",
			inet_ntop(family, &cliaddr.sin6_addr, buf, sizeof(buf)),
			ntohs(cliaddr.sin6_port));
		bzero(&cliaddr, sizeof(cliaddr));

		Close(clientfd);
	}
}