int main(int argc, char* argv[])
{
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    if(argc==1) {
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        inet_pton(AF_INET, argv[1], &addr.sin_addr);
    }
    addr.sin_port = htons(12200);
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));

    struct pollfd conns[MAXFD];
    for(int i=0;i<MAXFD;++i) conns[i].fd = -1;
    conns[0].fd = listenfd;
    conns[0].events = POLLIN;
    int conns_end = 1;

    Listen(listenfd,20);
    while(1)
    {
        int nready = Poll(conns,MAXFD,-1);
        if(conns[0].revents & POLLIN) { //new connection
            int pos;
            for(pos=0;pos<conns_end;++pos) {
                if(conns[pos].fd==-1) {
                    break;
                }
            }
            if(pos==conns_end&&conns_end==MAXFD) {
                fprintf(stderr,"too many connections.\n");
                exit(1);
            }
            if(pos==conns_end) {
                ++conns_end;
            }
            conns[pos].fd = Accept(listenfd,NULL,NULL);
            conns[pos].events = POLLIN;
            --nready;
        }
        for(int i=1;i<conns_end && nready>0 ;++i) { //client sockets are ready
            if( conns[i].fd!=-1 && (conns[i].revents & (POLLIN|POLL_ERR)) ) {
                int buf[MAXLINE];
                int n = read(conns[i].fd, buf, MAXLINE);
                if(n<0) { 
                    if(errno==ECONNRESET) {//connect RESET by client
                        Close(conns[i].fd);
                        conns[i].fd = -1;
                        if(i==conns_end-1)
                            --conns_end;
                    } else {
                        Perror("read error");
                    }
                }
                if(n==0) { //connect close by client
                    Close(conns[i].fd);
                    conns[i].fd = -1;
                    if(i==conns_end-1)
                        --conns_end;
                }
                if(n>0) { //normal data
                    Writen(conns[i].fd,buf,n);
                }
                --nready;
            }
        }
    }
    return 0;
}