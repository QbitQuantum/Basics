int init_online_detect()
{
    struct protoent *protocol;

    int size=3*1024;

    nsend=0;
    nreceived=0;

    if((protocol=getprotobyname("icmp") )==NULL)
    {
        perror("getprotobyname");
        //exit(1);
        return -1;
    }
    /*生成使用ICMP的原始套接字,这种套接字只有root才能生成*/
    if((sockfd=socket(AF_INET,SOCK_RAW,protocol->p_proto))<0)
    {
        perror("socket error");
        close(sockfd);
        //exit(1);
        return -1;

    }

#if 0
    //设置阻塞接收超时
    struct timeval tv_out;
    tv_out.tv_sec = 2; //超时2秒没有收到ICMP报文就返回
    tv_out.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv_out, sizeof(tv_out));
#endif

    /* 回收root权限,设置当前用户权限*/
    //setuid(getuid());
    /*扩大套接字接收缓冲区到50K这样做主要为了减小接收缓冲区溢出的
    的可能性,若无意中ping一个广播地址或多播地址,将会引来大量应答*/
    setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size));
    bzero(&dest_addr,sizeof(dest_addr));
    dest_addr.sin_family=AF_INET;
    //dest_addr.sin_addr.s_addr = inet_addr("192.168.1.184");
    return 0;
}