void mydg_echo(int sockfd, SA* myaddr, socklen_t salen)
{
    int n;
    char mesg[MAXLINE];
    socklen_t len;
    struct sockaddr* cli;

    cli = Malloc(salen);

    for (;;) {
        len = salen;
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, cli, &len);
        printf("child %d, datagram from %s", getpid(), Sock_ntop(cli, len));
        printf(", to %s\n", Sock_ntop(myaddr, salen));

        Sendto(sockfd, mesg, n, 0, cli, len);
    }
}