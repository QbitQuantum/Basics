void
child_main(int i, int listenfd, int addrlen)
{
	int				connfd;
	void			web_child(int);
	socklen_t		clilen;
	struct sockaddr	*cliaddr;

	cliaddr = Malloc(addrlen);

	printf("child %ld starting\n", (long) getpid());
	for ( ; ; ) {
		clilen = addrlen;
		my_lock_wait();
		connfd = Accept(listenfd, cliaddr, &clilen);
		my_lock_release();

		web_child(connfd);		/* process the request */
		Close(connfd);
	}
}