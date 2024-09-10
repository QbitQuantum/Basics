int main(int argc, char **argv){
	int res = 0;
	struct timeval tv1, tv2;
	char *directory = NULL;

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
	// Connect(sockfd2serverfp, (SA *)&servaddrfp, sizeof(servaddrfp));

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;// 
	setsockopt(sockfd2serverfp, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	int a = 65535;
	Setsockopt(sockfd2serverfp, SOL_SOCKET, SO_SNDBUF, &a, sizeof(int));
	Setsockopt(sockfd2serverfp, SOL_SOCKET, SO_RCVBUF, &a, sizeof(int));


#ifdef USE_UDP
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	sockfd2server = Socket(AF_INET, SOCK_DGRAM, 0);
#else
	sockfd2server = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT); //
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd2server, (SA *) &servaddr, sizeof(servaddr));
	Setsockopt(sockfd2server, SOL_SOCKET, SO_SNDBUF, &a, sizeof(int));
#endif
	// start 
	start_backup();

	uploadDir(directory);
	// uploadDir_recur(directory);

	gettimeofday(&tv2, NULL);
	printf("Time cost = %lfms\n",(tv2.tv_sec-tv1.tv_sec)*1000.0+(tv2.tv_usec-tv1.tv_usec)/1000.0);

    /* Upload complete, tell server to sync data to SDN controller
     * Need a alg(by dedu ratio) to control this sync
     */
    end_backup();


	close(sockfd4pox);
	
	// shutdown(sockfd2server, SHUT_WR);
	// shutdown(sockfd2serverfp, SHUT_WR);
	close(sockfd2serverfp);
	close(sockfd2server);
	exit(0);
}