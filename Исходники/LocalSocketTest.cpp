void LocalSocketTest::doSelectOrPoll1(SelectPtr pAction)
{
	Timespan timeout(250000);

	SocketAddress sas("/tmp/poco.server.tcp.sock");
	EchoServer echoServer(sas);
	SocketAddress sac("/tmp/poco.client.tcp.sock");
	StreamSocket ss(sas, &sac);

	Socket::SocketList readList;
	Socket::SocketList writeList;
	Socket::SocketList exceptList;

	readList.push_back(ss);
	assert (pAction(readList, writeList, exceptList, timeout) == 0);
	assert (readList.empty());
	assert (writeList.empty());
	assert (exceptList.empty());
	
	ss.sendBytes("hello", 5);

	ss.poll(timeout, Socket::SELECT_READ);

	readList.push_back(ss);
	writeList.push_back(ss);
	assert (pAction(readList, writeList, exceptList, timeout) == 2);
	assert (!readList.empty());
	assert (!writeList.empty());
	assert (exceptList.empty());

	char buffer[256];
	int n = ss.receiveBytes(buffer, sizeof(buffer));
	assert (n == 5);
	assert (std::string(buffer, n) == "hello");
	ss.close();
}