UDPPacket *UDPSocket::poll()
{
	if (WSAWaitForMultipleEvents(1, &event, false, 0, true) == WSA_WAIT_EVENT_0)
	{
		int len, FromLen = sizeof(INADDR);
		INADDR src;

		len = recvfrom(sid, packet.msg, PACKET_MAX_LENGTH, 0, src.getAddress(), &FromLen);

		if (len <= 0)
			return NULL;

		packet.src = src;
		packet.len = len;

		return &packet;
	}

	return NULL;
}