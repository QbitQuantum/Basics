// returns how many bytes were written to winamp's space
unsigned long WriteLocalToWinamp(void *localBuf, void *remoteBuf, unsigned long bufsize)
{
	int isError;
	HANDLE hWinamp;
	unsigned long dWinamp;

	// find the process id
	GetWindowThreadProcessId(hwndWinamp, &dWinamp);

	// open the process object
	hWinamp = OpenProcess(PROCESS_ALL_ACCESS,false,dWinamp);
	if(hWinamp == NULL) return 0;

	isError = WriteProcessMemory(hWinamp, remoteBuf, localBuf, bufsize, NULL);

	CloseHandle(hWinamp);

	if(!isError) return 0;
	else return bufsize;
}