void connectSocket(boost::asio::io_service& io_service, tcp::socket& socket, const std::string& url, const std::string &port) {
	boost::system::error_code error = boost::asio::error::host_not_found;

	// connect
	if (isIpAddress(url.c_str())) {
		boost::asio::ip::address addr = boost::asio::ip::address::from_string(url);
		boost::asio::ip::tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(addr, lexical_cast<int>(port));
		socket.close();
		socket.connect(endpoint);
	}
	else {
		tcp::resolver::query query(url, "http");
		tcp::resolver resolver(io_service);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		while (error && endpoint_iterator != end)
		{
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
			throw boost::system::system_error(error);
	}
}