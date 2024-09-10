	int Broadcast( int sd,char* message, int buffSize, SockAddr &addr )
	{
		int broadcast = 1;    
		setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(int));
		int bytes_sent = SendTo(sd,message,buffSize,addr);
		broadcast = 0;
		setsockopt(sd, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(int));
		return bytes_sent;
	}