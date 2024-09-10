int main(int argc, char **argv)
{
    int rc = 0;

    
    /* Defaults */
    inInAddr.sin_addr.s_addr    = INADDR_ANY;
    inInAddr.sin_port           = htons(DEFAULT_PORT);
    inInAddr.sin_family         = AF_INET;


    inSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (0 > inSocket)
    {
        printf("socket() call failed.\n");
        printError(inSocket, "socket");
        rc = -1;
        goto socket_failed;
    }
    
    /* Process cmdline opts. */
    char *shortOpts = "hi:e:p:";
    int   getoptRet;
    
    while(-1 != (getoptRet = getopt(argc, argv, shortOpts)))
    {
        switch(getoptRet)
        {
            case 'i':
                inInAddr.sin_addr.s_addr = inet_addr(optarg);
                break;
            case 'e':
                {
                struct ifreq fetchIfInfo;
                memset(&fetchIfInfo, 0, sizeof(struct ifreq));
                memcpy(fetchIfInfo.ifr_name, optarg, IFNAMSIZ - 1);
                
                /* Fetch the IP address to listen to based on interface name. */
                ioctl(inSocket, SIOCGIFADDR, &fetchIfInfo);
                
                struct sockaddr_in * const sockInfo = (struct sockaddr_in * const) &fetchIfInfo.ifr_addr;
                inInAddr.sin_addr.s_addr   = sockInfo->sin_addr.s_addr;
                }
                break;
            case 'p':
                inInAddr.sin_port        = htons(atoi(optarg));
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
                goto normal_exit;
                break;
        }
    }
    
    
    printf("Listening to: %s:%d\n", inet_ntoa(inInAddr.sin_addr),
                                    ntohs(inInAddr.sin_port));

    int timestampOn = 1;
    rc = setsockopt(inSocket, SOL_SOCKET, SO_TIMESTAMP, (int *) &timestampOn, sizeof(timestampOn));
    if (0 > rc)
    {
        printf("setsockopt(SO_TIMESTAMP) failed.\n");
        printError(rc, "setsockopt");
        goto setsockopt_failed;
    }

    rc = bind(inSocket, (struct sockaddr *) &inInAddr, sizeof(struct sockaddr_in));
    if (0 > rc)
    {
        printf("UDP bind() failed.\n");
        printError(rc, "bind");
        goto bind_failed;
    }

    struct msghdr   msg;
    struct iovec    iov;
    char            pktbuf[2048];
    
    char            ctrl[CMSG_SPACE(sizeof(struct timeval))];
    struct cmsghdr *cmsg = (struct cmsghdr *) &ctrl;

    msg.msg_control      = (char *) ctrl;
    msg.msg_controllen   = sizeof(ctrl);    

    msg.msg_name         = &inInAddr;
    msg.msg_namelen      = sizeof(inInAddr);
    msg.msg_iov          = &iov;
    msg.msg_iovlen       = 1;
    iov.iov_base         = pktbuf;
    iov.iov_len          = sizeof(pktbuf);


    struct timeval  time_kernel, time_user;
    int             timediff;


    printf("Starting main loop.\n");
    
    for(keepRunning = true; keepRunning;)
    {
        rc = recvmsg(inSocket, &msg, 0);

        gettimeofday(&time_user, NULL);
        
        if (cmsg->cmsg_level == SOL_SOCKET &&
            cmsg->cmsg_type  == SCM_TIMESTAMP &&
            cmsg->cmsg_len   == CMSG_LEN(sizeof(time_kernel))) 
        {
            memcpy(&time_kernel, CMSG_DATA(cmsg), sizeof(time_kernel));
        }
        
        printf("\n");
        printf("time_kernel                  : %d.%06d\n", (int) time_kernel.tv_sec, 
                                                           (int) time_kernel.tv_usec);
        printf("time_user                    : %d.%06d\n", (int) time_user.tv_sec,   
                                                           (int) time_user.tv_usec);
        
        timediff      = (time_user.tv_sec - time_kernel.tv_sec) * 1000000 + 
                        (time_user.tv_usec - time_kernel.tv_usec);
        totalUsec    += timediff; 
        ++totalPackets;
        
        rollingAverage  += timediff;
        rollingAverage  -= latencies[inDEX];
        latencies[inDEX] = timediff;
        inDEX = (inDEX + 1) % NUM_LATENCIES;
        printf("Current time diff is %d \n",timediff); 
        printf("Total Average                : %d/%d = %.2f us\n", totalUsec, 
                                                                   totalPackets, 
                                                                   (float) totalUsec / totalPackets);
        printf("Rolling Average (%d samples) : %.2f us\n", NUM_LATENCIES, 
                                                           (float) rollingAverage / NUM_LATENCIES);
    }

bind_failed:    
setsockopt_failed:
    close(inSocket);
socket_failed:
normal_exit:
    return rc;
}