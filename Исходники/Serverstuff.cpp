void ServerCF::Accept()
{
	struct sockaddr_in client;

	int len;


	len = sizeof( client );

        ToClientSocket = accept(serverSocket, (struct sockaddr*)&client, &len);
	if(ToClientSocket < 0){
		//error handling
	}else{
		WSAAsyncSelect(serverSocket,g_pWindow,WM_TOCLIENTSOCKET,(FD_READ|FD_CLOSE));
		//we don't want more than one connection, cause it crashes
		closesocket(serverSocket);
	}
}