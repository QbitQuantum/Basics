int
main(int argc, char **argv)
{
	int					sockfd, sockfd2;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	// 1. inquiry the server if the file is duplicated by fingerprint (a RTT)

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT+1); //
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	inquiry_by_fp(sockfd, "not_used");		/* do it all */

	close(sockfd); // yes close sockfd

	// 2. transfer not duplicated chunks to server 
	sockfd2 = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT); //
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd2, (SA *) &servaddr, sizeof(servaddr));

	transfer_file(sockfd2, 0);

	close(sockfd2);

	exit(0);
}