void CNullModem::Disconnect() {
	removeEvent(SERIAL_POLLING_EVENT);
	removeEvent(SERIAL_RX_EVENT);
	// it was disconnected; free the socket and restart the server socket
	LOG_MSG("Serial%d: Disconnected.",COMNUMBER);
	delete clientsocket;
	clientsocket=0;
	setDSR(false);
	setCTS(false);
	setCD(false);
	
	if (serverport) {
		serversocket = new TCPServerSocket(serverport);
		if (serversocket->isopen) 
			setEvent(SERIAL_SERVER_POLLING_EVENT, 50);
		else delete serversocket;
	} else if (dtrrespect) {
		setEvent(SERIAL_NULLMODEM_DTR_EVENT,50);
		DTR_delta = getDTR(); // try to reconnect the next time DTR is set
	}
}