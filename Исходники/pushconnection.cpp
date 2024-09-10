void PushConnection::onError(const boost::system::error_code &ec, Connection::ErrorSource errorSource) {
	std::cout << "PushConnection::onError: " << ec.value() << " " << ec.message() << " source: " << errorSource << std::endl;
	
	//close socket
	close();
}