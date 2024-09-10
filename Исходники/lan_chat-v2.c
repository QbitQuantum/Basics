int find_peer(int sockfd)
{
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(CHAT_PORT);

    /* Remove the last octet from the address */
    char *dot = strrchr(subnet_address, '.');
    dot[1] = 0;

    int i = start_idx;
    char try_address[strlen(subnet_address) + 4];
    do {
        snprintf(try_address, sizeof(try_address), "%s%d", subnet_address, i);
        printf("Trying %s\n", try_address);
        ++i;

        Inet_pton(AF_INET, try_address, &servaddr.sin_addr);
    } while (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0);

    printf("Bound!\n");

    return -1;
}