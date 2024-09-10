// pipe name: \\.\pipe\pipename
async_pipe_t async_pipe_server(const char* name)
{
	DWORD dwWait;
	Win32Pipe* o;

	o = (Win32Pipe*)GlobalAlloc(GPTR, sizeof(Win32Pipe));
	if(!o)
		return NULL;

	o->pipe = CreateNamedPipeA(name, PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE|PIPE_READMODE_BYTE|PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 4096, 4096, 0, NULL);
	if(INVALID_HANDLE_VALUE != o->pipe)
	{
		o->overlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if(NULL != o->overlap.hEvent)
		{
			// MSDN: Overlapped ConnectNamedPipe should return zero. 
			if(0==ConnectNamedPipe(o->pipe, &o->overlap))
			{
				switch(GetLastError())
				{
				case ERROR_PIPE_CONNECTED:
					return o;

				case ERROR_IO_PENDING:
					do
					{
						dwWait = WaitForSingleObjectEx(o->overlap.hEvent, INFINITE, TRUE);
						if(WAIT_OBJECT_0 == dwWait)
						{
							if(GetOverlappedResult(o->pipe, &o->overlap, &dwWait, FALSE))
								return o;
						}
					} while(dwWait==WAIT_IO_COMPLETION);
					break;
				}
			}
			
			CloseHandle(o->overlap.hEvent);
		}
		CloseHandle(o->pipe);
	}

	GlobalFree(o);
	return NULL;
}