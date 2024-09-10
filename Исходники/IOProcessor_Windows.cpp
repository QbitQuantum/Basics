static bool RequestReadNotification(IOOperation* ioop)
{
	DWORD	numBytes, flags;
	WSABUF	wsabuf;
	IODesc*	iod;
	int		ret;

//	Log_Trace("fd.index = %d", ioop->fd.index);

	iod = GetIODesc(ioop->fd);

	assert(iod->read == NULL);

	wsabuf.buf = NULL;
	wsabuf.len = 0;

	flags = 0;
	memset(&iod->ovlRead, 0, sizeof(OVERLAPPED));

	if (ioop->type == UDP_READ)
		flags |= MSG_PEEK;	// without this, the O/S would discard each incoming UDP packet
							// as it doesn't fit into the user-supplied (0 length) buffer

	ret = WSARecv(ioop->fd.sock, &wsabuf, 1, &numBytes, &flags, &iod->ovlRead, NULL);
	if (ret == SOCKET_ERROR)
	{
		ret = WSAGetLastError();
		if (ret != WSA_IO_PENDING)
		{
			Log_Trace("%d", ret);
			return false;
		}
	}

	iod->read = ioop;
	ioop->active = true;

	return true;
}