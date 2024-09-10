int main(int argc, char *argv[]) {
    int proxyfd, clifd;
    struct sockaddr_in proxyaddr, cliaddr;
    socklen_t cliaddrlen;

    /* initialize the socket as a server */
    proxyfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&proxyaddr, sizeof(proxyaddr));
    proxyaddr.sin_family = AF_INET;
    proxyaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    proxyaddr.sin_port = htons(PROXY_PORT);
    Bind(proxyfd, (struct sockaddr *)&proxyaddr, sizeof(proxyaddr));
    Listen(proxyfd, 5);

    /* infinite loop waiting for and processing requests */
    char cliaddrip[INET_ADDRSTRLEN];
    int pid;
    while (1) {
	cliaddrlen = sizeof(cliaddr);
	clifd = Accept(proxyfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
	Inet_ntop(AF_INET, &cliaddr.sin_addr, cliaddrip, INET_ADDRSTRLEN);

	fprintf(stdout, "---Request comes, IP=%s\n", cliaddrip);

	/* process the request in a subprocess */
	if ((pid=fork()) == 0) {
	    pid = getpid();
	    fprintf(stdout, "---pid=%d, Process the request in a subprocess\n", pid);

	    fprintf(stdout, "---pid=%d, Close proxy socket in the subprocess\n", pid);
	    Close(proxyfd);

	    do_proxy(clifd, &cliaddr, pid);

	    fprintf(stdout, "---pid=%d, Close the client socket in the subprocess\n", pid);
	    Close(clifd);

	    fprintf(stdout, "---pid=%d, Subprocess exits\n", pid);
	    exit(0);
	}

	fprintf(stdout, "---Close the client socket in the parent process\n");
	Close(clifd);
    }

    return 0;
}