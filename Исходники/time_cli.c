int main(int argc,char *argv[]){
	int cli_parent_fd = strtol(argv[2],NULL,10);
	int sockfd,confd;
	int port_num = 5590;
	char feedback[MAXLINE];

	struct sockaddr_in servaddr;

	//Create a TCP socket that will connect to the port of time server.
	sockfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port_num);

	Inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	//Connect to the server using the socket just created.
	confd = connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
	if(confd < 0){
		//If connection with the server fails.
		bzero(feedback,sizeof(feedback));
		strcpy(feedback,"[Client][Time]Server could not be reached\n");
		Write(cli_parent_fd,feedback,strlen(feedback));
		close(cli_parent_fd);
		exit(0);
	}

	time_server(cli_parent_fd,sockfd,port_num);
	close(sockfd);
	close(cli_parent_fd);
	close(confd);
	exit(0);

}