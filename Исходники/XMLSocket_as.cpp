bool
XMLSocket_as::connect(const std::string& host, boost::uint16_t port)
{

    if (!URLAccessManager::allowXMLSocket(host, port)) {
	    return false;
    }

    _socket.connect(host, port);
    
    // Start callbacks on advance.
    getRoot(owner()).addAdvanceCallback(this);
    
    return true;
}