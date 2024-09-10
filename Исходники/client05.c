int main(int argc, char **argv){
	int res = 0;
	struct timeval tv1, tv2;
	double total;
	char *directory = NULL;
	long count;

	if (argc != 3)
		err_quit("usage: client <IPaddress> <file dir>");
	serverip = argv[1];
	directory = argv[2];

	gettimeofday(&tv1, NULL);

	sockfd4pox = get_udp_socket(QUICK_PORT);// channel with POX

	bzero(&servaddrfp, sizeof(servaddrfp));
	servaddrfp.sin_family = AF_INET;
	servaddrfp.sin_port = htons(SERV_PORT+1);
	Inet_pton(AF_INET, argv[1], &servaddrfp.sin_addr);
	sockfd2serverfp = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	sockfd2server = Socket(AF_INET, SOCK_DGRAM, 0);

	uploadDir(directory);

	gettimeofday(&tv2, NULL);
	printf("Time cost = %lfms\n",(tv2.tv_sec-tv1.tv_sec)*1000.0+(tv2.tv_usec-tv1.tv_usec)/1000.0);

	close(sockfd4pox);
	close(sockfd2server);
	close(sockfd2serverfp);
	exit(0);
}