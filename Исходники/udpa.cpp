void serverEarlyRetrans(UdpSocket &sock, const int max, int message[], 
						int windowSize, int loss) {
	cerr << "Server early retrans test:" << endl;

	int ack;				// Holds the acknowledgment
	bool serverArray[max];	// Holds messages that server needs from client
	int sequence = 0;		// The sequence # counter

	// Init values in serverArray
	for (int i = 0; i < max; i++)
		serverArray[i] = false;

	while (sequence < max) {
		// Read the message from the client
		sock.recvFrom((char *)message, MSGSIZE);

		// Drop packets randomly
		if (rand() % 100 < loss) {
			continue;
		}

		// Got needed message from client 
		if (message[0] == sequence) {
			// Set the serverArray at sequence
			serverArray[sequence] = true;
			
			// Find the lowest number the server needs
			while (sequence < max) {
				if (serverArray[sequence] == false) {
					break;
				}
				sequence++;
			}
			
			// Send an ACK for previous seq #
			ack = sequence - 1;
		} 
		else {
			// Set the serverArray at message
			serverArray[message[0]] = true;
			
			// Send the number that is still needed 
			ack = sequence;
		}
		// Send the acknowledgment
		sock.ackTo((char *)&ack, sizeof(ack));
	}

}