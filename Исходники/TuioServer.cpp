TuioServer::TuioServer(const char* address, int port)
{
	//InitializeNetworking();
	long unsigned int ip = GetHostByName(address);
	transmitSocket = new UdpTransmitSocket(IpEndpointName(ip, port));
	
	
	if ((strcmp(address, "localhost") == 0) || (strcmp(address, "127.0.0.1") == 0))  sprintf(source, "reacTIVision");
	else { 
		
		char hostname[64];
		char *source_addr = NULL;
		struct hostent *hp = NULL;
		struct in_addr *addr = NULL;
		
		gethostname(hostname, 64);
		hp = gethostbyname(hostname);
		
		if (hp==NULL) {
			sprintf(hostname, "%s.local", hostname);
			hp = gethostbyname(hostname);
		}
		
		if (hp!=NULL) {
			/*for (int i = 0; hp->h_addr_list[i] != 0; ++i) {
				addr = (struct in_addr *)(hp->h_addr_list[i]);
				//std::cout << inet_ntoa(*addr) << std::endl;
			}*/
			addr = (struct in_addr *)(hp->h_addr_list[0]);
			source_addr = inet_ntoa(*addr);
		} else {
			//generate a random internet address
			srand ( (unsigned int)time(NULL) );
			int r = rand();
			addr = (struct in_addr*)&r;
			source_addr = inet_ntoa(*addr);
		}		
		sprintf(source, "reacTIVision@%s", source_addr); 
	}
	//printf("%s\n",source);
	
	objBuffer = new char[IP_MTU_SIZE];
	objPacket = new osc::OutboundPacketStream(objBuffer,IP_MTU_SIZE);
	(*objPacket) << osc::BeginBundleImmediate;
	(*objPacket) << osc::BeginMessage( "/tuio/2Dobj") << "source" << source << osc::EndMessage;

	curBuffer = new char[IP_MTU_SIZE];
	curPacket = new osc::OutboundPacketStream(curBuffer,IP_MTU_SIZE);
	(*curPacket) << osc::BeginBundleImmediate;
	(*curPacket) << osc::BeginMessage( "/tuio/2Dcur") << "source" << source << osc::EndMessage;

	objMessages=0;
	curMessages=0;
	running=true;
}