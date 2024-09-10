void onConnection(const TcpConnectionPtr& conn)
{
	if (conn->connected())
	{
		printf("onConnection(): tid=%d new connection [%s] from %s\n",
			CurrentThread::tid(),
			conn->name().c_str(),
			conn->peerAddress().toIpPort().c_str());


		conn->send(message); //一连接就发送
	}
	else
	{
		printf("onConnection(): tid=%d connection [%s] is down\n",
			CurrentThread::tid(),
			conn->name().c_str());
	}
}