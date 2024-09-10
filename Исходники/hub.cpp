	void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime)
	{
		ParseResult result = kSuccess;
		while (result == kSuccess) //while循环，当result一直为kSuccess
		{
			string cmd;
			string topic;
			string content;

			result = parseMessage(buf, &cmd, &topic, &content);
			if (result == kSuccess)
			{
				if (cmd == "pub")
				{
					doPublish(conn->name(), topic, content, receiveTime);
				}
				else if (cmd == "sub")
				{
					LOG_INFO << conn->name() << " subscribes " << topic;
					doSubscribe(conn, topic);


				}
				else if (cmd == "unsub")
				{
					doUnsubscribe(conn, topic);

				}
				else
				{
					conn->shutdown();
					result = kError;
				}
			}
			else if (result == kError)
			{
				conn->shutdown();
			}
		}
	}