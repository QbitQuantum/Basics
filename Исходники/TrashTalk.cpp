	void RunClient(const char *address, unsigned short port, SocketTransportLayer transport, int numMessages, int messageSize)
	{
		srand((unsigned int)time(NULL));

		cout << "Connecting to server. ";

		// Note: Here we don't build a proper MessageConnection, instead just work on a low-level abstraction layer
		// to be able to send raw data.

		Socket *socket = network.ConnectSocket(address, port, transport);
		if (!socket)
		{
			cout << "Failed to connect!" << endl;
			return;
		}

		for(int i = 0; i < numMessages; ++i)
		{
			std::vector<char> data;
			while((int)data.size() < messageSize)
				data.push_back(rand() & 0xFF);

			socket->Send(data.size() > 0 ? &data[0] : 0, data.size());

			Clock::Sleep((rand() % 100) + 1);
		}
		socket->Disconnect();
		socket->Close();
		network.DeleteSocket(socket);

		cout << "Finished sending data." << endl;
	}