void DatagramSocketTest::testSendToReceiveFrom()
{
	UDPEchoServer echoServer(SocketAddress("localhost", 0));
	DatagramSocket ss;
	int n = ss.sendTo("hello", 5, SocketAddress("localhost", echoServer.port()));
	assert (n == 5);
	char buffer[256];
	SocketAddress sa;
	n = ss.receiveFrom(buffer, sizeof(buffer), sa);
	assert (sa.host() == echoServer.address().host());
	assert (sa.port() == echoServer.port());
	assert (n == 5);
	assert (std::string(buffer, n) == "hello");
	ss.close();
}