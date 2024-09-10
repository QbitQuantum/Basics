void ConsoleRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	try
	{
		std::string username;
		Poco::OSP::Web::WebSession::Ptr pSession;
		{
			Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = _pContext->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
			if (pWebSessionManagerRef)
			{
				Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
				pSession = pWebSessionManager->find(_pContext->thisBundle()->properties().getString("websession.id"), request);
				username = pSession->getValue<std::string>("username", "");
			}
		}	
	
		if (!username.empty())
		{
			Poco::Net::WebSocket webSocket(request, response);
			_pContext->logger().information(Poco::format("Console WebSocket connection established with %s.", request.clientAddress().toString()));
			forwardMessages(webSocket);
		}
		else
		{
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
			response.setContentLength(0);
			response.send();
		}
	}
	catch (Poco::Net::WebSocketException& exc)
	{
		_pContext->logger().log(exc);
		switch (exc.code())
		{
		case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
			response.set("Sec-WebSocket-Version", Poco::Net::WebSocket::WEBSOCKET_VERSION);
			// fallthrough
		case Poco::Net::WebSocket::WS_ERR_NO_HANDSHAKE:
		case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
		case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			response.setContentLength(0);
			response.send();
			break;
		}
	}
}