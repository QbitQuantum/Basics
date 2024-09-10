shared_ptr<InterprocessIo> InterprocessServer::Connect()
{
	shared_handle hPipe(CreateNamedPipe(
		GetPipeName(),
		PIPE_ACCESS_DUPLEX |       // read/write access
		FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_MESSAGE |       // message type pipe
		PIPE_READMODE_MESSAGE |   // message-read mode
		PIPE_WAIT,                // non-blocking mode
		PIPE_UNLIMITED_INSTANCES, // max. instances
		BUF_SIZE,                  // output buffer size
		BUF_SIZE,                  // input buffer size
		NMPWAIT_USE_DEFAULT_WAIT, // client time-out
		NULL)					  // NULL DACL
	);
	if(!hPipe) {
		return shared_ptr<InterprocessIo>();
	}

	if(!ConnectNamedPipe(hPipe.get(), NULL) && (GetLastError()!=ERROR_PIPE_CONNECTED)) {
		return shared_ptr<InterprocessIo>();
	}

	return shared_ptr<InterprocessIo>(new InterprocessIo(hPipe));
}