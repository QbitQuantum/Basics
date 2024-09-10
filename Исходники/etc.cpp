void SendRestartMessage (char *WindowClass, char *Title)
{
	HWND hPrevWnd = FindWindow(WindowClass, Title);
	if (!hPrevWnd) return;

	// Command line argument를 hPrevWnd 윈도우로 전송한다.
	char *cmd = GetCommandLine();
	int n_cmd = strlen(cmd)+1;
	char *buff = (char *)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, n_cmd);

	strcpy (buff, cmd);

	COPYDATASTRUCT tip;
	tip.dwData = 0;
	tip.cbData = n_cmd;
	tip.lpData = buff;
	
	SendMessage (hPrevWnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&tip);
	
	::HeapFree(::GetProcessHeap(), 0, buff);

	PostMessage (hPrevWnd, WM_RESTART, 0, 0);
	FlashWindow (hPrevWnd, TRUE);
}