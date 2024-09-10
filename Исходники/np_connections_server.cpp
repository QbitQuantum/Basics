static PIPE_HANDLE createNamedPipe(const char* pipeName, SECURITY_ATTRIBUTES sa)
{
	return CreateNamedPipeA(	pipeName,
	                        PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
	                        PIPE_TYPE_BYTE | PIPE_WAIT | PIPE_READMODE_BYTE,
	                        PIPE_UNLIMITED_INSTANCES,
	                        8192, 8192, 0,
	                        &sa);
}