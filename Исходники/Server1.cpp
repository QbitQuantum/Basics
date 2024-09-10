int __cdecl main(void)
{

	// Create a SOCKET for connecting to server


	// Setup the TCP listening socket

	Network  nt;
	int iResult;
	SOCKET ListenSocket;
	ListenSocket = nt.Bind("0.0.0.0", "5005");
	ListenSocket = nt.Listen(ListenSocket);
	SOCKET ClientSocket = nt.Accept(ListenSocket);
	char recvbuf[DEFAULT_BUFLEN];





	// Receive until the peer shuts down the connection
	do {

		nt.Recv(ClientSocket, recvbuf);
		// Echo the buffer back to the sender
		nt.Send(ClientSocket, "hello my name");

	} while (ClientSocket != INVALID_SOCKET);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}