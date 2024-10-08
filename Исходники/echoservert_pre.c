int main(int argc, char **argv) 
{
    int i, listenfd, connfd, port, clientlen=sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    pthread_t tid; 

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);
    sbuf_init(&sbuf, SBUFSIZE);
    listenfd = Open_listenfd(port);

    for (i = 0; i < NTHREADS; i++)  /* Create worker threads */
	Pthread_create(&tid, NULL, thread, NULL);

    while (1) { 
	connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
	sbuf_insert(&sbuf, connfd); /* Insert connfd in buffer */
    }
}