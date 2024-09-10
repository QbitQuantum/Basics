float receive(){

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Threado Starto"));
	UE_LOG(YourLog, Log, TEXT("Threado Starto"));
	//while (true){
	//	if (killThread) return 0;
	//killThread = true;
	//}
	//while (true){ GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, TEXT("tick")); }


	SOCKET sd;
	unsigned short int port = 5555;
	struct sockaddr_in server, client;
	WSADATA wsaData;

	/* Open windows connection */
	if (WSAStartup(0x0101, &wsaData) != 0)//variable w is a structure of WSADATA form.
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Could not open Windows connection"));
		fprintf(stderr, "Could not open Windows connection.\n");
		UE_LOG(YourLog, Fatal, TEXT("Could not open Windows connection.\n"));
		return 1;
	}

	/* Open a datagram socket */
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == INVALID_SOCKET)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Could not create socket"));
		fprintf(stderr, "Could not create socket.\n");
		UE_LOG(YourLog, Fatal, TEXT("Could not create socket.\n"));
		WSACleanup();
		return 2;
	}

	//non blocking stuff I think
	u_long iMode = 1;
	ioctlsocket(sd, FIONBIO, &iMode);

	/* Clear out server struct */
	memset((void *)&server, '\0', sizeof(struct sockaddr_in));

	/* Set family and port */
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	/* Set address automatically if desired */

	/* automatically get host name of this computer */
	//int errorCode;
	char host_name[256];
	gethostname(host_name, sizeof(host_name));
	hostent *hp = gethostbyname(host_name);

	/* Check for NULL pointer */
	if (hp != NULL)
	{
		/* Assign the address */ 
		unsigned int a, b, c, d;
		server.sin_addr.S_un.S_un_b.s_b1 = a = hp->h_addr_list[0][0];
		server.sin_addr.S_un.S_un_b.s_b2 = b = hp->h_addr_list[0][1];
		server.sin_addr.S_un.S_un_b.s_b3 = c = hp->h_addr_list[0][2];
		server.sin_addr.S_un.S_un_b.s_b4 = d = hp->h_addr_list[0][3];

		FString Fs = FString(ANSI_TO_TCHAR(host_name));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Fs);
		std::cout << "Hostname: " << host_name << " " << ((int)hp->h_addr_list[0][0] & 0x256) << "." << (unsigned int)hp->h_addr_list[0][1] << "." << (unsigned int)hp->h_addr_list[0][2] << "." << (unsigned int)hp->h_addr_list[0][3] << std::endl;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Fs);
		UE_LOG(YourLog, Warning, TEXT("found address: %d.%d.%d.%d"), a, b, c, d);
	}

	/* hardcoded address as backup */
	else
	{
		fprintf(stderr, "Failed to discover hostname. Defaulted to 192.168.1.107. \n");
		UE_LOG(YourLog, Log, TEXT("Failed to discover hostname. Defaulted to 192.168.1.104. \n"));
		server.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)192;
		server.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)168;
		server.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)1;
		server.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)104;
	}

	//doesn't crash when stalled here, bind seems to be the tricky part
	UE_LOG(YourLog, Log, TEXT("about to bind"));

	/* Bind address to socket */
	if (bind(sd, (struct sockaddr *)&server,
		sizeof(struct sockaddr_in)) == -1)
	{
		int errnum = -1;
		errnum = WSAGetLastError();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Could not bind address to socket"));
		fprintf(stderr, "Could not bind address to socket.\n");
		//UE_LOG(YourLog, Warning, TEXT("tryibng to print message"));
		//UE_LOG(YourLog, Warning, TEXT("Could not bind address to socket due to %d.\n"), errnum);//Seems like Fatal logging triggers a breakpoint
		UE_LOG(YourLog, Fatal, TEXT("Could not bind address to socket due to %d.\n"), errnum);//Fatal rather than warning maybe
		closesocket(sd);
		WSACleanup();
		return errnum;
	}

	int client_length = (int)sizeof(struct sockaddr_in);
	int bytes_received;

	/*while (true){
		Sleep(50);
		if (killThread == true) {
			//closeConnection(sd); 
			
			fprintf(stderr, "KillThread: ending server for FreePIE.\n");
			UE_LOG(YourLog, Warning, TEXT("KillThread: ending server for FreePIE.\n"));
			closesocket(sd);
			WSACleanup();
			return 0; }
	}*/

	//FString path = FPaths::GameDir() + "/DataLog/log.txt";
	time_t timeStamp = time(0);
	char* timeString = std::ctime(&timeStamp);	

	struct tm * timeinfo;
	timeinfo = localtime(&timeStamp);

	char buffer[80];
	//strftime(buffer, 200, "%S-%M-%H_%a-%b-%G", timeinfo);
	strftime(buffer, 200, "%S-%M-%H_%d-%b-%Y", timeinfo);
	//FString path = FPaths::GameDir() + "/DataLog/" + buffer + ".csv";
	userID = FString::FromInt(time(0));
	FString path = FPaths::GameDir() + "/DataLog/" + userID + "A" +".csv";
	DataLogFile.open(*path, std::ios::out);
	DataLogFile << "acceleration:x,y,z,Orientation:yaw,pitch,roll,PredGravityX,PredGravityY,PredGravityZ\n";

	while (true){
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("reading"));
		//UE_LOG(YourLog, Warning, TEXT("KillThread is %d"), killThread);
		if (killThread == true) {
			fprintf(stderr, "KillThread: ending server for FreePIE.\n");
			DataLogFile.close();
			if (!recording) std::remove(TCHAR_TO_ANSI(*path));//if recording was never started delete record file
			//UE_LOG(YourLog, Warning, TEXT("KillThread: ending server for FreePIE.\n"));//this will break because if killthread then game is closing
			closesocket(sd);
			WSACleanup();
			return 5555;
		}
		//}
		//std::cout << "Reading a datagram" << std::endl;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Black, TEXT("about to read")); //GEngine->
		/* Receive bytes from client */
		bytes_received = recvfrom(sd, UDPReceiveBuffer, BUFFER_SIZE, 0,
			(struct sockaddr *)&client, &client_length);
		/*if (bytes_received < 0)
		{
		//while (true){
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Black, TEXT("Failed to receive datagram"));
		//}
		fprintf(stderr, "Could not receive datagram.\n");
		closesocket(sd);
		WSACleanup();
		//pollingThread.~thread();
		//ExitThread(0);
		return 4444;
		}*/

		int nError = WSAGetLastError();
		if (nError != WSAEWOULDBLOCK&&nError != 0)
		{
			UE_LOG(YourLog, Log, TEXT("Winsock error code\r\n"));
			std::cout << "Winsock error code: " << nError << "\r\n";
			std::cout << "Server disconnected!\r\n";
			return 9000;
		}

		else if (bytes_received > 0) parseDatagram((char*)UDPReceiveBuffer);
		//std::cout << (int)client.sin_addr.S_un.S_un_b.s_b1 << '.' << (int)client.sin_addr.S_un.S_un_b.s_b2 << '.' << (int)client.sin_addr.S_un.S_un_b.s_b3 << '.' << (int)client.sin_addr.S_un.S_un_b.s_b4 << std::endl;
		//fprintf(stderr, buffer);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sleeping"));
		Sleep(3);
	}
	return 2;
}