	void onReadable(Poco::Net::ReadableNotification* pNf)
	{
		pNf->release();

		try
		{
			char buffer[256] = { 0, };
			int n = m_socket.receiveBytes(buffer, sizeof(buffer));
			if (n > 0)
			{
				std::cout << "클라이언트에서 받은 메시지: " << buffer << std::endl;

				char szSendMessage[256] = { 0, };
				sprintf_s(szSendMessage, 256 - 1, "Re:%s", buffer);
				int nMsgLen = (int)strnlen_s(szSendMessage, 256 - 1);

				m_socket.sendBytes(szSendMessage, nMsgLen);
			}
			else
			{
				m_socket.shutdownSend();
				delete this;  // 메모리 해제하지 않으면 소멸자가 호출되지 않는다.
			}
		}
		catch (Poco::Exception& exc)
		{
			std::cerr << "EchoServer: " << exc.displayText() << std::endl;

			m_socket.shutdown();
			delete this;  
		}
	}