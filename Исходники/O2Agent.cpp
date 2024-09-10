int
O2Agent::
connect2(SOCKET s, const struct sockaddr *name, int namelen, int timeout)
{
	bool err = false;

	WSAEVENT event = WSACreateEvent();
	if (event == WSA_INVALID_EVENT)
		err = true;

	if (!err && WSAEventSelect(s, event, FD_CONNECT) == SOCKET_ERROR)
		err = true;

	if (!err && connect(s, name, namelen) == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK)
			err = true;
		//非ブロッキングでconnectした場合、通常はSOCKET_ERRORになり
		//WSAGetLastError() == WSAEWOULDBLOCKが返ってくる。
		//それ以外のエラーは本当にconnect失敗
	}
	else
		err = true;

	if (!err && WSAWaitForMultipleEvents(1, &event, FALSE, timeout, FALSE) != WSA_WAIT_EVENT_0)
		err = true;

	WSANETWORKEVENTS events;
	if (!err && WSAEnumNetworkEvents(s, event, &events) == SOCKET_ERROR)
		err = true;
	if (!err && (!(events.lNetworkEvents & FD_CONNECT) || events.iErrorCode[FD_CONNECT_BIT] != 0))
		err = true;

	WSAEventSelect(s, NULL, 0);
	WSACloseEvent(event);

	/* back to blocking mode
	ulong argp = 0;
	ioctlsocket(s, FIONBIO, &argp);
	*/

	return (err ? SOCKET_ERROR : 0);
}