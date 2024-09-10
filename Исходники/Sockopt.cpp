int is_socket_closed(int sock)
{
	int nRet;
	HANDLE hCloseEvent = WSACreateEvent();
	WSAEventSelect(sock, hCloseEvent, FD_CLOSE);

	DWORD dwRet = WaitForSingleObject(hCloseEvent, 1);

	if(dwRet == WSA_WAIT_EVENT_0)
		nRet = 1;
	else if(dwRet == WSA_WAIT_TIMEOUT)
		nRet = 0;

	WSACloseEvent(hCloseEvent);
	return nRet;
}