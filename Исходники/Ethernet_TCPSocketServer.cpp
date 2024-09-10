int Ethernet_TCPSocketServer::bind(int port) {
    if (init_socket(SOCK_STREAM) < 0)
        return -1;
    
    struct sockaddr_in localHost;
    memset(&localHost, 0, sizeof(localHost));
    
    localHost.sin_family = AF_INET;
    localHost.sin_port = htons(port);
    localHost.sin_addr.s_addr = INADDR_ANY;
    
    if (lwip_bind(_sock_fd, (const struct sockaddr *) &localHost, sizeof(localHost)) < 0) {
        close();
        return -1;
    }
    
    return 0;
}