int main(int argc, char** argv)
{
    CSCGlobal::gAgentName = "wttbd";
    int				listenfd, connfd;
    socklen_t		addrlen, len;
    struct sockaddr*	cliaddr;
    char			buff[MAXLINE];
    char			serv[12];
    int				n;
    const int		on = 1;
    struct addrinfo	hints, *res, *ressave;

    // get the config
    CConfig::load();

    // process the version info
    if ((argc == 2) && (strcmp("-v", argv[1]) == 0))
    {
        printf("%s %s\r\n", argv[0], SC_VER_STR);
        exit(0);
    }

    // log startup to syslog
    logToSyslog(WTTBD_IDENT, SC_SYSLOG_TEXT);

    if (argc == 2)
    {
        // default to port .
        strcpy(serv, TCP_PORT_WTTBD_STR);
        daemon_init(argv[0], 0, argv[1]);
    }
    else if (argc == 3)
    {
        // take port from command line
        strcpy(serv, argv[2]);
        daemon_init(argv[0], 0, argv[1]);
    }
    else
    {
        // default to port 4451
        strcpy(serv, TCP_PORT_WTTBD_STR);
        daemon_init(argv[0], 0);
    }

    int fd = 0;
    struct flock locking;

    locking.l_type = F_WRLCK;
    locking.l_whence = SEEK_SET;
    locking.l_start = 1;
    locking.l_len = 0;

    // check to see if already running  - if so exit
    if ( ((fd = open(WTTBD_LOCK_FILE, O_RDWR | O_CREAT, 0666)) == -1) ||
            ((fcntl(fd, F_SETLK, &locking)) == -1) )
    {
        // log startup to syslog
        logToSyslog(WTTBD_IDENT, SC_SYSLOG_RUNNING);
        exit(-1);
    }

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(NULL, serv, &hints, &res)) != 0)
    {
        // log startup to syslog
        logToSyslog(WTTBD_IDENT, gai_strerror(n));
        exit(-1);
    }

    ressave = res;

    do
    {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;		/* error, try next one */

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        if ((n = bind(listenfd, res->ai_addr, res->ai_addrlen)) == 0)
        {
            break;			/* success */
        }
        else if (errno == EINVAL)
        {

            logToSyslog(WTTBD_IDENT, "Exiting - Unable to bind to socket - already in use");
        }

        close(listenfd);	/* bind error, close and try next one */
    }
    while ( (res = res->ai_next) != NULL);

    if (res == NULL)	/* errno from final socket() or bind() */
    {
        logToSyslog(WTTBD_IDENT, "Exiting - No socket to bind to - Process already running.");
        exit(-1);
    }

    listen(listenfd, SC_MAX_LISTENQ);

    freeaddrinfo(ressave);

    addrlen = res->ai_addrlen;	/* size of protocol address */
    cliaddr = (struct sockaddr*)malloc(addrlen);

    // install child signal handler
    signal(SIGCHLD, sig_child);

    for ( ; ; )
    {
        pid_t pid;

        len = addrlen;
        connfd = accept(listenfd, cliaddr, &len);

        if ((pid = fork()) == 0)
        {
            close(listenfd);

            char 	str[128];	/* Unix domain is largest */
            char*   name ;
            name = str;
            std::string log;
            log = "Connection from :";
            log += inet_ntop(AF_INET, &(((sockaddr_in*)cliaddr)->sin_addr), name, sizeof(str));

            logToSyslog(WTTBD_IDENT, log.c_str());

            //****************************
            // do the work here
            //****************************
            char buffer[128];
            int numread = read(connfd, buffer, 127);
            // terminate the buffer
            buffer[numread] = '\0';

            close(connfd);

            // if input value is 0 then just testing to see if alive
            if ((buffer != NULL) && (atol(buffer) == 0))
            {
                exit(0);
            }
            else
            {
                // run the wttt program
                execlp(WTTT_APP_PATH, WTTT_APP, "0", buffer, "3", NULL);
            }

            // cleanup
            exit(0);
        }
        close(connfd);
    }
}