void MsgHandlerJSON::Run() {
	std::string msg;
	syslog(LOG_INFO, "JSON message handler started");

	m_closed = false;

	while(IsRunning()) {
		// exit if connection was closed
		if(m_closed) {
			break;
		}

		// wait for string
		if(!ReceiveString(msg)) {
			continue;
		}

		std::cout << msg << std::endl;

		// check for http request
		if(msg.substr(0, 8) == "OPTIONS " && msg.size() > 8) {
			msg = msg.substr(8);
		}
		else if(msg.substr(0, 4) != "GET ") {
			continue;
		}

		std::string::size_type p = msg.rfind("HTTP/");

		if(p == std::string::npos) {
			continue;
		}

		msg = msg.substr(0, p);
		std::cout << "URI: " << msg << std::endl;

		// extract JSON query string
		p = msg.find("?");

		std::string url;
		std::string query;

		if(p > 0) {
			url = msg.substr(0, p);
		}

		if(p < msg.size() - 1) {
			query = URLDecode(msg.substr(p + 1));
		}

		std::cout << "URL: " << url << std::endl;
		std::cout << "QUERY: " << query << std::endl;

		// get message id
		while((url[0] > '9' || url[0] < '0') && url.size() > 1) {
			url = url.substr(1);
		}

		uint32_t msgid = atoi(url.c_str());
		MsgPacket* request = MsgPacketFromJSON(query, msgid);

		if(m_msgtype != 0) {
			request->setType(m_msgtype);
		}

		std::cout << "MSGID: " << request->getMsgID() << std::endl;
		std::cout << "MSGTYPE: " << request->getType() << std::endl;

		request->print();

		MsgPacket* response = new MsgPacket(request->getMsgID(), request->getType(), request->getUID());

		std::string jsonformat;
		std::string result;

		request->rewind();

		if(OnMessage(request, response)) {
			if(OnCustomJSONResponse(response, result)) {
				SendHTTPResponse(result);
			}
			else if(OnResponseFormat(response, jsonformat)) {
				result = MsgPacketToJSON(response, jsonformat);
				SendHTTPResponse(result);
			}
		}

		delete response;
		delete request;
	}
}