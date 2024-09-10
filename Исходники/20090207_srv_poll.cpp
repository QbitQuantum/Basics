int
main (int argc,char* argv[])
{
  int i,maxi,listenfd,connfd,sockfd;
  int nready;
  ssize_t n;
  char line[MAXLINE];
  socklen_t clilen;
  struct pollfd client[OPEN_MAX];
  struct sockaddr_in cliaddr,servaddr;
  listenfd = Socket(AF_INET,SOCK_STREAM,0);
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);
  Bind(listenfd,(sockaddr*)&servaddr,sizeof(servaddr));
  Listen(listenfd,LISTENQ);
  client[0].fd = listenfd;
  client[0].events = POLLRDNORM;
  for (i=1;i<OPEN_MAX;++i)
  	client[i].fd = -1;//indicates avallable entry
  maxi=0; //max index int client[]
  for(;;)
  {
  	//nready = poll(client,maxi+1,INFTIM);
  	nready = poll(client,maxi+1,-1);
  	if(client[0].revents&POLLRDNORM)//new client connection
  	{
  		clilen = sizeof(cliaddr);
  		connfd = Accept(listenfd,(sockaddr*)&cliaddr,&clilen);
  		for (i=1; i<OPEN_MAX;++i)
  		{
  			if (client[i].fd<0)
  			{
           client[i].fd = connfd; //save descriptor
           break;
  			}
  		}
  		if (i == OPEN_MAX)
  			err_sys("too many clients");
  		client[i].events = POLLRDNORM;
  		if(i>maxi)
  			maxi = i; //max index in client[]
  		if(--nready<=0)
  			continue; //no more readable descriptors
  	}
  	for (i=1; i<=maxi; ++i)//check all clients for data
  	{
  		if((sockfd = client[i].fd)<0)
  			continue;;
  		if(client[i].revents&(POLLRDNORM|POLLERR))
  		{
  			if((n=readline(sockfd,line,MAXLINE))<0)
  			{
  				if(errno == ECONNRESET)
  				{//connection reset by client
  					Close(sockfd);
  					client[i].fd=-1;
  				}
  				else
  					err_sys("readline error");
  			}
  			else if(n==0)
  			{//connection closed by client
  				Close(sockfd);
  				client[i].fd=-1;
  			}
  			else
  				writen(sockfd,line,n);
  			if(--nready<=0)
  				break; //no more readable descriptors
  		}
  	}
  }

}