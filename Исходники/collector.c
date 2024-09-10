int main(int ac, char **av) {

    ssize_t l;
    char buf[2000];
    int r;
    int n;

    /* Socket variables */
    int s, exp;
    u_int yes=1;
    int port;
    struct sockaddr_in me, them;
    socklen_t sl = sizeof(struct sockaddr_in);

    struct pollfd fds[2];

    /*Initialization*/{
        port=3811;
        bzero(&me,sizeof(me));
        me.sin_family= AF_INET;
        me.sin_port=htons(port);

        s=socket(AF_INET,SOCK_DGRAM,0);
        bind(s,(struct sockaddr *)&me,sizeof(me));

        exp=socket(AF_INET,SOCK_STREAM,0);
        setsockopt(exp,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
        bind(exp,(struct sockaddr *)&me,sizeof(me));
        listen(exp,10);

        bzero(&fds,sizeof(fds));

        fcntl(s,F_SETFL,O_NONBLOCK);
        fcntl(exp,F_SETFL,O_NONBLOCK);

        fds[0].fd = s;
        fds[0].events |= POLLIN;
        fds[1].fd = exp, fds[1].events |= POLLIN;

        db_create(&db,NULL,0);
        db->set_cachesize(db, 0, 512*1024*1024, 0);
        db->open(db,NULL,"stats.db",NULL,DB_BTREE,DB_CREATE|DB_TRUNCATE,0);

        signal(SIGHUP,hup);
        signal(SIGINT,die);
        signal(SIGTERM,die);
        signal(SIGCHLD,child);
        signal(SIGUSR1,truncatedb);
        daemon(1,0);
    }
    /* Loop! loop! loop! */
    for(;;) {
        n=0;
        r=poll(fds,2,-1);

        /* Process incoming UDP queue */
        while(( fds[0].revents & POLLIN ) &&
                ((l=recvfrom(s,&buf,1500,0,NULL,NULL))!=-1)) {
            if (l==EAGAIN)
                break;
            handleMessage((char *)&buf,l);
            n++;
            /*  Still handle export connections under high load */
            if (n==5000)
                break;
        }

        /* Process incoming TCP queue */
        while((fds[1].revents & POLLIN ) &&
                ((r=accept(exp,(struct sockaddr *)&them,&sl))!=-1)) {
            if (r==EWOULDBLOCK)
                break;
            handleConnection(r);
        }
    }
    return(0);
}