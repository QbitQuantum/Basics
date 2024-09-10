void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN sendAddr;

	WSABUF dataBuf;
	char msg[]="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	int sendBytes=0;
	WSAEVENT eventObject;
	WSAOVERLAPPED overlapped;

	if(argc!=3){
		printf("Usage : %s <IP> <PORT> \n",argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	sock=WSASocket(PF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	memset(&sendAddr,0,sizeof(sendAddr));
	sendAddr.sin_family=AF_INET;
	sendAddr.sin_port=htons(atoi(argv[2]));
	sendAddr.sin_addr.s_addr=inet_addr(argv[1]);

	if(connect(sock,(SOCKADDR*)&sendAddr,sizeof(sendAddr))==SOCKET_ERROR) ErrorHandling("connect error");

	eventObject=WSACreateEvent();
	memset(&overlapped,0,sizeof(overlapped));
	dataBuf.len=strlen(msg)+1;
	dataBuf.buf=msg;

	if(WSASend(sock,&dataBuf,1,&sendBytes,0,&overlapped,NULL)==SOCKET_ERROR){
		if(WSAGetLastError()==WSA_IO_PENDING){ //전송할 데이터가 남아 있는 상태
			puts("Background data send");
			WSAWaitForMultipleEvents(1,&eventObject,TRUE,WSA_INFINITE,FALSE);
			WSAGetOverlappedResult(sock,&overlapped,&sendBytes,FALSE,NULL);
		}
		else ErrorHandling("WSASend error");
	}

	printf("Send data size : %d \n",sendBytes);
	WSACloseEvent(eventObject);
	closesocket(sock);
	WSACleanup();
}