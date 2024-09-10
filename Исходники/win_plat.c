void platform_cleanup(void)
{
	// Unregister a change notification if we have one
	if (notification_handle != INVALID_HANDLE_VALUE)
	{
		CancelMibChangeNotify2(notification_handle);
	}

	// Cleanup WinSock
	WSACleanup();
}