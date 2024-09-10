int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("Usage: cli <Ipaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

//	if (connect_nob(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
//		err_sys("connect error");

    connect_nob(sockfd, (SA *)&servaddr, sizeof(servaddr), 10);

	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");
	exit(0);
}