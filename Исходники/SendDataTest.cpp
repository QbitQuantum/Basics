// Function for server
void vServerConnection( int iListenPort )
{
	SocketObject	ServerSocketObject;
	SocketObject	ClientSocketObject;
	//Data can be greater than 128 in length, it's just set to 128 for efficiency.
	//char			DataPacket[128];				// Data packet to receive//original version
	char			DataPacket[1024];				// Data packet to receive
	memset(DataPacket, 0, 1024);
	int				iBytesReceived = 0;				// # of bytes received
	
	cout << "<Server> Attempting to listen on Port " << iListenPort << endl;
	
	// Attempt to start the server
	if ( ServerSocketObject.Bind( iListenPort ) )
	{
		cout << "<Server> Listening" << endl;
		
		// Listen for connection on the Listen port, 
		ServerSocketObject.Listen();
		
		// Accept the connection
		ServerSocketObject.Accept( ClientSocketObject );
		cout << "<Server> Client Connected to Port " << iListenPort << endl;
		
		// Receive data
		//iBytesReceived = ClientSocketObject.Recv(&DataPacket[0], 128, 0);//original version
		iBytesReceived = ClientSocketObject.Recv(&DataPacket[0], 1024, 0);
		printf("%s\n", strerror(errno));
		cout << "<Server> Received " << iBytesReceived << " Bytes" << endl;
		cout << "<Server> Data Received = " << DataPacket << endl;

		// Disconnect the client
		ClientSocketObject.Disconnect();
		cout << "<Server> Client Disconnected" << endl;
	}
	else
	{
		cout << "<Server> Failed to Listen" << endl;
	}
}