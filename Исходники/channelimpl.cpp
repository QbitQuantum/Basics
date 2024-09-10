CHANNEL channel(ENDPOINT ep, QUEUE que) {
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

	unsigned long ul = 1;
	if (ioctlsocket(s, FIONBIO, (unsigned long *)&ul) == SOCKET_ERROR){
	}

	channelimpl * ch = pool::objpool<channelimpl>::allocator(1);
	new (ch) channelimpl(que, s, ep);

	if (ch->que != 0){
		CreateIoCompletionPort((HANDLE)ch->s, ((queueimpl*)((handle*)ch->que))->iocp, 0, 0);

		WSABUF * wsabuf = pool::objpool<WSABUF>::allocator(1);
		wsabuf->buf = ch->buf;
		wsabuf->len = 0;
		DWORD bytes = 0;
		DWORD flags = 0;
		overlappedex * ovp = pool::objpool<overlappedex>::allocator(1);
		new (ovp)overlappedex();
		ovp->h = (handle*)ch;
		ovp->com_type = iocp_type_ipv4_udp;
		ovp->event_type = type_recv;
		OVERLAPPED * ovp_ = static_cast<OVERLAPPED *>(ovp);
		memset(ovp_, 0, sizeof(OVERLAPPED));
		if (WSARecvFrom(ch->s, wsabuf, 1, &bytes, &flags, (sockaddr*)(&((endpointimpl*)ch->from)->addr), &((endpointimpl*)ch->from)->len, ovp_, 0) == SOCKET_ERROR){
			if (WSAGetLastError() != WSA_IO_PENDING){
				return false;
			}
		}
	}

	return (CHANNEL)((handle*)ch);
}