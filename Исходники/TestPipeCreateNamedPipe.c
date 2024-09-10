int TestPipeCreateNamedPipe(int argc, char* argv[])
{
	HANDLE SingleThread;
	HANDLE ClientThread;
	HANDLE ServerThread;
	HANDLE hPipe;

	/* Verify that CreateNamedPipe returns INVALID_HANDLE_VALUE on failure */
	hPipe = CreateNamedPipeA(NULL, 0, 0, 0, 0, 0, 0, NULL);
	if (hPipe != INVALID_HANDLE_VALUE)
	{
		printf("CreateNamedPipe unexpectedly returned %p instead of INVALID_HANDLE_VALUE (%p)\n",
			hPipe, INVALID_HANDLE_VALUE);
		return -1;
	}

#ifndef _WIN32
	signal(SIGPIPE, SIG_IGN);
#endif
	if (!(ReadyEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		printf("CreateEvent failure: (%"PRIu32")\n", GetLastError());
		return -1;
	}
	if (!(SingleThread = CreateThread(NULL, 0, named_pipe_single_thread, NULL, 0, NULL)))
	{
		printf("CreateThread (SingleThread) failure: (%"PRIu32")\n", GetLastError());
		return -1;
	}
	if (!(ClientThread = CreateThread(NULL, 0, named_pipe_client_thread, NULL, 0, NULL)))
	{
		printf("CreateThread (ClientThread) failure: (%"PRIu32")\n", GetLastError());
		return -1;
	}
	if (!(ServerThread = CreateThread(NULL, 0, named_pipe_server_thread, NULL, 0, NULL)))
	{
		printf("CreateThread (ServerThread) failure: (%"PRIu32")\n", GetLastError());
		return -1;
	}
	WaitForSingleObject(SingleThread, INFINITE);
	WaitForSingleObject(ClientThread, INFINITE);
	WaitForSingleObject(ServerThread, INFINITE);
	CloseHandle(SingleThread);
	CloseHandle(ClientThread);
	CloseHandle(ServerThread);
	return testFailed;
}