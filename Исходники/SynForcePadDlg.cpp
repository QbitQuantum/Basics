void CSynForcePadDlg::EviaDadosViaSocket(ULONG ul,	LONG lX, LONG lY, LONG lZ, long lForce, int evento)
{

	   // evento = 1 -> TOUCH_DOWN
	   // evento = 2 -> TOUCH_MOVE
	   // evento = 3 -> TOUCH_UP
	
	
	  		// Aqui coloco as definições do SOCKET
		int wsaret=WSAStartup(0x101,&wsaData);
	
		if(wsaret)	
			return;
		
		conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		if(conn==INVALID_SOCKET)
			return;


		int porta = 123;

		sprintf(ServerNameInChar,"127.0.0.1");


		if(inet_addr((char*) ServerNameInChar)==INADDR_NONE)
		{
			hp=gethostbyname(ServerNameInChar);
		}
		else
		{
			addr=inet_addr(ServerNameInChar);
			hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
		}
		if(hp==NULL)
		{
			closesocket(conn);
			return;
		}

		server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
		server.sin_family=AF_INET;
		server.sin_port=htons(porta);

		if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
		{
			closesocket(conn);
			return;	
		}

	    // Fim da inicialização do socket

	
		// SEQUENCIA DE DADOS: Finger %d, XRaw %d, YRaw %d, ZRaw %d, Force %d, evento
	// sprintf(buff,"Ola DADOS: Finger %d, XRaw %d, YRaw %d, ZRaw %d, Force %d",ul, lX, lY, lZ, lForce);
	// sprintf(buff,"Ola DADOS: Finger %d, X %d, Y %d, Z %d, F %d, E %d",ul, lX, lY, lZ, lForce, evento);

		sprintf(buff,"Ola %d,%d,%d,%d,%d,%d",ul, lX, lY, lZ, lForce, evento);
	send(conn,buff,strlen(buff),0);


	 // Finalizações do socket
 closesocket(conn);

 WSACleanup();

 
}