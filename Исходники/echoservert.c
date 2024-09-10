int main(int argc, char **argv) 
{
    int port = atoi(argv[1]);
    struct sockaddr_in clientaddr;
    int clientlen=sizeof(clientaddr);
    pthread_t tid; 

    int listenfd = Open_listenfd(port);
    while (1) {
	int *connfdp = Malloc(sizeof(int));
	struct hostent *hp;
	char *haddrp;
	int client_port;

	*connfdp = Accept(listenfd, (SA *) &clientaddr, &clientlen);
	/* determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			   sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
	client_port = ntohs(clientaddr.sin_port);
	printf("Server connected to %s (%s), port %d\n",
	   hp->h_name, haddrp, client_port);
	Pthread_create(&tid, NULL, echo_thread, connfdp);
    }
}