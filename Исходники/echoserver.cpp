void EchoServer::onClose(const TcpConnectionPtr &conn)
{
	cout << "client : " << conn->getPeerAddr().toIp() << " : "
		 << conn->getPeerAddr().toPort() << " close" << endl;
	conn->shutdown();
	
}