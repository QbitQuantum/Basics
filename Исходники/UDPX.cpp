	DWORD WINAPI ConnectThread(void* arg)
	{
		ConnectThreadArugments* args = (ConnectThreadArugments*)arg;
		UDPXAddress* Address = args->Address;
		ConnectionHandelerFn OnConnect = args->ConnectionHandeler;

		srand(time(NULL));
		int startsequence = INT_MIN + rand();
		
		BYTE pdata[5];
		pdata[0] = PacketType::Handshake;
		_WriteInt(startsequence, pdata, 1);
		
		Socket s;
		int Attempts = 5;
		std::cout<<Attempts;
		double Timeout = 1.0;

		PacketQueue* FirstNode = NULL;
		PacketQueue* LastestNode = NULL;
		
		while(Attempts >= 0)
		{
			s.Send(Address, (const char*)pdata, 5);
			--Attempts;
			
			while(true)
			{
				std::cout<<"Checking handshake.\n";
				BYTE packet[UDPX_MAXPACKETSIZE];
				UDPXAddress* Sender = new UDPXAddress();
				int recived = s.Receive(Sender, packet, UDPX_MAXPACKETSIZE);
				
				if(recived == -1) break;
				if(!Sender) break;

				std::cout<<Sender->Address<<" in rec\n";
				printf("%u in class\n", Sender->Address);
				
				
				if(Sender->Address == Address->Address) // make sure it's from the correct person.
				{
					std::cout<<"Got Packet.\n";
					if(recived == 5 && packet[0] == PacketType::HandshakeAck)
					{
						std::cout<<"Got Handshake.\n";
						int recsequence = _ReadInt(packet, 1);
						UDPXConnection* connection = new UDPXConnection(Sender);
						connection->m_ReciveSequence = recsequence; // Crashed here.
						OnConnect(connection);
						PacketQueue* Node = FirstNode;
						while(Node)
						{
							connection->ReciveRaw(Node->Data, Node->Length);

							PacketQueue* LastNode = Node;
							Node = Node->Next;
							delete LastNode;
						}
						return 0;
					}
					else
					{
						PacketQueue* Node = new PacketQueue();
						Node->Data = packet;
						Node->Length = recived;
						Node->Next = NULL;
						if(!FirstNode)
						{
							FirstNode = Node;
							LastestNode = Node;
						}
						else
						{
							LastestNode->Next = Node;
							LastestNode = Node;
						}
					}
				}
			}
			Sleep(Timeout * 1000);
		}
		if(FirstNode) // Lets free any data there may have been
		{
			PacketQueue* Node = FirstNode;
			while(Node)
			{
				PacketQueue* LastNode = Node;
				Node = Node->Next;
				free(LastNode);
			}
		}
		std::cout<<"Connection timed out.\n";
		OnConnect(NULL);
		return 0;
	}