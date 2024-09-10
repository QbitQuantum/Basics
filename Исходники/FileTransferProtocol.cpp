int FileTransferProtocol::recvCommand(net::Socket &s, char &command) {
	char d;
	int bytes_received;
	bytes_received = s.recv(&d, 1, 0);
	if (bytes_received == SOCKET_ERROR || bytes_received != 1) {
		onTransferError("Could not receive direction from client!");
		return -1;
	}
	if (d != 'D' && d != 'U' && d != 'L' && d != 'Q') {
		onTransferError("Client sent invalid direction!");
		return -1;
	}
	command = d;
	return 0;
}