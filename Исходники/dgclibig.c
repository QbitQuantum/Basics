void metaserver_keepalive(int sockfd, const SA *servaddr, socklen_t servlen)
{
    char         mesg[MAXLINE];
    char        *mesg_ptr;
    uint32_t     handshake=0, command=0;
    SA           addr;
    socklen_t    addrlen;
    unsigned int packet_size;

    packet_size = 0;
    mesg_ptr = pack_uint32(SKEEP_ALIVE, mesg, &packet_size);
    Sendto(sockfd, mesg, packet_size, 0, servaddr, servlen);

    addrlen = sizeof(addr);
    Recvfrom(sockfd, mesg, MAXLINE, 0, &addr, &addrlen);
    mesg_ptr = unpack_uint32(&command, mesg);

    if(command == HANDSHAKE)
    {
        mesg_ptr = unpack_uint32(&handshake, mesg_ptr);
        printf("Server contacted successfully.\n");

        packet_size = 0;
        mesg_ptr = pack_uint32(SERVERSHAKE, mesg, &packet_size);
        mesg_ptr = pack_uint32(handshake, mesg_ptr, &packet_size);

        Sendto(sockfd, mesg, packet_size, 0, servaddr, servlen);
    }
}