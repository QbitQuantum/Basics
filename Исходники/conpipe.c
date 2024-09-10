FILE *openpipe(char *command, unsigned short redirect_stderr)
{
	SECURITY_ATTRIBUTES		sa		= {0};
	STARTUPINFO				si		= {0};
	PROCESS_INFORMATION		pi		= {0};
	BOOL					bTest= 0;
	DWORD					dwNumberOfBytesRead = 0;

	FILE					*stream;
	int						CrtFileHandle;

	hPipeOutputRead = hPipeOutputWrite = hPipeInputRead = hPipeInputWrite = NULL;

	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	if(!CreatePipe(&hPipeOutputRead,&hPipeOutputWrite,&sa,0))
		{
		mexPrintf("Can't open stdout pipe\n");
		return(NULL);
		}

	if(!CreatePipe(&hPipeInputRead,&hPipeInputWrite,&sa,0))
		{
		mexPrintf("Can't open stdin pipe\n");
		return(NULL);
		}

	si.cb = sizeof(si);
	si.dwFlags		= STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow	= SW_HIDE;
	si.hStdInput	= hPipeInputRead;
	si.hStdOutput	= hPipeOutputWrite;
	if(redirect_stderr)
		si.hStdError	= hPipeOutputWrite;

	if(CreateProcess(NULL, command, NULL, NULL, TRUE, HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi) == 0)
		{
		mexPrintf("Could not execute subprocess\n");
		return(NULL);
		}

	CloseHandle(hPipeOutputWrite);
	CloseHandle(hPipeInputRead);

	/*  Convert OS file handle to CRT file pointer  */
	if((CrtFileHandle = _open_osfhandle((long)hPipeOutputRead, _O_RDONLY|_O_BINARY)) == -1)
		{
		mexPrintf("Could not translate windows handle to crt handle\n");
		return(NULL);
		}

	/*  Change handle access to stream access.  */
	if((stream = _fdopen(CrtFileHandle, "r+b")) == NULL)
		{
		mexPrintf("Could not open FILE * for pipe\n");
		return(NULL);
		}

	subprocess = pi.hProcess;

	return(stream);

}