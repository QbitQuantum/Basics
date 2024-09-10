// returns true only if pipes have been initialised successfully
bool initStdHandles()
{
	if (initialisedStdHandles)
		return true;

#if 0
	// Get I/O redirection arguments from command-line
	char*	stdoutFilename;
	char*	stderrFilename;
	char*	stdinFilename;
	BOOL	stdoutAppend;
	BOOL	stderrAppend;
	BOOL	stdinAppend;
	if (getRedirArgs(GetCommandLine(),
			&stdinFilename, &stdoutFilename, &stderrFilename, &stdinAppend, &stdoutAppend, &stderrAppend))
	{
	}
#endif

	TCHAR			name[100];
	HANDLE			hFileMapping = NULL;
	unsigned char*	pBuffer = NULL;

	_stprintf(name, TEXT("wcecompat.%08x.child_data"), GetCurrentProcessId());
	hFileMapping = CreateFileMapping((HANDLE)INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1, name);
	if (hFileMapping == NULL)
		goto cleanup;
	else if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hFileMapping);
		hFileMapping = NULL;

		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("wcecompat.starting_child"));
		if (hEvent == NULL)
		{	// failed to create named event
		}
		else if (GetLastError() == ERROR_ALREADY_EXISTS)
		{	// we're in DllMain, so do nothing
		}
		else
		{
			CloseHandle(hEvent);
		}
	}
	else
	{
		pBuffer = (unsigned char*)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);
		if (pBuffer == NULL)
		{	// failed to map buffer
		}
		else
		{
			g_childData = new ChildData;
			if (g_childData == NULL)
				goto cleanup;
			if (!g_childData->decode(pBuffer))//, 16384);
				goto cleanup;
			g_childData->restoreEnvironment();
			RedirArg* stdinRedir = g_childData->getRedirArg(0);
			RedirArg* stdoutRedir = g_childData->getRedirArg(1);
			RedirArg* stderrRedir = g_childData->getRedirArg(2);
			if (stdinRedir != NULL && stdinRedir->redirType != RT_NONE)
			{
				if (stdinRedir->redirType == RT_PIPE_UNSPEC)
				{
					_FD_STRUCT* fds = fds_from_index(STDIN);
					if (fds == NULL)
						goto cleanup;
					fds->pipe = createPipe(stdinRedir->filename, OPEN_EXISTING);
					if (fds->pipe == NULL)
					{	// failed to open stdin pipe
						goto cleanup;
					}
					fds->pipeChannel = (unsigned char)stdinRedir->fd2;
				}
				else if (stdinRedir->redirType == RT_HANDLE)
				{
				}
				else if (stdinRedir->redirType == RT_FILE)
				{
//					WCHAR*	mode = L"r";	// default to "r" for the cases we don't know how to handle
					bool	r = stdinRedir->openForRead;
					bool	w = stdinRedir->openForWrite;
					bool	a = stdinRedir->append;
/*
					// rwa	mode
					// 010	"w"
					// 011	"a"
					// 100	"r"
					// 110	"r+"
					// 111	"a+"
					if (a)
					{
						if (r)
							mode = L"a+";
						else
							mode = L"a";
					}
					else if (r)
					{
						if (w)
							mode = L"r+";
						else
							mode = L"r";
					}
					else if (w)
						mode = L"w";
					FILE*	f = _wfopen(stdinRedir->filename, mode);
					if (f == NULL)
						goto cleanup;
					memcpy(&mystdin, f, sizeof(_FD_STRUCT));
					free(f);
*/
					// rwa	mode
					// 010	"w"		w,   CREATE_ALWAYS					O_WRONLY				O_CREAT|O_TRUNC
					// 011	"a"		w,   OPEN_ALWAYS   (APPEND DATA)	O_WRONLY	O_APPEND	O_CREAT
					// 100	"r"		r,   OPEN_EXISTING					O_RDONLY				
					// 110	"r+"	r/w, OPEN_EXISTING					O_RDWR					
					// 111	"a+"	r/w, OPEN_ALWAYS   (APPEND DATA)	O_RDWR		O_APPEND	O_CREAT
					int	flags = 0;
					int	mode = 0;
					if (r && w)
						flags |= O_RDWR;
					else if (r)
						flags |= O_RDONLY;
					else if (w)
						flags |= O_WRONLY;
					if (w)
					{
						if (!(r && !a))
						{
							flags |= O_CREAT;
							mode = S_IREAD | S_IWRITE;
						}
						if (!r && !a)
							flags |= O_TRUNC;
					}
					if (a)
						flags |= O_APPEND;
					_FD_STRUCT* fds = fds_from_index(STDIN);
					if (fds == NULL)
						goto cleanup;
					if (!_wopen_fds(stdinRedir->filename, flags, mode, fds))
						goto cleanup;
				}
			}
			if (stdoutRedir != NULL && stdoutRedir->redirType != RT_NONE)
			{
				if (stdoutRedir->redirType == RT_PIPE_UNSPEC)
				{
					_FD_STRUCT* fds = fds_from_index(STDOUT);
					if (fds == NULL)
						goto cleanup;
					fds->pipe = createPipe(stdoutRedir->filename, OPEN_EXISTING);
					if (fds->pipe == NULL)
					{	// failed to open stdout pipe
						goto cleanup;
					}
					fds->pipeChannel = (unsigned char)stdoutRedir->fd2;
				}
				else if (stdoutRedir->redirType == RT_HANDLE)
				{
				}
				else if (stdoutRedir->redirType == RT_FILE)
				{
//					WCHAR*	mode = L"r";	// default to "r" for the cases we don't know how to handle
					bool	r = stdoutRedir->openForRead;
					bool	w = stdoutRedir->openForWrite;
					bool	a = stdoutRedir->append;
/*
					// rwa	mode
					// 010	"w"
					// 011	"a"
					// 100	"r"
					// 110	"r+"
					// 111	"a+"
					if (a)
					{
						if (r)
							mode = L"a+";
						else
							mode = L"a";
					}
					else if (r)
					{
						if (w)
							mode = L"r+";
						else
							mode = L"r";
					}
					else if (w)
						mode = L"w";
					FILE*	f = _wfopen(stdoutRedir->filename, mode);
					if (f == NULL)
						goto cleanup;
					memcpy(&mystdout, f, sizeof(_FD_STRUCT));
					free(f);
*/
					// rwa	mode
					// 010	"w"		w,   CREATE_ALWAYS					O_WRONLY				O_CREAT|O_TRUNC
					// 011	"a"		w,   OPEN_ALWAYS   (APPEND DATA)	O_WRONLY	O_APPEND	O_CREAT
					// 100	"r"		r,   OPEN_EXISTING					O_RDONLY				
					// 110	"r+"	r/w, OPEN_EXISTING					O_RDWR					
					// 111	"a+"	r/w, OPEN_ALWAYS   (APPEND DATA)	O_RDWR		O_APPEND	O_CREAT
					int	flags = 0;
					int	mode = 0;
					if (r && w)
						flags |= O_RDWR;
					else if (r)
						flags |= O_RDONLY;
					else if (w)
						flags |= O_WRONLY;
					if (w)
					{
						if (!(r && !a))
						{
							flags |= O_CREAT;
							mode = S_IREAD | S_IWRITE;
						}
						if (!r && !a)
							flags |= O_TRUNC;
					}
					if (a)
						flags |= O_APPEND;
					_FD_STRUCT* fds = fds_from_index(STDOUT);
					if (fds == NULL)
						goto cleanup;
					if (!_wopen_fds(stdoutRedir->filename, flags, mode, fds))
						goto cleanup;
				}
			}
			if (stderrRedir != NULL && stderrRedir->redirType != RT_NONE)
			{
				if (stderrRedir->redirType == RT_PIPE_UNSPEC)
				{
					_FD_STRUCT* fds = fds_from_index(STDERR);
					if (fds == NULL)
						goto cleanup;
					if (stdoutRedir != NULL && stdoutRedir->redirType == RT_PIPE_UNSPEC &&
							wcscmp(stderrRedir->filename, stdoutRedir->filename) == 0)
					{
						_FD_STRUCT* fds_stdout = fds_from_index(STDOUT);
						if (fds_stdout == NULL)
							goto cleanup;
						fds->pipe = fds_stdout->pipe;
					}
					else
					{
						fds->pipe = createPipe(stderrRedir->filename, OPEN_EXISTING);
						if (fds->pipe == NULL)
						{	// failed to open stderr pipe
							goto cleanup;
						}
					}
					fds->pipeChannel = (unsigned char)stderrRedir->fd2;
				}
				else if (stderrRedir->redirType == RT_HANDLE)
				{
				}
				else if (stderrRedir->redirType == RT_FILE)
				{
//					WCHAR*	mode = L"r";	// default to "r" for the cases we don't know how to handle
					bool	r = stderrRedir->openForRead;
					bool	w = stderrRedir->openForWrite;
					bool	a = stderrRedir->append;
/*
					// rwa	mode
					// 010	"w"
					// 011	"a"
					// 100	"r"
					// 110	"r+"
					// 111	"a+"
					if (a)
					{
						if (r)
							mode = L"a+";
						else
							mode = L"a";
					}
					else if (r)
					{
						if (w)
							mode = L"r+";
						else
							mode = L"r";
					}
					else if (w)
						mode = L"w";
					FILE*	f = _wfopen(stderrRedir->filename, mode);
					if (f == NULL)
						goto cleanup;
					memcpy(&mystderr, f, sizeof(_FD_STRUCT));
					free(f);
*/
					// rwa	mode
					// 010	"w"		w,   CREATE_ALWAYS					O_WRONLY				O_CREAT|O_TRUNC
					// 011	"a"		w,   OPEN_ALWAYS   (APPEND DATA)	O_WRONLY	O_APPEND	O_CREAT
					// 100	"r"		r,   OPEN_EXISTING					O_RDONLY				
					// 110	"r+"	r/w, OPEN_EXISTING					O_RDWR					
					// 111	"a+"	r/w, OPEN_ALWAYS   (APPEND DATA)	O_RDWR		O_APPEND	O_CREAT
					int	flags = 0;
					int	mode = 0;
					if (r && w)
						flags |= O_RDWR;
					else if (r)
						flags |= O_RDONLY;
					else if (w)
						flags |= O_WRONLY;
					if (w)
					{
						if (!(r && !a))
						{
							flags |= O_CREAT;
							mode = S_IREAD | S_IWRITE;
						}
						if (!r && !a)
							flags |= O_TRUNC;
					}
					if (a)
						flags |= O_APPEND;
					_FD_STRUCT* fds = fds_from_index(STDERR);
					if (fds == NULL)
						goto cleanup;
					if (!_wopen_fds(stderrRedir->filename, flags, mode, fds))
						goto cleanup;
				}
			}
		}
	}

	initialisedStdHandles = true;
	atexit(shutdownIo);

cleanup:

	if (!initialisedStdHandles)
		uninitStdHandles();

	if (pBuffer != NULL)
		UnmapViewOfFile(pBuffer);
	if (hFileMapping != NULL)
		CloseHandle(hFileMapping);

	return initialisedStdHandles;
}