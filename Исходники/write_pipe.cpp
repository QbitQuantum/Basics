void WritePipe::setup_pipe()
{
	// Create a pipe to send data
	_pipe = CreateNamedPipeA(
		_pipe_name.c_str(), // name of the pipe
		PIPE_ACCESS_OUTBOUND, // 1-way pipe -- send only
		PIPE_TYPE_BYTE | PIPE_WAIT, // send data as a byte stream
		1, // only allow 1 instance of this pipe
		0, // no outbound buffer
		0, // no inbound buffer
		10, // use default wait time
		NULL // use default security attributes
		);
	if (_pipe == NULL || _pipe == INVALID_HANDLE_VALUE) 
	{
		traceerr("Failed to create outbound pipe instance.");
		return;
	}
	bool result = ConnectNamedPipe(_pipe, NULL);
	if (!result)
	{
		traceerr( "Failed to make connection on named pipe.");
		CloseHandle(_pipe); // close the pipe
		return;
	}
	running = true;
}