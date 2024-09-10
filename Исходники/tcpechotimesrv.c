 int main(int argc, char **argv)
  {  
	int  echosockfd,timesockfd ,connfd,*conptr,pollready,selready;
	int rset;
	pthread_t th;
    socklen_t clilen,len;
    struct sockaddr_in cliaddr, servaddr;
    struct pollfd client[2];
	int fileflags;
	char str[INET_ADDRSTRLEN];
	  
     rset=1;// for setsockopt() to select SO_REUSEADr 
	   
	if((timesockfd = socket(AF_INET, SOCK_STREAM, 0))== -1)/* Time Socket creation */
	{
		err_quit(" Time socket Error\n");
	}
	if((echosockfd = socket(AF_INET, SOCK_STREAM, 0))== -1)/* Echo Socket creation */
	{
		err_quit(" Echo socket Error\n");
	}
	
    setsockopt(timesockfd, SOL_SOCKET, SO_REUSEADDR,&rset, sizeof(int));
	setsockopt(echosockfd, SOL_SOCKET, SO_REUSEADDR,&rset, sizeof(int));
	 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
     
	servaddr.sin_port = htons (11433);
    Bind(timesockfd, (SA *) &servaddr, sizeof(servaddr));/*Bind Time Socket*/
   	Listen(timesockfd, LISTENQ);/*Listen for Time clients*/
	 
	servaddr.sin_port = htons (11432);
    Bind(echosockfd, (SA *) &servaddr, sizeof(servaddr));/*Bind Time Socket*/
    Listen(echosockfd, LISTENQ);/*Listen for Echo clients*/
	 
	signal(SIGPIPE,SIG_IGN);/*Handling SIGPIPE */ 
    Fputs("Server Waiting For Connections.....\n", stdout);
    for(;;)
	{
		 
		client[0].fd =timesockfd ;
		client[0].events =POLLRDNORM; 

		client[1].fd =echosockfd ;
		client[1].events =POLLRDNORM;
		  
		pollready=poll(client,3,NULL);
		if(pollready== -1)
		{
			err_sys("Poll has failed");
		}
		if (client[0].revents & POLLRDNORM)
		{
			conptr = Malloc(sizeof(int));
			*conptr = Accept(timesockfd, (SA *) NULL,NULL);/*Accept connection form time client*/
			Fputs("Connection formed between a Time client with the server\n",stdout);
			Pthread_create(&th, NULL, &timesel, conptr);/*creation of Thread*/
		}
		 
	    if (client[1].revents & POLLRDNORM)
		{
			clilen = sizeof(cliaddr);
			conptr = Malloc(sizeof(int));
			*conptr = Accept(echosockfd, (SA *) &cliaddr, &clilen);/*Accept connection form Echo client*/
			Fputs("Connection formed between a Echo client with the server\n",stdout);
			Pthread_create(&th, NULL, &echosel, conptr);/*creation of Thread*/
		 
		}
	}
 }