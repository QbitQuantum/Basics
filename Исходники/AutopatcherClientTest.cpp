int main(int argc, char **argv)
{
	printf("A simple client interface for the advanced autopatcher.\n");
	printf("Use DirectoryDeltaTransfer for a simpler version of an autopatcher.\n");
	printf("Difficulty: Intermediate\n\n");

	printf("Client starting...");
	SystemAddress serverAddress=UNASSIGNED_SYSTEM_ADDRESS;
	AutopatcherClient autopatcherClient;
	FileListTransfer fileListTransfer;
	autopatcherClient.SetFileListTransferPlugin(&fileListTransfer);
	unsigned short localPort=0;
	if (argc>=6)
	{
		localPort=atoi(argv[5]);
	}
#ifdef USE_TCP
	PacketizedTCP packetizedTCP;
	if (packetizedTCP.Start(localPort,1)==false)
	{
		printf("Failed to start TCP. Is the port already in use?");
		return 1;
	}
	packetizedTCP.AttachPlugin(&autopatcherClient);
	packetizedTCP.AttachPlugin(&fileListTransfer);
#else
	RakPeerInterface *rakPeer;
	rakPeer = RakNetworkFactory::GetRakPeerInterface();
	SocketDescriptor socketDescriptor(localPort,0);
	rakPeer->Startup(1,0,&socketDescriptor, 1);
	// Plugin will send us downloading progress notifications if a file is split to fit under the MTU 10 or more times
	rakPeer->SetSplitMessageProgressInterval(10);
	rakPeer->AttachPlugin(&autopatcherClient);
	rakPeer->AttachPlugin(&fileListTransfer);
#endif
	printf("started\n");
	char buff[512];
	if (argc<2)
	{
		printf("Enter server IP: ");
		gets(buff);
		if (buff[0]==0)
			//	strcpy(buff, "94.198.81.195");
			strcpy(buff, "127.0.0.1");
	}
	else
		strcpy(buff, argv[1]);

#ifdef USE_TCP
	packetizedTCP.Connect(buff,60000,false);
#else
	rakPeer->Connect(buff, 60000, 0, 0);
#endif

	printf("Connecting...\n");
	char appDir[512];
	if (argc<3)
	{
		printf("Enter application directory: ");
		gets(appDir);
		if (appDir[0]==0)
		{
			strcpy(appDir, "C:/temp2");
		}
	}
	else
		strcpy(appDir, argv[2]);
	char appName[512];
	if (argc<4)
	{
		printf("Enter application name: ");
		gets(appName);
		if (appName[0]==0)
			strcpy(appName, "TestApp");
	}
	else
		strcpy(appName, argv[3]);

	bool patchImmediately=argc>=5 && argv[4][0]=='1';

	if (patchImmediately==false)
		printf("Hit 'q' to quit, 'p' to patch, 'c' to cancel the patch. 'r' to reconnect. 'd' to disconnect.\n");
	else
		printf("Hit 'q' to quit, 'c' to cancel the patch.\n");

	char ch;
	Packet *p;
	while (1)
	{
#ifdef USE_TCP
		SystemAddress notificationAddress;
		notificationAddress=packetizedTCP.HasCompletedConnectionAttempt();
		if (notificationAddress!=UNASSIGNED_SYSTEM_ADDRESS)
		{
			printf("ID_CONNECTION_REQUEST_ACCEPTED\n");
			serverAddress=notificationAddress;
		}
		notificationAddress=packetizedTCP.HasNewIncomingConnection();
		if (notificationAddress!=UNASSIGNED_SYSTEM_ADDRESS)
			printf("ID_NEW_INCOMING_CONNECTION\n");
		notificationAddress=packetizedTCP.HasLostConnection();
		if (notificationAddress!=UNASSIGNED_SYSTEM_ADDRESS)
			printf("ID_CONNECTION_LOST\n");


		p=packetizedTCP.Receive();
		while (p)
		{
			if (p->data[0]==ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR)
			{
				char buff[256];
				RakNet::BitStream temp(p->data, p->length, false);
				temp.IgnoreBits(8);
				stringCompressor->DecodeString(buff, 256, &temp);
				printf("ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR\n");
				printf("%s\n", buff);
			}
			else if (p->data[0]==ID_AUTOPATCHER_FINISHED)
				printf("ID_AUTOPATCHER_FINISHED\n");
			else if (p->data[0]==ID_AUTOPATCHER_RESTART_APPLICATION)
				printf("Launch \"AutopatcherClientRestarter.exe autopatcherRestart.txt\"\nQuit this application immediately after to unlock files.\n");

			packetizedTCP.DeallocatePacket(p);
			p=packetizedTCP.Receive();
		}
#else
		p=rakPeer->Receive();
		while (p)
		{
			if (p->data[0]==ID_DISCONNECTION_NOTIFICATION)
				printf("ID_DISCONNECTION_NOTIFICATION\n");
			else if (p->data[0]==ID_CONNECTION_LOST)
				printf("ID_CONNECTION_LOST\n");
			else if (p->data[0]==ID_CONNECTION_REQUEST_ACCEPTED)
			{
				printf("ID_CONNECTION_REQUEST_ACCEPTED\n");
				serverAddress=p->systemAddress;
			}
			else if (p->data[0]==ID_CONNECTION_ATTEMPT_FAILED)
				printf("ID_CONNECTION_ATTEMPT_FAILED\n");
			else if (p->data[0]==ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR)
			{
				char buff[256];
				RakNet::BitStream temp(p->data, p->length, false);
				temp.IgnoreBits(8);
				stringCompressor->DecodeString(buff, 256, &temp);
				printf("ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR\n");
				printf("%s\n", buff);
			}
			else if (p->data[0]==ID_AUTOPATCHER_FINISHED)
				printf("ID_AUTOPATCHER_FINISHED\n");
			else if (p->data[0]==ID_AUTOPATCHER_RESTART_APPLICATION)
				printf("Launch \"AutopatcherClientRestarter.exe autopatcherRestart.txt\"\nQuit this application immediately after to unlock files.\n");

			rakPeer->DeallocatePacket(p);
			p=rakPeer->Receive();
		}
#endif

		if (kbhit())
			ch=getch();
		else
			ch=0;

		if (ch=='q')
			break;
		else if (ch=='r')
		{
#ifdef USE_TCP
			packetizedTCP.Connect(buff,60000,false);
#else
			rakPeer->Connect(buff, 60000, 0, 0);
#endif
		}
		else if (ch=='d')
		{
#ifdef USE_TCP
			packetizedTCP.CloseConnection(serverAddress);
#else
			rakPeer->CloseConnection(serverAddress, true);
#endif
		}
		else if (ch=='p' || (serverAddress!=UNASSIGNED_SYSTEM_ADDRESS && patchImmediately==true))
		{
			patchImmediately=false;
			char lastUpdateDate[128];
			char restartFile[512];
			strcpy(restartFile, appDir);
			strcat(restartFile, "/autopatcherRestart.txt");
		//	printf("Enter last update date (only newer updates retrieved) or nothing to get all updates\n");
		//	gets(lastUpdateDate);
			lastUpdateDate[0]=0;

			if (autopatcherClient.PatchApplication(appName, appDir, lastUpdateDate, serverAddress, &transferCallback, restartFile, argv[0]))
			{
				printf("Patching process starting.\n");
			}
			else
			{
				printf("Failed to start patching.\n");
			}
		}
		else if (ch=='c')
		{
			autopatcherClient.Clear();
			printf("Autopatcher cleared.\n");
		}

		RakSleep(30);
	}

	// Dereference so the destructor doesn't crash
	autopatcherClient.SetFileListTransferPlugin(0);

#ifdef USE_TCP
	packetizedTCP.Stop();
#else
	rakPeer->Shutdown(500,0);
	RakNetworkFactory::DestroyRakPeerInterface(rakPeer);
#endif
	return 1;
}