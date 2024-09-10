VOID InstanceThread (LPVOID lpvParam)
{
   CHAR chRequest[BUFSIZE];
   CHAR chReply[BUFSIZE];
   DWORD cbBytesRead, cbReplyBytes, cbWritten;
   BOOL fSuccess;
   HANDLE hPipe;

   hPipe = (HANDLE)lpvParam;
   while (1)
     {
	fSuccess = ReadFile(hPipe,
			    chRequest,
			    BUFSIZE,
			    &cbBytesRead,
			    NULL);
	if (!fSuccess || cbBytesRead == 0)
	  break;

	GetAnswerToRequest(chRequest, chReply, &cbReplyBytes);

	fSuccess = WriteFile(hPipe,
			     chReply,
			     cbReplyBytes,
			     &cbWritten,
			     NULL);
	if (!fSuccess || cbReplyBytes != cbWritten)
	  break;
    }

   FlushFileBuffers(hPipe);
   DisconnectNamedPipe(hPipe);
   CloseHandle(hPipe);
}