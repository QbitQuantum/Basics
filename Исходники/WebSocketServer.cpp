	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		Application& app = Application::instance();
		try
		{
			WebSocket ws(request, response);
			printf("getReceiveTimeout %d\n", ws.getReceiveTimeout().totalSeconds());
			app.logger().information("WebSocket connection established.");
			char buffer[1024];
			int flags;
			int n;
			do
			{
				n = ws.receiveFrame(buffer, sizeof(buffer), flags);
				app.logger().information(Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));
				ws.sendFrame(buffer, n, flags);
			}
			while (n > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
			app.logger().information("WebSocket connection closed.");
		}
		catch (WebSocketException& exc)
		{
			app.logger().log(exc);
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

		app.logger().information("WebSocket connection terminated.");
	}