/* download the frame */
int tcp_receive_frame(void)
{
    int sPort = DEFAULT_PORT_TCP;
    int sListen = 0;
    int sAccept = 0;
    int sRecv = 0;
    int frame_fd;
    unsigned int sLen = 0;
    char tar_cmd[50];
    char frame_name[20];
    char recv_buf[RECV_BUF_LEN];
    struct sockaddr_in ser;
    struct sockaddr_in cli;

    printf("Server waiting...\n");
   
    sListen = Socket(AF_INET, SOCK_STREAM, 0);
    if (sListen < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    ser.sin_family = AF_INET;
    ser.sin_port = htons(sPort);
    ser.sin_addr.s_addr = htonl(INADDR_ANY);
   
    Bind(sListen, (struct sockaddr*)&ser, sizeof(ser));
    Listen(sListen, 5); 

    while(1)
    {
        sLen = sizeof(cli);
        sAccept = Accept(sListen, (struct sockaddr*)&cli, (unsigned int*)&sLen);
   
//        printf("accept() client IP: [%s]\n", (char*)inet_ntoa(cli.sin_addr));
//        printf("accept() client PORT: [%d]\n", ntohs(cli.sin_port)); 

        sRecv = Recv(sAccept, frame_name, sizeof(frame_name), 0);   

        frame_fd = open(frame_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (frame_fd == -1)
        {
            perror("open frame");
            return -1;
        }

        while (1)
        {   
            sRecv = Recv(sAccept, recv_buf, sizeof(recv_buf), 0);
            write(frame_fd, recv_buf, sRecv);
            if (sRecv == 0)
            {
                break;
            }
        }

        close(frame_fd);
        Close(sAccept);
   
        sprintf(tar_cmd, "tar -xzf %s", frame_name);
        system(tar_cmd);

        sleep(1);
    }

    Close(sListen);
   
    return 0;
}