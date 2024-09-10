static HANDLE_OR_FILEPTR
open_windows_pipe(const char *filename)
{
#ifdef WIN32
	HANDLE pipe;
	int result;

	pipe = CreateNamedPipe(filename,
		PIPE_ACCESS_OUTBOUND,          // write-only
		PIPE_TYPE_MESSAGE | PIPE_WAIT, // blocking writes
		1,                             // only allow one pipe
		70000,          // write buffer. GTH max is 64k
		10000,          // read buffer. We don't read
		0,              // default timeout
		0);             // no security attributes

	if (pipe == INVALID_HANDLE_VALUE) {
		die("Unable to create a named pipe. Giving up.");
	}

	result = ConnectNamedPipe(pipe, 0);
	if (!result) {
		die("Unabled to connect the named pipe. Giving up.");
	}

	return pipe;
#else
	die("Cannot open a windows named pipe on a non-windows OS. Giving up.");
	return 0;
#endif
}