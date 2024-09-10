//----< this defines processing to frame messages >------------------
HttpMessage ClientHandler::readMessage(Socket& socket) {
	connectionClosed_ = false;
	HttpMessage msg;
	while (true) { // read message attributes
		std::string attribString = socket.recvString('\n');
		if (attribString.size() > 1) {
			HttpMessage::Attribute attrib = HttpMessage::parseAttribute(attribString);
			msg.addAttribute(attrib);
		}
		else break;
	}
	if (msg.attributes().size() == 0) { // If client is done, connection breaks
		connectionClosed_ = true;					// and recvString returns empty string
		return msg;
	}
	if (msg.attributes()[0].first == "POST") // read body if POST
	{
		if (msg.attributes()[0].second == "Message") msg = readBody(msg, socket); // case 0 - normal message
		else if (msg.attributes()[0].second == "File") { // case 1 - client sending file to server
			saveFileServer(msg, socket);
			msg = constructMessage(msg);
		}
		else if (msg.attributes()[0].second == "closePackage") msg = closePackage(msg); // case 7 - close a package
		else if (msg.attributes()[0].second == "returnFile") { // case 4 - server sends files to client
			saveFileClient(msg, socket);
			msg = constructMessage(msg);
		}
	}
	else if (msg.attributes()[0].first == "GET") { // read message if GET
		msg = readBody(msg, socket);
		if (msg.attributes()[0].second == "getFileList")  msg = getFileList(msg); // case 5 - request list of packages
		else if (msg.attributes()[0].second == "getFileNameList")  msg = getFileNameList(msg); // case 6 - request list of files in a packages
		else if (msg.attributes()[0].second == "File" || msg.attributes()[0].second == "FileWithDeps")
			msg = getFiles(msg, msg.attributes()[0].second);
	}
	else {
		msg.removeAttribute("content-length");
		std::string bodyString = "<msg>Error message</msg>";
		std::string sizeString = Converter<size_t>::toString(bodyString.size());
		msg.addAttribute(HttpMessage::Attribute("content-length", sizeString));
		msg.addBody(bodyString);
	}
	return msg;
}