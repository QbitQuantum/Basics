int conn_nonb(char *ip,int port,int nsec)
{
    int flags, n, error;
    //socklen_t len;
    fd_set rset,wset;
    struct timeval tval;

    FD_ZERO(&wset);
    FD_ZERO(&rset);
    tval.tv_sec = nsec;
    tval.tv_usec = 0;
    //struct servent *sent;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    error = 0;
    if((n=connect(sockfd,(struct sockaddr *)&address,sizeof(address)))<0){
        if(errno!=EINPROGRESS)
        {
            printf("Connecting error!\n");
            return -1;
        }
        else if(n==0)
        { //This case may be happen on localhost?
            printf("Connecting success! \n");
            return 0;
        }
    }
    FD_SET(sockfd,&rset);
    wset=rset;
    //usleep(10);


    int rst = select(sockfd + 1, &rset,&wset,NULL,&tval);

    switch (rst) {
        case -1:
            perror("Select error"); exit(-1);
        case 0:
            close(sockfd);
            //printf("Timed Out!\n");
            break;
        default:
            if (FD_ISSET(sockfd,&rset)||FD_ISSET(sockfd,&wset)) {
                int error;
                socklen_t len = sizeof (error);
                if(getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,&len) < 0)
                {
                    printf ("getsockopt fail,connected fail\n");
                    return -1;
                }
                if(error==0)
                {
                    //printf ("%d open\n",port);
                    return 0;
                }
            }
            close(sockfd);
    }
    return -1;
}