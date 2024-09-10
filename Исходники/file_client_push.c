// 发起三次握手
int ShakeHands(char *file_name, FILE **fpp)
{
    Packet fnpack;
    int filesize = 0;
    // 上传请求信号 dataID = -3
    fnpack.dataID = -3;
    FILE *fp = *fpp;
    fp = fopen(file_name, "rb");
    if (NULL == fp){
        printf("File:\t %s can not open to read.\n",file_name);exit(1);
    }
    char message[BUFFER_SIZE],md5sum[33]={'\0'};
    md5(&filesize,md5sum,&fp);                              // 计算文件大小和md5
    bzero(&message,sizeof(message));
    sprintf(message,"%s\t%d\t%s",file_name,filesize,md5sum);// 发送message包括文件名，文件大小和md5
    strncpy(fnpack.data, message, strlen(message));
    fnpack.dataLength = strlen(message);
    fnpack.flag = -1;
    
    printf("Sending request ...\n");
    Sendto(client_socket,(char *)&fnpack, sizeof(Packet),0, (struct sockaddr *)&server_addr, slen);
    
    Packet ack;
    Recvfrom(client_socket, (char *)&ack, sizeof(Packet), 0, (struct sockaddr *)&server_addr, &slen);
    if (ack.dataID == -5){
        // 服务器反馈 -5，说明秒传命中
        printf("File Exist on Server. Using fast copy.\n");
        return -5;
    }
    return 1;
}