Piper::Piper()
{
	// Get tibias main module for future use
	baseAddress = (DWORD) GetModuleHandle(0);
	// Define a pipe name
	pipeName = L"\\\\.\\pipe\\piperpipe";
	// Create the pipe
	hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, BUFFER_SIZE, BUFFER_SIZE, 5000, NULL);
	// If we didn't make it, tell the user something went wrong.
	if (hPipe == NULL || hPipe == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Error loading named pipe, please consult your software provider for support", L"Error!", MB_ICONSTOP);
	}
	// Wait for a client to connect to see the data down the pipe.
	ConnectNamedPipe(hPipe, NULL);
	// Send a message down the pipe to confirm it's working
	Send("SYSTEM OPERATIONAL");
	// Send the base address for good measure
	char *buff = new char[32];
	_itoa_s(baseAddress, buff, strlen(buff), 16);
	Send(buff);
	for (int i = 0; i < 10; i++)
	{
		Send("Testing");
		Sleep(1000);
	}
}