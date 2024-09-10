void SocketUdp::Send(const std::string& packet)
{
	SOCKADDR_IN sin;

	DEBUG << "Sending in progress" << std::endl;
	for (std::list<EndPoint*>::iterator it = this->client_.begin() ; it != this->client_.end() ; ++it) { 
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr((*it)->getIpStr().c_str());
		WSAHtons(this->socket_, (*it)->getPort(), &sin.sin_port);

		WSABUF* fb = new WSABUF();
		CHAR* buffer = new CHAR[sizeof(UDPPacket)];
		PackManUDP::Memcpy(buffer, packet.data(), packet.size());
		fb->buf = buffer;
		fb->len = sizeof(UDPPacket);

		DWORD sended = 0;

		if (WSASendTo(this->socket_, fb, 1, &sended, 0, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin), 0, 0) == SOCKET_ERROR)
			throw ErrorInOut("Cannot send data");
		DEBUG << "Sending completed" << std::endl;

		delete fb;
		delete buffer;
	}
}