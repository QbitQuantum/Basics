static void
Destroy(void)
{
	if (WSACleanup() == SOCKET_ERROR &&
	    WSAGetLastError() == WSAEINPROGRESS) {
#ifndef _WIN32_WCE
		WSACancelBlockingCall();
#endif
		WSACleanup();
	}
	AG_MutexDestroy(&agNetWin32Lock);
}