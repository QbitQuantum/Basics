void SIOClientImpl::disconnectFromEndpoint(const std::string& endpoint)
{
	_clients.erase(endpoint);

	if (_clients.empty() || endpoint == "/")
    {
		log("SIOClientImpl::disconnectFromEndpoint out of endpoints, checking for disconnect");
		
		if(_connected)
            this->disconnect();
	}
    else
    {
		std::string path = endpoint == "/" ? "" : endpoint;

		std::string s = "0::" + path;

		_ws->send(s);
	}
}