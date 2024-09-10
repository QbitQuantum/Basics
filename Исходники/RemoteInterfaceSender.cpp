bool RemoteInterfaceSender::sendMessage(RemoteInterfaceMessage* message) {
	// Do we have a valid destination?
	if(message && message->destinationIp != "" && message->destinationPort != 0) {

		// Init socket
		QUdpSocket socket;
		if(!socket.bind(QHostAddress(server->ip), server->port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
			// Show error
			Debug::error("[RemoteInterfaceSender] could not bind");
			return false;
		} else {
			// Add port and ip keys
			if(socket.localAddress().toString() != server->ip) 	message->properties->insert("reply-ip",socket.localAddress().toString());
			if(socket.localPort() != server->port) 				message->properties->insert("reply-port",QString("%1").arg(socket.localPort()));

			// Write to socket
			socket.writeDatagram(message->toString().toAscii(), QHostAddress(message->destinationIp), message->destinationPort);

			// Add to sent list
			server->addMessageToSent(message);

			// Show what happened
			Debug::print("[RemoteInterfaceSender] sent %1 message to %2:%3", message->type, message->destinationIp, message->destinationPort);
			return true;
		}

	} else {
		// Show error
		Debug::warning("[RemoteInterfaceSender] message destination must be specified!");
		return false;
	}
}