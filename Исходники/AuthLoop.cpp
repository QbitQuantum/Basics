void AuthLoop(CONNECT_INFO* cfg, Ref< UsersPool > OnlineUsers, Ref< CrossThreadQueue< string > > OutputQueue) {
	RakPeerInterface* rakServer = RakNetworkFactory::GetRakPeerInterface();

	PacketFileLogger* msgFileHandler = NULL;
	if (cfg->logFile) {
		msgFileHandler = new PacketFileLogger();
		rakServer->AttachPlugin(msgFileHandler);
	}

	InitSecurity(rakServer, cfg->useEncryption);
	SocketDescriptor socketDescriptor(cfg->listenPort, 0);

	if (rakServer->Startup(8, 30, &socketDescriptor, 1)) {
		stringstream s;
		s << "auth started! Listening on: " << cfg->listenPort << "\n";
		OutputQueue->Insert(s.str());
	} else QuitError("auth server init error!");
	rakServer->SetMaximumIncomingConnections(8);

	if (msgFileHandler != NULL) msgFileHandler->StartLog(".\\logs\\auth");

	Packet* packet;

	while (!LUNIterminate) {
		RakSleep(30);	// This sleep keeps RakNet responsive
		packet = rakServer->Receive();
		if (packet == NULL) continue;
		PrintPacketInfo(packet, msgFileHandler);

		switch (packet->data[0]) {
			case ID_LEGO_PACKET:

				switch (packet->data[1]) {
					case LUNI_INITAW:
						if (packet->data[3] == 0) {	// thats just a formality so far since no other numbers occured for this case
							// response: 00, 00
							auto v = OpenPacket(".\\auth\\init_aw.bin");
							// bytes 8-10 is the game version (same numbers are mentioned in the game log)
							// the client expects it to be the same that he sent (otherwise he displays "server is being updated" and disconnects)
							ServerSendPacket(rakServer, v, packet->systemAddress);
						}
						break;

					case LUNI_LOGIN: //user logging into server
						{
							auto usr = HandleUserLogin(rakServer, packet, cfg, OnlineUsers);
							if( usr != NULL ) OutputQueue->Insert("\n" + usr->GetUsername() + " Logged-in\n");
						#ifdef DEBUG
							else OutputQueue->Insert("\n Login failed!\n");
						#endif
						}
						break;

					default:
						stringstream s;
						s << "\nauth received unknow pakcet: " << RawDataToString(packet->data, packet->length) << endl;
						OutputQueue->Insert(s.str());
				}

				break;

			case ID_NEW_INCOMING_CONNECTION:
#			ifdef DEBUG
				OutputQueue->Insert("\n Auth is receiving a new connection...\n");
			#endif
				break;

			case ID_DISCONNECTION_NOTIFICATION: // do nothing
				break;

			default:
				stringstream s;
				s << "\nauth received unknow pakcet: " << RawDataToString(packet->data, packet->length) << endl;
				OutputQueue->Insert(s.str());
		}

		rakServer->DeallocatePacket(packet);
	}

	stringstream s;
	s << "Quitting auth\n";
	OutputQueue->Insert(s.str());

	rakServer->Shutdown(0);
	RakNetworkFactory::DestroyRakPeerInterface(rakServer);
}