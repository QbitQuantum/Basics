void PubSubClient::onMessage(const TcpConnectionPtr& conn,
	Buffer* buf,
	Timestamp receiveTime)
{
	ParseResult result = kSuccess;
	while (result == kSuccess)
	{
		string cmd;
		string topic;
		string content;
		result = parseMessage(buf, &cmd, &topic, &content);
		if (result == kSuccess)
		{
			if (cmd == "pub" && subscribeCallback_)
			{
				subscribeCallback_(topic, content, receiveTime);
			}
		}
		else if (result == kError)
		{
			conn->shutdown();
		}
	}
}