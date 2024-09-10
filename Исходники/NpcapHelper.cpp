VOID GetAnswerToRequest( LPSTR pchRequest, 
						LPSTR pchReply, 
						LPDWORD pchBytes )
						// This routine is a simple function to print the client request to the console
						// and populate the reply buffer with a default data string. This is where you
						// would put the actual client request processing code that runs in the context
						// of an instance thread. Keep in mind the main thread will continue to wait for
						// and receive other client connections while the instance thread is working.
{
	printf("Client Request String:\"%s\"\n", pchRequest);

	DWORD dwError;
	HANDLE hFile = getDeviceHandleInternal(pchRequest, &dwError);
	printf("Driver Handle: 0x%08p\n", hFile);
	if (hFile)
	{
		char buf[BUFSIZE];
		sprintf_s(buf, BUFSIZE, "%p,%d", hFile, dwError);
		strcpy_s(pchReply, BUFSIZE, buf);
		*pchBytes = (DWORD) strlen(buf) * sizeof(char);
	}
	else
	{
		// Check the outgoing message to make sure it's not too long for the buffer.
		if (FAILED(StringCchCopyA( pchReply, BUFSIZE, "default answer from server")))
		{
			*pchBytes = 0;
			pchReply[0] = 0;
			printf("StringCchCopy failed, no outgoing message.\n");
			return;
		}
		*pchBytes = (DWORD) (strlen(pchReply) + 1) * sizeof(char);
	}
}