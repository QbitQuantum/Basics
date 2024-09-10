int SocketWrapper::peek(char *o_buf, int buf_size) 
{
    if (NULL == o_buf) {
        HAGGLE_ERR("Invalid params\n");
        return 0;
    }

    struct sockaddr saddr; 
    bzero(&saddr, sizeof(struct sockaddr));
    socklen_t addrlen = sizeof(struct sockaddr);

    ssize_t rc = recvFrom(o_buf, buf_size, MSG_PEEK, &saddr, &addrlen);

    if (0 >= rc) {
        HAGGLE_ERR("Error: could not peek on socket\n");
    }

    return rc;
}