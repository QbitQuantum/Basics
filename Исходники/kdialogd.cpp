static int createSocket()
{
    int         socketFd;
    ksocklen_t  addrlen;
    struct stat s;
    const char  *sock=getSockName();
    int stat_err=lstat(sock, &s);

    if(!stat_err && S_ISLNK(s.st_mode))
    {
        kWarning() << "Someone is running a symlink attack on you" ;
        if(unlink(sock))
        {
            kWarning() << "Could not delete symlink" ;
            return -1;
        }
    }

    if (!access(sock, R_OK|W_OK))
    {
        kWarning() << "stale socket exists" ;
        if (unlink(sock))
        {
            kWarning() << "Could not delete stale socket" ;
            return -1;
        }
    }

    socketFd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (socketFd < 0)
    {
        kError() << "socket(): " << strerror(errno);
        return -1;
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, sock, sizeof(addr.sun_path)-1);
    addr.sun_path[sizeof(addr.sun_path)-1] = '\000';
    addrlen = SUN_LEN(&addr);
    if (bind(socketFd, (struct sockaddr *)&addr, addrlen) < 0)
    {
        kError() << "bind(): " << strerror(errno);
        return -1;
    }

    struct linger lin;
    lin.l_onoff = lin.l_linger = 0;
    if (setsockopt(socketFd, SOL_SOCKET, SO_LINGER, (char *) &lin,
                   sizeof(linger)) < 0)
    {
        kError() << "setsockopt(SO_LINGER): " << strerror(errno);
        return -1;
    }

    int opt = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
                   sizeof(opt)) < 0)
    {
        kError() << "setsockopt(SO_REUSEADDR): " << strerror(errno);
        return -1;
    }
    opt = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_KEEPALIVE, (char *) &opt,
                   sizeof(opt)) < 0)
    {
        kError() << "setsockopt(SO_KEEPALIVE): " << strerror(errno);
        return -1;
    }
    chmod(sock, 0600);
    if (listen(socketFd, 1) < 0)
    {
        kError() << "listen(): " << strerror(errno);
        return -1;
    }

    return socketFd;
}