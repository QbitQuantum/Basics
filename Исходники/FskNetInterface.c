DWORD WINAPI networkInterfaceChangeThreadFunc( LPVOID lpParam )
{
	static OVERLAPPED overlap;
	DWORD ret;

	HANDLE hand = NULL;
	HANDLE watch[2];
	overlap.hEvent = WSACreateEvent();

	while (1) {
		ret = NotifyAddrChange(&hand, &overlap);

		if (ret != NO_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				printf("NotifyAddrChange error...%d\n", WSAGetLastError());
				break;
			}
		}
		watch[0] = overlap.hEvent;
		watch[1] = networkInterfaceChangeQuitEvent;

		ret = WaitForMultipleObjects(2, watch, FALSE, INFINITE);
		if (ret == WAIT_OBJECT_0) {
			PostMessage(networkInterfaceTrackerWindow, gNetworkInterfaceChangedMessage, 0, 0);
//			printf("IP Address table changed..\n");
			Sleep(100);
		}
		else
			break;
	}
	CloseHandle(overlap.hEvent);
	CloseHandle(networkInterfaceChangeQuitEvent);
	DestroyWindow(networkInterfaceTrackerWindow);
	networkInterfaceChangeQuitEvent = NULL;
	networkInterfaceTrackerWindow = NULL;
	networkInterfaceChangeThread = NULL;

	return 0;
}