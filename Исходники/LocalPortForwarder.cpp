void LocalPortForwarder::forward(Poco::Net::StreamSocket& socket)
{
	if (_logger.debug())
	{
		_logger.debug(Poco::format("Local connection accepted, creating forwarding connection to %s, remote port %hu", _remoteURI.toString(), _remotePort));
	}
	try
	{
		std::string path(_remoteURI.getPathEtc());
		if (path.empty()) path = "/";
		Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPRequest::HTTP_1_1);
		request.set(SEC_WEBSOCKET_PROTOCOL, WEBTUNNEL_PROTOCOL);
		request.set(X_WEBTUNNEL_REMOTEPORT, Poco::NumberFormatter::format(_remotePort));
		Poco::Net::HTTPResponse response;
		Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket = _pWebSocketFactory->createWebSocket(_remoteURI, request, response);
		if (response.get(SEC_WEBSOCKET_PROTOCOL, "") != WEBTUNNEL_PROTOCOL)
		{
			_logger.error("The remote host does not support the WebTunnel protocol.");
			pWebSocket->shutdown(Poco::Net::WebSocket::WS_PROTOCOL_ERROR);
			pWebSocket->close();
			socket.close();
			return;
		}

		_pDispatcher->addSocket(socket, new StreamSocketToWebSocketForwarder(_pDispatcher, pWebSocket), _localTimeout);
		_pDispatcher->addSocket(*pWebSocket, new WebSocketToStreamSocketForwarder(_pDispatcher, socket), _remoteTimeout);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error(Poco::format("Failed to open forwarding connection: %s", exc.displayText()));
		socket.close();
	}
}