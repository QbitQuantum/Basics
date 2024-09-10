/*
 * wfaCreateTCPServSock(): initially create a TCP socket
 * intput:   port -- TCP socket port to listen
 * return:   socket id;
 */
int wfaCreateTCPServSock(unsigned short port)
{
    int sock;                        /* socket to create */
    struct sockaddr_in servAddr; /* Local address */
    const int on = 1;

    /* Create socket for incoming connections */
    if ((sock = wSOCKET(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        DPRINT_ERR(WFA_ERR, "createTCPServSock socket() failed");
        return WFA_FAILURE;
    }
      
    /* Construct local address structure */
    wMEMSET(&servAddr, 0, sizeof(servAddr));
    wfaGetifAddr(gnetIf, &servAddr);
    servAddr.sin_family = AF_INET;        /* Internet address family */
    //servAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    servAddr.sin_port = htons(port);              /* Local port */

    wSETSOCKOPT(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    /* Bind to the local address */
    if (wBIND(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    {
        DPRINT_ERR(WFA_ERR, "bind() failed");
        return WFA_FAILURE;
    }

    /* Mark the socket so it will listen for incoming connections */
    if (wLISTEN(sock, MAXPENDING) < 0)
    {
        DPRINT_ERR(WFA_ERR, "listen() failed");
        return WFA_FAILURE;
    }

    return sock;
}