int main(int argc,char**argv)
{
	int listenfd, connfd, n;
	socklen_t			len;

	char buffer[MAXLINE];
	char writeBuffer[MAXLINE];
	char buff[MAXLINE];
	
	//char errorMessage[] = "DENIED";

	char username[50];
	char pass[50];
	
	struct sockaddr_in servaddr, cliaddr;

	if(argc != 2) //verifies number of command-line args; two in this instance
		err_quit("usage: <program name> <Port Number> ");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0); //create socket

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family 	=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port	=htons(atoi(argv[1]));

	printf("\nStart");
	Bind(listenfd, (SA *) &servaddr,sizeof(servaddr));

	printf("\nListening...");
	Listen(listenfd, LISTENQ);


	for( ; ; )
	{
		len = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &len);
		printf("\nAccepted\n");

		while( (n = read(connfd, buffer, MAXLINE)) > 0)
		{
			//exception has occured
			if(n<0)
			{
				break;
			}
			if(strstr(buffer, "\r\n\r\n") != NULL)
			{
				sscanf(buffer, "username: %s password: %s\r\n\r\n", username, pass);
				break;
			}
		}
		if(n<0)
		{
			break;
		}
		//printf("%s",buffer);
		//printf("pass %s",pass);

		//authenticate user
		if(strstr(username, "admin") != NULL && strstr(pass, "pass") != NULL) {
			
			Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));

			snprintf(writeBuffer, sizeof(writeBuffer), "PROCEED, IP: %s, Port: %d\r\n\r\n", buff , ntohs(cliaddr.sin_port) );

			Write(connfd, writeBuffer, strlen(writeBuffer));
			//Write(connfd, successMessage, strlen(successMessage));
		} else {
			snprintf(writeBuffer, sizeof(writeBuffer), "DENIED\n\r\n");
			Write(connfd, writeBuffer, strlen(writeBuffer));
		}

		printf("\nClose connection");
		Close(connfd);
	}


	return 0;
}