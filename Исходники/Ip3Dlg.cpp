// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
UINT ThreadFun(LPVOID pParam){  //线程要调用的函数
   WSADATA wsd;
   int len=sizeof(struct sockaddr_in);
   int ret;
	TCHAR recvbuf[BUFSIZE];
   if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
   {
	   printf("WSAStartup()failed\n");
	   return -1;
   }
   if((sock=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,
	   WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF|
	   WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)
   {
	   printf("socket failed with :%d\n",WSAGetLastError());
	   WSACleanup();
	   return -1;
   }
   //将sock绑定到本机端口上
   local.sin_family=AF_INET;
   local.sin_port=htons(MCASTPORT);
   local.sin_addr.s_addr=INADDR_ANY;

   if(bind(sock,(struct sockaddr*)&local,sizeof(local))==SOCKET_ERROR)
   {
	   printf("bind failed with %d\n",WSAGetLastError());
	   closesocket(sock);
	   WSACleanup();
	   return -1;
   
   
   }
   //加入多播组

   remote.sin_family=AF_INET;
   remote.sin_port=htons(MCASTPORT);
   remote.sin_addr.s_addr=inet_addr(MCASTADDR);

   if((sockM=WSAJoinLeaf(sock,(SOCKADDR*)&remote,sizeof(remote),
	   NULL,NULL,NULL,NULL,
	   JL_BOTH))==INVALID_SOCKET)
   {
     printf("WSAJoinLeaf()failed:%d\n",WSAGetLastError());
     closesocket(sock);
	 WSACleanup();
	 return -1;
   }
   //接收多播数据，当收到的数据为QUIT时退出

   while(1)
   {
	   if((ret=recvfrom(sock,recvbuf,BUFSIZE,0,
		   (struct sockaddr*)&from,&len))==SOCKET_ERROR)
	   {
		   //printf("recvfrom failed with :%d\n",WSAGetLastError());
		   closesocket(sockM);
		   closesocket(sock);
		   WSACleanup();
		   return -1;
	   }
	   if(strcmp(recvbuf,"QUIT")==0)  break;
	   else{
		   recvbuf[ret]='\0';
		   Str+=inet_ntoa(from.sin_addr);
		   Str+=":";
		   Str+=recvbuf;
		   Str+="\r\n";
		   HWND hWnd = GetDlgItem(AfxGetMainWnd()->m_hWnd,IDC_EDIT1);
		   CWnd *pWnd = CWnd::FromHandle(hWnd);
		   pWnd->SetWindowText(_T(Str));

	   }
   }

   closesocket(sockM);
   closesocket(sock);
   WSACleanup();
   return 0;
}