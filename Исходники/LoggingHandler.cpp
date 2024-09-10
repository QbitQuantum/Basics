void LoggingHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	bool reauth = true;
	if (request.hasCredentials())
	{
		std::string cred;
		std::string scheme;
		try
		{
			Poco::Net::HTTPBasicCredentials cred(request);
			std::string user = cred.getUsername();
			std::istringstream istr(cred.getPassword(), std::ios::binary);
			Poco::MD5Engine md5;
			Poco::DigestOutputStream dos(md5);
			Poco::StreamCopier::copyStream(istr, dos);
			dos.close();
			std::string pwd = Poco::DigestEngine::digestToHex(md5.digest());
			reauth = (pwd != _pwdHash || _user != user);
		}
		catch (...)
		{
			reauth = true;
		}
	}
	if (reauth)
	{
		response.requireAuthentication(TITLE);
		response.send();
		return;
	}
	Poco::Net::HTMLForm form(request);
	std::string offsetStr;
	Poco::Net::NameValueCollection::ConstIterator it = form.find(OFFSET);
	if (it != form.end())
		offsetStr = it->second;
	int offset(0);
	Poco::NumberParser::tryParse(offsetStr, offset);
	std::string numEntriesStr;
	it = form.find(NUMENTRIES);
	if (it != form.end())
		numEntriesStr = it->second;
	int numEntries = DEFAULT_NUMENTRIES;
	Poco::NumberParser::tryParse(numEntriesStr, numEntries);
	std::vector<Poco::Message> messages;
	_channel.getMessages(messages, offset, numEntries);
	displayMessages(messages, offset, numEntries, _channel.getCurrentSize(), response);
}