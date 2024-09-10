void MulticastSocketTest::testMulticast()
{
	MulticastEchoServer echoServer;
	MulticastSocket ms;
	int n = ms.sendTo("hello", 5, echoServer.group());
	assert (n == 5);
	char buffer[256];
	n = ms.receiveBytes(buffer, sizeof(buffer));
	assert (n == 5);
	assert (std::string(buffer, n) == "hello");
	ms.close();
}