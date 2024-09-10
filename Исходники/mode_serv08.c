int
main(int argc, char **argv)
{
	int					ret, i, connfd;
	struct sockaddr_in	cliaddr, servaddr;
    socklen_t clilen, addrlen;
	void				sig_int(int);
    pthread_t tid;
    struct Thread *arg;

    if (argc != 3)
        err_quit("Usage: %s <port> <#threads>", basename(argv[0]));

    nthreads = atoi(argv[2]);

    if ((pThread = calloc(nthreads, sizeof(struct Thread))) == NULL)
        err_sys("calloc error");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);
    addrlen = sizeof(struct sockaddr_in);

    for (i = 0; i < nthreads; i++) {
        arg = pThread + i;
        arg->id = i;
        if ((ret = pthread_create(&tid, NULL, &mode_doit, (void *)arg)) != 0) {
            errno = ret;
            perror("pthread_create error");
            exit(1);
        }
    }

    Signal(SIGINT, sig_int);

    iput = iget = 0;
    for (;;) {
        clilen = addrlen;
        if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0)
            err_sys("accept error");

        if ((ret = pthread_mutex_lock(&mlock)) != 0) {
            errno = ret;
            perror("pthread_mutex_lock error");
            exit(1);
        }
        clifd[iput] = connfd;
        if (++iput == MAXNCLI)
            iput = 0;
        if (iput == iget)
            err_quit("iput = iget = %d\n", iput);
        if ((ret = pthread_cond_signal(&cond)) != 0) {
            errno = ret;
            perror("pthread_cond_signal error");
            exit(1);
        }
        if ((ret = pthread_mutex_unlock(&mlock)) != 0) {
            errno = ret;
            perror("pthread_mutex_unlock error");
            exit(1);
        }
    }
}