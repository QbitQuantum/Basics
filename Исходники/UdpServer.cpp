UINT __stdcall UdpServerForIpWorker(PVOID context)
{
	UdpServer server;
	if (server.Init("127.0.0.1", (int)context)) {
		std::vector<UCHAR> buffer;
		buffer.resize(0x1000);
		for (;;) {
			sockaddr_in addr;
			int recv_length = server.Recv((char *)buffer.data(), buffer.size(), &addr);
			if (recv_length == -1) {
				break;
			}

			server.Send("OK", 3, &addr);
		}
	}

	return 0;
}