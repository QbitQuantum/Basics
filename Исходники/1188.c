/*connect host:port*/
SOCKET Conecta(char *Host, short puerto)
{
	/*struct for make the socket*/
	WSADATA wsaData;
	SOCKET Winsock;//listener socket
	/*two structures for connect*/
	struct sockaddr_in Winsock_In;
	struct hostent *Ip;

	/*start the socket*/
	WSAStartup(MAKEWORD(2,2), &wsaData);
	/*make*/
	Winsock=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,(unsigned int)NULL,(unsigned int)NULL);

	//check socket status
	if(Winsock==INVALID_SOCKET)
	{
		/*exit*/
		WSACleanup();
		return -1;
	}

	/*complete the struct*/
	Ip=gethostbyname(Host);
	Winsock_In.sin_port=htons(puerto);
	Winsock_In.sin_family=AF_INET;
	Winsock_In.sin_addr.s_addr=inet_addr(inet_ntoa(*((struct in_addr *)Ip->h_addr)));

	/*connect*/
	if(WSAConnect(Winsock,(SOCKADDR*)&Winsock_In,sizeof(Winsock_In),NULL,NULL,NULL,NULL)==SOCKET_ERROR)
	{
		/*end*/
		WSACleanup();
		return -1;
	}

	return Winsock;
}