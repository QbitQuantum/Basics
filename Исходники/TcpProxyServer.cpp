bool TcpProxyServer::GetRemoteAddressAndPort(boost::asio::ip::tcp::socket& clientSocket, boost::asio::ip::address& remoteAddress, unsigned short& remotePort)
{
	boost::asio::ip::tcp::socket::endpoint_type userAgentEnpoint = clientSocket.remote_endpoint();
    unsigned short userAgentPort = userAgentEnpoint.port();
	boost::asio::ip::address userAgentIP = userAgentEnpoint.address();
	if(userAgentIP != boost::asio::ip::address_v4::from_string("127.0.0.1")) {
		return false;
	}

	std::pair<u_long, USHORT> remoteAddressPair = WinsockHooker::GetRemoteAddressPair(userAgentPort);
	
	if(remoteAddressPair.first == 0ul) {
		return false;
	}

	boost::asio::ip::address_v4 remote_address(remoteAddressPair.first);
	unsigned short remote_port = remoteAddressPair.second;
	if(remote_address == boost::asio::ip::address_v4::from_string("127.0.0.1") && remote_port == listen_port)
	{
		return false;
	}
	remoteAddress = remote_address;
	remotePort = remote_port;

	TSINFO4CXX("Connect: IP:" << remoteAddress.to_string() << ", Port: " << remotePort);
	return true;
}