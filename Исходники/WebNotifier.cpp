	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		/// Creates WebSocket and accepts the connection request from web client.
	{
		try
		{
			if (!_pWS)
			{
				_pWS = new WebSocket(request, response);
				Timespan ts(600, 0);
				_pWS->setReceiveTimeout(ts);
				_pWS->setSendTimeout(ts);
			}
			std::cout << std::endl << "WebSocket connection established." << std::endl << PROMPT;

			char buffer[1024];
			int n, count = 0;
			do
			{
				n = _pWS->receiveFrame(buffer, sizeof(buffer), _flags);
			}
			while (n > 0 || (_flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
				std::cout << "WebSocket connection closed." << std::endl;
		}
		catch (WebSocketException& exc)
		{
			std::cout << exc.displayText() << std::endl;
			switch (exc.code())
			{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
		}
	}