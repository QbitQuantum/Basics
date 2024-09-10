int main(int argc, char *argv[])
{
        int fd = -1;

        struct sockaddr_in sin;

        int serv_port = MULTICAST_PORT;

        /* 参数处理*/
        if( argc < 2 || argc >3 ) {
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
        if(argc == 3) {
                serv_port = atoi(argv[2]);
        }

        /* 1.创建UDP套接字*/
        if( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("socket");
                exit(1);
        }
	/* 加入多播组 */
	struct ip_mreq mreq;
	bzero(&mreq, sizeof(mreq));
	mreq.imr_multiaddr.s_addr = inet_addr(argv[1]);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY); /* 本地端口建议使用INADDR_ANY*/
	
	if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq,sizeof(mreq))< 0) {
		perror("multicast setsockopt error");
		exit(EXIT_FAILURE);
	}

	/* 2. 绑定 */
        /*2.1 填充sockaddr_in结构体，填充绑定的IP地址和端口号 */
        sin.sin_family = AF_INET;
        sin.sin_port = htons(MULTICAST_PORT);
#if 0
        if(inet_pton(AF_INET,SERV_IP, &sin.sin_addr) != 1) {
                perror("inet_pton");
                exit(EXIT_FAILURE);
        }
#else
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
#endif
        bzero(sin.sin_zero, 8);

        /* 允许地址快速重用 **/
        int b_reuse =1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));

        /* 2.2 调用bind()函数去绑定在本地的某个IP地址+端口上*/
        if(bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
                perror("bind");
                exit(EXIT_FAILURE);
        }
	
	char buf[BUFSIZ];
	int ret = -1;
	char cli_ip_addr[16];

	struct sockaddr_in cin;
	int clen = sizeof(struct sockaddr_in);
	printf("Multicast demo staring....OK!\n");
	while(1) {
		bzero(buf, BUFSIZ);
		do {
			ret = recvfrom(fd, buf, BUFSIZ-1, 0, (struct sockaddr *)&cin, &clen); 
		}while (ret < 0 && EINTR == errno);
		if(ret < 0) {
			perror("recvfrom");
			continue;
		}	
		
		if( inet_ntop(AF_INET, &cin.sin_addr.s_addr, cli_ip_addr,sizeof(cin)) != NULL) {
               		printf("Client(%s:%d) said:%s\n", cli_ip_addr, ntohs(cin.sin_port), buf);
        	} else {
                	perror("inet_ntop");
			printf("Client said:%s\n", buf);
        	}

		if(!ret || !strncasecmp (buf, QUIT_STR, strlen (QUIT_STR))) {  /* 对方输入了quit,或对方已经关闭*/ 
			printf("client(%s:%d) is exited.\n", cli_ip_addr, ntohs(cin.sin_port));
		}
	}
	
	close(fd);
}