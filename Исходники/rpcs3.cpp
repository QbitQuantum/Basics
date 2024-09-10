Rpcs3App::Rpcs3App()
{
#ifdef _WIN32
	timeBeginPeriod(1);

	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	std::atexit([]
	{
		timeEndPeriod(1);
		WSACleanup();
	});
#endif

#if defined(__unix__) && !defined(__APPLE__)
	XInitThreads();
#endif
}