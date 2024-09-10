bool EtfArduinoService::SendMessage(LPVOID lpvMessage, DWORD bufferSize) {
	if (hPipe == 0)
		if (!OpenPipeConnection())
			return false;
	DWORD cbToWrite = bufferSize * sizeof(message_t);
	DWORD cbWritten = 0;
	BOOL fSuccess = WriteFile( 
		hPipe,               // pipe handle 
		lpvMessage,             // message 
		cbToWrite,              // message length 
		&cbWritten,             // bytes written 
		NULL);                  // not overlapped 
	// Make sure the message got through the pipe before returning.
	FlushFileBuffers(hPipe);
	if (!fSuccess) {
		_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError()); 
		return false;
	}
	if (cbWritten != cbToWrite) {
		return false;
	}
	return true;
}