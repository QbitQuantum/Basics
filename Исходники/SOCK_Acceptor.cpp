SOCK_Acceptor::SOCK_Acceptor(INET_Addr& addr)
{
	// Create a local endpoint ofcommunication.
	handle_ = socket(AF_INET, SOCK_STREAM, 0);
	// Associate address with endpoint.
	bind(handle_, addr.addr(), addr.size());
	// Make endpoint listen for connections.
	listen(handle_, 5);
}