DWORD WINAPI ShellHookThread(PVOID pParam)
{

	HWND hWnd = CreateWindowW(L"Button", NULL, WS_OVERLAPPED,0, 0, 10, 10, HWND_MESSAGE, NULL, NULL, NULL);

#if defined(WIN64) || defined(_WIN64)
	SetWindowLongPtrW(hWnd,GWLP_WNDPROC,(LONG)ShellHookWndProc);
#else
	SetWindowLongW(hWnd,GWL_WNDPROC,(LONG)ShellHookWndProc);
#endif
	BOOL bRes = RegisterShellHookWindow(hWnd);

	MSG msg;
	// Ö÷ÏûÏ¢Ñ­»·:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}