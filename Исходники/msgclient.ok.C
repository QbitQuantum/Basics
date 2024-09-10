int
main(int argc, char **argv)
{
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if (argc != 3)
		err_sys("usage: exe  <IPaddress> <port>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");
		
	setnonblocking(sockfd); //设置非阻塞，需要判断errno
		
	int port = atoi(argv[2]);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(port);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s", argv[1]);
	
	int ret;
	ret=connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(ret<0 && errno == EINPROGRESS)
	{
		fd_set wset, rset;
		FD_ZERO(&wset);
		FD_SET(sockfd, &wset);
		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		rset = wset;
		
		switch(select(sockfd+1,&rset,&wset,NULL,&timeout))
		{
			case -1: //select错误
            case  0:  close(sockfd); exit(-1);break; //超时 推出
            default:
		#ifndef _YOUHUA
            if(!FD_ISSET(sockfd,&wset)) //测试sock是否可读，即是否网络上有数据
            {
				printf("connect error\n");
				close(sockfd);
				exit(0);
            }// end if break;
		#else
			//改进的非阻塞socket connet连接判断
			//如果connect成功，fd变为可写，如果失败fd可读可惜
			if(FD_ISSET(sockfd,&wset) ||FD_ISSET(sockfd,&rset)  )
			{
				int error = 0;
                socklen_t len = sizeof(error);              //防止connect三次握手的第三个ACK包被丢掉。
                if(getsockopt(sock_fd,SOL_SOCKET,SO_ERROR,&error,&len) < 0)      
                 {
                     perror("get sock opt fail:");
                 }
                 if(error == 0)
                 {
                     //printf("connect success\n");
                     //sleep(1);
                 }
                 else
                 {
                 	//printf("connect fail\n");
					close(sockfd);
					exit(0);
                 }
           }
		#endif
		}	
	}
	//printf("connect ok\n");

	sleep(3);
	int counter = 0;
	loop:
	
	long urlid;
	scanf("%ld", &urlid);
	//sprintf(recvline,"client msg[%d]  [%d], wait response", sockfd,counter++);
	sprintf(recvline,"%ld|url_dianping_1|", urlid );
	write(sockfd, recvline,strlen(recvline));
	
	//printf("request msg[%d]  send over\n",counter);
	
	/*
	for (;;) {
		fd_set cli_set;
		FD_ZERO(&cli_set);
		FD_SET(sockfd, &cli_set);
		int r = select (sockfd + 1, &cli_set, NULL, NULL, NULL);
		if (r == -1 && errno == EINTR) continue;
        if (r < 0) {
            exit (1);
        }
		
		if (FD_ISSET (sockfd, &cli_set)) {
			if(read(sockfd, recvline, MAXLINE) >0)
				printf("==msg %\n",  recvline);
		}
	*/
	sleep(1);
	//非阻塞模式使用
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	
		printf("%s", recvline);	
	}
	//printf("recv response over\n");	
	if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
	{
		printf("  goto loop \n");
		goto loop;
	}
	else
	{
		//close(sockfd);
		//长连接的话，进行重连
		//
	}
	/*if( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	
		printf("recv response[%d](%s)\n",counter-1, recvline);	
		
	goto loop;}*/
	close(sockfd);
	//printf("receive over exit  %d \n", n);
	
	if (n < 0)
		err_sys("read error");

	exit(0);
}