void ShowGfxErrorDialog()
{
	// Application.Close will eventually post a quit message. We need to discard
	// that, so DialogBox() doesn't immediately exit. 
	auto msg = MSG();
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		if (msg.message == WM_QUIT) break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	int ret = DialogBox(Application.GetInstance(), MAKEINTRESOURCE(IDD_GFXERROR), NULL, GfxErrProcedure);
	if (ret == 0 || ret == -1)
	{
		LPVOID lpMsgBuf;
		DWORD err = GetLastError();
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );
		LogF("Error in GfxErrorDlg: %d - %s", err, StdStrBuf((wchar_t*)lpMsgBuf).getData());
		LocalFree(lpMsgBuf);
	}

	// If we discarded a quit message, re-post it now
	if (msg.message == WM_QUIT)
		PostQuitMessage(msg.wParam);
}