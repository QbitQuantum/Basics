static inline bool ipc_pipe_internal_create_pipe(ipc_pipe_server_t *pipe,
		const char *name)
{
	char new_name[512];
	const DWORD access = PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED;
	const DWORD flags = PIPE_TYPE_MESSAGE     |
	                    PIPE_READMODE_MESSAGE |
	                    PIPE_WAIT;

	strcpy_s(new_name, sizeof(new_name), "\\\\.\\pipe\\");
	strcat_s(new_name, sizeof(new_name), name);

	pipe->handle = CreateNamedPipeA(new_name, access, flags, 1,
			IPC_PIPE_BUF_SIZE, IPC_PIPE_BUF_SIZE, 0, NULL);

	return pipe->handle != INVALID_HANDLE_VALUE;
}