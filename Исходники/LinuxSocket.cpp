Socket* Socket::Accept()
{
    struct sockaddr_in6 sockaddr;
    socklen_t len = sizeof(struct sockaddr_in6);
    int newSocket = accept(socket_->fd, (struct sockaddr*)&sockaddr, &len);

    if(newSocket >= 0)
    {
        char str[INET6_ADDRSTRLEN];
        inet_ntop( AF_INET6, INETADDR_ADDRESS((struct sockaddr*)&sockaddr), str, sizeof(str));

        log(LOG_NOTICE) << "accept! " << str << " fd " << newSocket;
        SocketHandle_t* handle = new SocketHandle_t;
        handle->fd = newSocket;
        return new Socket(handle);
    }
    else
    {
        log(LOG_NOTICE) << "accept " << strerror(errno);
        return NULL;
    }
}