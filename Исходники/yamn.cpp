DWORD WINAPI YAMNHotKeyThread(LPVOID Param)
{
	MSG WinMessage;
	WORD HotKey = LOWORD(Param);
	int HotKeyID;

//	register hotkey for main YAMN thread first 
	if(!(HotKeyID=RegisterHotKey(NULL,(int)GlobalAddAtom(YAMN_HKCHECKMAIL),HIBYTE(HotKey),LOBYTE(HotKey))))
		return 0;

	while(1)
	{
		GetMessage(&WinMessage,NULL,WM_HOTKEY,WM_YAMN_CHANGEHOTKEY);

//	if we want to close miranda, we get event and do not run pop3 checking anymore
		if(WAIT_OBJECT_0==WaitForSingleObject(ExitEV,0))
			break;

		switch(WinMessage.message)
		{
//	user pressed hotkey
			case WM_HOTKEY:
				ForceCheckSvc((WPARAM)0,(LPARAM)0);
				break;
//	hotkey changed
			case WM_YAMN_CHANGEHOTKEY:
				UnregisterHotKey(NULL,HotKeyID);
				HotKeyID=RegisterHotKey(NULL,(int)GlobalAddAtom(YAMN_HKCHECKMAIL),WinMessage.wParam,WinMessage.lParam);
				break;
		}
	}
	return 1;
}