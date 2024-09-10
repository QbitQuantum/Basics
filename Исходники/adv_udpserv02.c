int main(int argc, char *argv[])
{
    int sockfd;
    const int on = 1;
    pid_t pid;

    struct ifaddrs *ifp, *ifphead;
    struct sockaddr_in *sa, cliaddr, wildaddr;

    struct ifreq ifr;

    if (getifaddrs(&ifp) < 0)
        err_sys("getifaddrs error");

    for (ifphead = ifp; ifp = ifp->ifa_next; ifp != NULL) {
        if (!(ifp->ifa_flags & IFF_UP))
            continue;
        if (ifp->ifa_addr->sa_family != AF_INET)
            continue;
        sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
        Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        sa = (struct sockaddr_in *) ifp->ifa_addr;
        sa -> sin_family = AF_INET;
        sa -> sin_port = htons(SERV_PORT);
        Bind(sockfd, (SA *)sa, sizeof(*sa));
        printf("bound %s\n", Sock_ntop((SA *)sa, sizeof(*sa)));

        if ((pid = fork()) == 0) { /* child */
            adv_mydg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr), (SA *)sa);
            exit(0); /* never executed */
        }

        /* Parent continue... */

        /* try to bind the broadcast address */
#ifdef SIOCGIFBRDADDR
        if (ifp->ifa_flags & IFF_BROADCAST) {
            sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
            bzero(&ifr, sizeof(struct ifreq));
            strncpy(ifr.ifr_name, ifp->ifa_name, IFNAMSIZ);
            if (ioctl(sockfd, SIOCGIFBRDADDR, &ifr) < 0)
                err_sys("ioctl SIOCGIFBRDADDR error");
            sa = (struct sockaddr_in *) &ifr.ifr_ifru.ifru_broadaddr;
            sa->sin_family = AF_INET;
            sa->sin_port = htons(SERV_PORT);
            close(sockfd);
            sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
            Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
            if (bind(sockfd, (SA *)sa, sizeof(*sa)) < 0) {
                if (errno == EADDRINUSE) {
                    printf("EADDRINUSE: %s\n",
                            Sock_ntop((SA *)sa, sizeof(*sa)));
                    Close(sockfd);
                    continue;
                } else {
                    err_sys("bind error for %s",
                            Sock_ntop((SA *)sa, sizeof(*sa)));
                }
            }
            printf("bound %s\n", Sock_ntop((SA *)sa, sizeof(*sa)));
            if ((pid = fork()) == 0) { /* child */
                adv_mydg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr), (SA *)sa);
                exit(0); /* never executed */
            }
        }
#endif
    }

    /* bind wildcard address */
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&wildaddr, sizeof(wildaddr));
    wildaddr.sin_family = AF_INET;
    wildaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    wildaddr.sin_port = htons(SERV_PORT);
    Bind(sockfd, (SA *)&wildaddr, sizeof(wildaddr));
    printf("bound %s\n", Sock_ntop((SA *)&wildaddr, sizeof(wildaddr)));
    if ((pid = fork()) == 0) { /* child */
        adv_mydg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr), (SA *)&wildaddr);
        exit(0);
    }

    freeifaddrs(ifphead);
    exit(0);
}