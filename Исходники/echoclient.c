int main(int argc, char **argv) 
{
    int clientfd, port;
    char *host, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
    printf("client get: %s\n",buf);
	Rio_writen(clientfd, buf, strlen(buf));
    printf("client buf: %s\n",buf);
	Rio_readlineb(&rio, buf, MAXLINE);
	Fputs(buf, stdout);
    }
    
//    printf("outside\n");
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}