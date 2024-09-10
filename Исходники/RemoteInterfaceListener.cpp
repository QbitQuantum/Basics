void RemoteInterfaceListener::run() {

	// Init socket
	stopRequested = false;
	QUdpSocket socket;
	if(!socket.bind(QHostAddress(server->ip), server->port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
		// Show error
		Debug::print("[RemoteInterfaceListener] could not bind");
		stopRequested = true;
	}

	// Enter processing loop...
	while (stopRequested == false) {

		// Process all pending datagrams
		while(socket.hasPendingDatagrams() && !stopRequested) {
			// Get the data from socket
			QByteArray data;
			data.resize(socket.pendingDatagramSize());
			QHostAddress sender;
			quint16 senderPort;
			socket.readDatagram(data.data(), data.size(), &sender, &senderPort);

			// Extract message and keep track of the pointer in the server
			RemoteInterfaceMessage *message = new RemoteInterfaceMessage(&data);
			message->sourceIp = sender.toString();
			message->sourcePort = senderPort;
			message->destinationIp = server->ip;
			message->destinationPort = server->port;
			server->messages->append(message);

			// Show reception and pass on for processing...
			Debug::print("[RemoteInterfaceListener] received %1 message from %2:%3", message->type, sender.toString(), senderPort);
			server->processMessage(message);
		}

		// Sleep wait
		QThread::msleep(core->intSetting("RemoteInterface_ListenerInterval"));

	}
}