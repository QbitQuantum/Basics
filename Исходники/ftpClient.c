int makeClientSocket(const char *hostname, int port){
    int sock;
    struct hostent *host;
    struct sockaddr_in addr;
    if((host = gethostbyname(hostname)) == NULL ){
        perror(hostname);
        abort();
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(port);
    addr.sin_addr.s_addr    = *(long*)(host->h_addr);
    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0){
        CLOSESOCKET(sock);
        perror(hostname);
        abort();
    }
    return sock;
}