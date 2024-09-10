int CreateInitSockClient(HWND hwnd, SOCKET& sock, sockaddr_in sa, char *buf)
{
	int i;
	char lineErr[256], buf2[128];
	CHECKERR(sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP), FL_ERR_SOCKET);
	CHECKERR(i = WSAAsyncSelect (sock, hwnd, WM_FLY_TASKS, FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE ), FL_ERR_WSAAYNC);
	i=connect (sock, (SOCKADDR *)&sa, sizeof(sa));
	if (i==-1)
	{
		if (WSAGetLastError()!=WSAEWOULDBLOCK)
		{
			sprintf(buf, "code=%d", i);
			MessageBox (NULL, buf, "Error in connect", MB_OK);
		}
	}
	_beginthreadex (NULL, 0, ConnectingThread, (void*)sock, 0, &connectThreadID);
	return i;
}