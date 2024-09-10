int ftp_open_data(struct ftpconnection *connection) {
    struct sockaddr_in servaddr;
    struct in_addr sin;
    char *line;
    int h1, h2, h3, h4, p1, p2, port;
    int response;
    SOCKLEN len;
    if ((connection->dataconfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = 0;
    if (bind(connection->dataconfd, (SOCKADDR *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind");
        return -1;
    }
    if (listen(connection->dataconfd, 1) < 0) {
        perror("listen");
        return -1;
    }
    len = 128;
    if (getsockname(connection->dataconfd, (SOCKADDR *)&servaddr, &len) < 0) {
        perror("getsockname");
        return -1;
    }
    line = (char *)malloc(MAX_LINE_SIZE);
    if(NULL == line)
    {
        return -1;
    }
    port = servaddr.sin_port;
    sin.s_addr = connection->localip;
    sprintf(line, "%s.%d\r\n", inet_ntoa(sin), port);
    sscanf(line, "%d.%d.%d.%d.%d", &h1, &h2, &h3, &h4, &port);
    p1 = (port / 256);
    p2 = port - (256 * p1);
    sprintf(line, "PORT %d,%d,%d,%d,%d,%d\r\n", h1, h2, h3, h4, p2, p1);
    connection->status = STATUS_WAITING;
    ftp_sendline(connection, line);
    FREE(line);
    response = ftp_getrc(connection, NULL, 0, 0);
    switch (response) {
    case 200 :
        return 0;
    case 421 :
        printf("Service unavailable\n");
        ftp_disconnect(connection);
        return response;
        break;
    case 500 :
        printf("Server doesn't understand PORT\n");
        return response;
        break;
    case 501 :
        printf("Server doesn't understand PORT parameters\n");
        return response;
        break;
    case 502 :
        printf("Server doesn't understand PORT\n");
        return response;
        break;
    case 530 :
        printf("Not logged in\n");
        return response;
        break;
    default  :
        printf("Unknown response to PORT: %d\n", response);
        return response;
        break;
    }
}