int main(int argc,char* argv[])
{
    if(argc != 2)
    {
       printf("usage: dnsclient <host_name>\n");
       return -1;
    }
 
    time_t ident;
    int fd;
    int rc;
    int serveraddrlent;
    char *q;
    unsigned char *p;
    unsigned char *countp;
    unsigned char reqBuf[512] = {0};
    unsigned char rplBuf[512] = {0};
    struct sockaddr_in serveraddr;
 
    //udp
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1)
    {
       perror("error create udp socket");
       return -1;
    }
   
    time(&ident);
    //copy
    p = reqBuf;
    //Transaction ID
    *(p++) = ident;
    *(p++) = ident>>8;
    //Header section
    //flag word = 0x0100
    *(p++) = 0x01;
    *(p++) = 0x00;
    //Questions = 0x0001
    //just one query
    *(p++) = 0x00;
    *(p++) = 0x01;
    //Answer RRs = 0x0000
    //no answers in this message
    *(p++) = 0x00;
    *(p++) = 0x00;
    //Authority RRs = 0x0000
    *(p++) = 0x00;
    *(p++) = 0x00;
    //Additional RRs = 0x0000
    *(p++) = 0x00;
    *(p++) = 0x00;
    //Query section
    countp = p;  
    *(p++) = 0;
    for(q=argv[1]; *q!=0; q++)
    {
       if(*q != '.')
       {
           (*countp)++;
           *(p++) = *q;
       }
       else if(*countp != 0)
       {
           countp = p;
           *(p++) = 0;
       }
    }
    if(*countp != 0)
       *(p++) = 0;
 
    //Type=1(A):host address
    *(p++)=0;
    *(p++)=1;
    //Class=1(IN):internet
    *(p++)=0;
    *(p++)=1;
 
    printf("\nRequest:\n");
    printmessage(reqBuf);
 
    //fill
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(53);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.1.1");
 
    //send to DNS Serv
    if(sendto(fd,reqBuf,p-reqBuf,0,(void *)&serveraddr,sizeof(serveraddr)) < 0)
    {
       perror("error sending request");
       return -1;
    }
 
    //recev the reply
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddrlent = sizeof(serveraddr);
    rc = recvfrom(fd,&rplBuf,sizeof(rplBuf),0,(void *)&serveraddr,&serveraddrlent);
    if(rc < 0)
    {
       perror("error receiving request\n");
       return -1;
    }  
 
    //print out results
    printf("\nReply:\n");
    printmessage(rplBuf);
 
    //exit
    printf("Program Exit\n");
    return 0; 
}