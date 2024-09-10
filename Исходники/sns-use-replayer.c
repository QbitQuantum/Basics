static void *listenForMessages( void *ptr )
{  
    struct sockaddr_in si_me;
    struct sockaddr_in si_other;
    socklen_t slen = sizeof(si_other);
    ssize_t readBytes = 0;
    char buf[BUFLEN+1]; //add space fer terminating \0
    char msgId[MSGIDLEN+1]; //add space fer terminating \0
    int port = PORT;

    DLT_REGISTER_APP("SNSS", "SENSOSRS-SERVICE");
    DLT_REGISTER_CONTEXT(gContext,"SSRV", "Global Context");

    LOG_INFO(gContext,"SensorsService listening on port %d...",port);

    if((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    {
        LOG_ERROR_MSG(gContext,"socket() failed!");
        exit(EXIT_FAILURE);
    }

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;

    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(s, (struct sockaddr *)&si_me, sizeof(si_me)) == -1)
    {
        LOG_ERROR_MSG(gContext,"socket() failed!");
        exit(EXIT_FAILURE);
    }

    while(isRunning == true)
    {
        //use select to introduce a timeout - alloy shutdown even when no data are received
        fd_set readfs;    /* file descriptor set */
        int    maxfd;     /* maximum file desciptor used */        
        int res;
        struct timeval Timeout;
        /* set timeout value within input loop */
        Timeout.tv_usec = 0;  /* milliseconds */
        Timeout.tv_sec  = 1;  /* seconds */
        FD_SET(s, &readfs);
        maxfd = s+1;
        /* block until input becomes available */
        res = select(maxfd, &readfs, NULL, NULL, &Timeout);

        if (res > 0)
        {
            
            readBytes = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_other, &slen);

            if(readBytes < 0)
            {
                LOG_ERROR_MSG(gContext,"recvfrom() failed!");
                exit(EXIT_FAILURE);
            }
            
            buf[readBytes] = '\0';

            LOG_DEBUG_MSG(gContext,"------------------------------------------------");
    
            LOG_DEBUG(gContext,"Received Packet from %s:%d", 
                      inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

            sscanf(buf, "%*[^'$']$%" STRINGIFY(MSGIDLEN) "[^',']", msgId);
    
            LOG_DEBUG(gContext,"MsgID:%s", msgId);
            LOG_DEBUG(gContext,"Len:%u", (unsigned int)strlen(buf));
            LOG_INFO(gContext,"Data:%s", buf);

            LOG_DEBUG_MSG(gContext,"------------------------------------------------");

            if(strcmp("GVSNSGYR", msgId) == 0)
            {
                processGVSNSGYR(buf);
            }
            else if(strcmp("GVSNSWHE", msgId) == 0)
            {
                processGVSNSWHE(buf);
            }
            else if(strcmp("GVSNSVSP", msgId) == 0)
            {
                processGVSNSVSP(buf);
            }
        }
    }

    close(s);

    return EXIT_SUCCESS;
}