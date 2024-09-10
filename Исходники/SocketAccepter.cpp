SocketAccepter::SocketAccepter(SocketEventHandle *eventHandle):SocketHandle(eventHandle,NULL)
{
	DWORD bytes = 0;
	GUID acceptex_guid = WSAID_ACCEPTEX;

	if (WSAIoctl(socket_,SIO_GET_EXTENSION_FUNCTION_POINTER,
		&acceptex_guid,sizeof(acceptex_guid),
		&fnAcceptEx_,sizeof(fnAcceptEx_),
		&bytes,NULL,NULL) == SOCKET_ERROR)
	{
		ATLTRACE2("failed to load AcceptEx: %d\n", WSAGetLastError());
	}
}