	virtual void run()
	{
		try
		{
			int recvSize = 0;

			do
			{
				char buffer[256] = { 0, };
				recvSize = socket().receiveBytes(buffer, sizeof(buffer));
				std::cout << "클라이언트에서 받은 메시지: " << buffer << std::endl;


				char szSendMessage[256] = { 0, };
				sprintf_s(szSendMessage, 128 - 1, "Re:%s", buffer);
				int nMsgLen = (int)strnlen_s(szSendMessage, 256 - 1);

				socket().sendBytes(szSendMessage, nMsgLen);				
			} while (recvSize > 0);

			std::cout << "클라이언트와 연결이 끊어졌습니다" << std::endl;
		}
		catch (Poco::Exception& exc)
		{
			std::cerr << "Session: " << exc.displayText() << std::endl;
		}
	}