	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		Application& app = Application::instance();
		try
		{			
			std::string proto = request.get("Sec-WebSocket-Protocol", "");
			Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket;
			if (proto == "com.appinf.webtunnel.server/1.0")
			{
				response.set("Sec-WebSocket-Protocol", proto);
				pWebSocket = new Poco::Net::WebSocket(request, response);
				_portReflector.addServerSocket(pWebSocket, "ac9667bb-6032-4267-af61-9a7aafd40479");
			}
			else if (proto == "com.appinf.webtunnel.client/1.0")
			{
				response.set("Sec-WebSocket-Protocol", proto);
				std::string portStr = request.get("X-WebTunnel-RemotePort", "");
				unsigned port;
				if (!portStr.empty() && Poco::NumberParser::tryParseUnsigned(portStr, port) && port > 0 && port < 65536)
				{
					pWebSocket = new Poco::Net::WebSocket(request, response);
					try
					{
						_portReflector.addClientSocket(pWebSocket, "ac9667bb-6032-4267-af61-9a7aafd40479", static_cast<Poco::UInt16>(port));
					}
					catch (Poco::NotFoundException&)
					{
						pWebSocket->shutdown(Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, "No connection to target available");
					}
				}
				else
				{
					pWebSocket = new Poco::Net::WebSocket(request, response);
					pWebSocket->shutdown(Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, "Missing or invalid X-WebTunnel-RemotePort header");
				}
			}
			else
			{
				pWebSocket = new Poco::Net::WebSocket(request, response);
				pWebSocket->shutdown(Poco::Net::WebSocket::WS_PROTOCOL_ERROR);
			}
		}
		catch (WebSocketException& exc)
		{
			app.logger().log(exc);
			switch (exc.code())
			{
			case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case Poco::Net::WebSocket::WS_ERR_NO_HANDSHAKE:
			case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
		}
	}