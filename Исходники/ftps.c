int main(int argc, const char *argv[])
{
	struct sockaddr_in si;
	socklen_t socklen;
	struct servent *s;
	int sockfd, i;

	signal(SIGCHLD, SIG_IGN);

	printf("ftps v1.0\n");
	printf("2015.03.29\n");
	printf("author niulibing\n");

	if((fp=fopen("/etc/ftp.conf", "r")) == NULL)
	{
		perror("fopen");
		exit(1);
	}

	fgets(data, sizeof(data), fp);
	data[strlen(data)-1] = '\0';
	chdir(data);

	if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	if((s=getservbyname("ftp", "tcp")) == NULL)
	{
		printf("getservbyname fail\n");
		exit(1);
	}

	si.sin_family = AF_INET;
	si.sin_port = s->s_port;
	si.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (const struct sockaddr *)&si, sizeof(si)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if(listen(sockfd, 5) == -1)
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{
		socklen = sizeof(si);
		if((acceptfd=accept(sockfd, (struct sockaddr *)&si, &socklen)) == -1)
		{
			perror("accept");
			exit(1);
		}

		if(fork() == 0)
		{
			close(sockfd);
			
			while(recv(acceptfd, data, sizeof(data), 0) > 0)
			{
				arg[0] = strtok(data, " ");
				for(i=1; arg[i-1]!=NULL; i++)
				{
					arg[i] = strtok(NULL, " ");
				}

				if(strcmp(arg[0], "list") == 0)
				{
					list();
					break;
				}

				if(strcmp(arg[0], "get") == 0)
				{
					get();
					break;
				}

				if(strcmp(arg[0], "put") == 0)
				{
					put();
					break;
				}
			}

			close(acceptfd);
			exit(0);
		}

		close(acceptfd);
	}
}