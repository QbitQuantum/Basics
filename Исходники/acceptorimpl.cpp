acceptorimlp::acceptorimlp(QUEUE _que, ENDPOINT ep){
	_handle_type = handle_ipv4_tcp_acceptor_type;
	que = _que;

	sl = socket(AF_INET, SOCK_STREAM, 0);
	sa = socket(AF_INET, SOCK_STREAM, 0);

	outbuf = new char[1024];

	if (bind(sl, (sockaddr*)(&((endpointimpl*)((handle*)ep))->addr), sizeof(SOCKADDR_IN)) != 0){
		throw std::exception("bind error");
	}

	if (listen(sl, 10) != 0){
		throw std::exception("listen error");
	}

	int corenum = 8;
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	corenum = info.dwNumberOfProcessors;

	if (CreateIoCompletionPort((HANDLE)sl, ((queueimpl*)((handle*)_que))->iocp, 0, corenum) != ((queueimpl*)((handle*)_que))->iocp){
		throw std::exception("CreateIoCompletionPort error", WSAGetLastError());
	}

	memset(outbuf, 0, sizeof(outbuf));

	overlappedex * ovlp = pool::objpool<overlappedex>::allocator(1);
	new (ovlp) overlappedex();
	ovlp->h = (handle*)this;
	ovlp->com_type = iocp_type_ipv4_tcp;
	ovlp->event_type = type_accept;
	OVERLAPPED * ovp = static_cast<OVERLAPPED *>(ovlp);
	memset(ovp, 0, sizeof(OVERLAPPED));
	if (!AcceptEx(sl, sa, outbuf, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, 0, ovp)){
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING){
			throw std::exception("acceptorimlp", error);
		}
	}
}