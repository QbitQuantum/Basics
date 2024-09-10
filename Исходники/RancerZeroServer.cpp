int main(int argc, char** argv) {
	RakNet::RakPeerInterface *server = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet* p;
	unsigned char packetIdentifier;
	RakNet::SystemAddress clientID = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
	RakNet::RakNetStatistics *rss;
	RakNet::SocketDescriptor socketDescriptors[2];
	char portstring[30];

	socketDescriptors[0].port = SERVER_PORT;
	socketDescriptors[0].socketFamily = AF_INET; // Test out IPV4
	socketDescriptors[1].port = SERVER_PORT;
	socketDescriptors[1].socketFamily = AF_INET6; // Test out IPV6
	if (server->Startup(4, socketDescriptors, 2) != RakNet::RAKNET_STARTED) {
		std::cout << "IPV6 not supported, starting with IPV4-only interface..." << std::endl;
		if (server->Startup(4, socketDescriptors, 1) != RakNet::RAKNET_STARTED) {
			std::cerr << "Error creating server, exiting..." << std::endl;
			exit(-1);
		}
	}
	std::cout << "Server started successfully. Listening on port " << SERVER_PORT << std::endl;
	server->SetMaximumIncomingConnections(20);
	server->SetOccasionalPing(true);
	server->SetUnreliableTimeout(1000);

	DataStructures::List<RakNet::RakNetSocket2*> sockets;
	server->GetSockets(sockets);
	std::cout << "Socket addresses used by RakNet:" << std::endl;
	for (unsigned int i = 0; i < sockets.Size(); i++) {
		printf("%i. %s\n", i + 1, sockets[i]->GetBoundAddress().ToString(true));
	}
	char message[2048];

	// Loop for input
	while (1)
	{

		// This sleep keeps RakNet responsive
		RakSleep(30);

		if (kbhit())
		{
			// Notice what is not here: something to keep our network running.  It's
			// fine to block on gets or anything we want
			// Because the network engine was painstakingly written using threads.
			Gets(message, sizeof(message));

			if (strcmp(message, "quit") == 0)
			{
				puts("Quitting.");
				break;
			}

			if (strcmp(message, "stat") == 0)
			{
				rss = server->GetStatistics(server->GetSystemAddressFromIndex(0));
				StatisticsToString(rss, message, 2);
				printf("%s", message);
				printf("Ping %i\n", server->GetAveragePing(server->GetSystemAddressFromIndex(0)));

				continue;
			}

			if (strcmp(message, "ping") == 0)
			{
				server->Ping(clientID);

				continue;
			}

			if (strcmp(message, "pingip") == 0)
			{
				printf("Enter IP: ");
				Gets(message, sizeof(message));
				printf("Enter port: ");
				Gets(portstring, sizeof(portstring));
				if (portstring[0] == 0)
					strcpy(portstring, "1234");
				server->Ping(message, atoi(portstring), false);

				continue;
			}

			if (strcmp(message, "kick") == 0)
			{
				server->CloseConnection(clientID, true, 0);

				continue;
			}

			if (strcmp(message, "getconnectionlist") == 0)
			{
				printf("Connections:\n");
				RakNet::SystemAddress systems[10];
				unsigned short numConnections = 10;
				server->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
				for (int i = 0; i < numConnections; i++)
				{
					printf("%i. %s\n", i + 1, systems[i].ToString(true));
				}
				continue;
			}

			if (strcmp(message, "ban") == 0)
			{
				printf("Enter IP to ban.  You can use * as a wildcard\n");
				Gets(message, sizeof(message));
				server->AddToBanList(message);
				printf("IP %s added to ban list.\n", message);

				continue;
			}


			// Message now holds what we want to broadcast
			char message2[2048];
			// Append Server: to the message so clients know that it ORIGINATED from the server
			// All messages to all clients come from the server either directly or by being
			// relayed from other clients
			message2[0] = 0;
			const static char prefix[] = "Server: ";
			strncpy(message2, prefix, sizeof(message2));
			strncat(message2, message, sizeof(message2) - strlen(prefix) - 1);

			// message2 is the data to send
			// strlen(message2)+1 is to send the null terminator
			// HIGH_PRIORITY doesn't actually matter here because we don't use any other priority
			// RELIABLE_ORDERED means make sure the message arrives in the right order
			// We arbitrarily pick 0 for the ordering stream
			// RakNet::UNASSIGNED_SYSTEM_ADDRESS means don't exclude anyone from the broadcast
			// true means broadcast the message to everyone connected
			server->Send(message2, (const int)strlen(message2) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}

		// Get a packet from either the server or the client

		for (p = server->Receive(); p; server->DeallocatePacket(p), p = server->Receive())
		{
			// We got a packet, get the identifier with our handy function
			packetIdentifier = GetPacketIdentifier(p);

			// Check if this is a network message packet
			switch (packetIdentifier)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				printf("ID_DISCONNECTION_NOTIFICATION from %s\n", p->systemAddress.ToString(true));;
				break;


			case ID_NEW_INCOMING_CONNECTION:
				// Somebody connected.  We have their IP now
				printf("ID_NEW_INCOMING_CONNECTION from %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
				clientID = p->systemAddress; // Record the player ID of the client

				printf("Remote internal IDs:\n");
				for (int index = 0; index < MAXIMUM_NUMBER_OF_INTERNAL_IDS; index++)
				{
					RakNet::SystemAddress internalId = server->GetInternalID(p->systemAddress, index);
					if (internalId != RakNet::UNASSIGNED_SYSTEM_ADDRESS)
					{
						printf("%i. %s\n", index + 1, internalId.ToString(true));
					}
				}

				break;

			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
				break;

			case ID_CONNECTED_PING:
			case ID_UNCONNECTED_PING:
				printf("Ping from %s\n", p->systemAddress.ToString(true));
				break;

			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				printf("ID_CONNECTION_LOST from %s\n", p->systemAddress.ToString(true));;
				break;

			default:
				// The server knows the static data of all clients, so we can prefix the message
				// With the name data
				printf("%s\n", p->data);

				// Relay the message.  We prefix the name for other clients.  This demonstrates
				// That messages can be changed on the server before being broadcast
				// Sending is the same as before
				sprintf(message, "%s", p->data);
				server->Send(message, (const int)strlen(message) + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, p->systemAddress, true);

				break;
			}

		}
	}

	server->Shutdown(300);
	// We're done with the network
	RakNet::RakPeerInterface::DestroyInstance(server);


}