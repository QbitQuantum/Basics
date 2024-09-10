static DWORD WINAPI Connect (LPTHREAD_ARG pThArg)
{
	BOOL f;
	/*	Pipe connection thread that allows the server worker thread 
		to poll the ShutDown flag. */
	f = ConnectNamedPipe (pThArg->hNamedPipe, NULL);
	_tprintf (_T("ConnNP finished: %d\n"), f);
	_endthreadex (0);
	return 0; 
}