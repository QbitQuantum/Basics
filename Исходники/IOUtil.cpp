void IOUtil::createSocketPair(int pair[2]) throw (IOException&)
{
#if defined(WIN32)
	Socket connectSocket;
	Socket serverClientSocket;
	ServerSocket listenSocket;

	SocketAddress loopback = SocketAddress::loopback(AF_INET, 0);
	listenSocket.listen(loopback, 5, false);
	connectSocket.connect(listenSocket.getLocalAddress(), true);

	if (!listenSocket.accept(serverClientSocket))
	{
		THROW2(IOException, "Can't accept for socket pair");
	}

	pair[0] = connectSocket.detach();
	pair[1] = serverClientSocket.detach();
#else
	if (0 != ::socketpair(AF_LOCAL, SOCK_STREAM, 0, pair))
	{
		THROW2(IOException, "Can't create socket pair");
	}
#endif
}