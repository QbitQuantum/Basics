    int APIENTRY
WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow )
{
    InitCommonControls();
    HWND hwnd = CreateDialog(hInstance,
		MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, dlgproc);
    if (!hwnd)
	return -1;
    g_hwnd = hwnd;
    SetClassLong(g_hwnd, GCL_HICON, (LONG)LoadIcon(hInstance,
		MAKEINTRESOURCE(IDI_NETUPVIM)));

    MSG msg;
    ShowWindow(hwnd, SW_SHOW);
    int res = MessageBox(hwnd,
	    "Vimのネットワークアップデートを開始しますか?\r\n"
	    "\r\n"
	    "アップデートには数分かそれ以上かかる場合も\r\n"
	    "あります。もしも現在Vimを使用している場合、\r\n"
	    "アップデートを始める前にVimを終了してください。"
	    , "Vimアップデートの確認", MB_YESNO | MB_ICONQUESTION);
    if (res == IDNO)
	DestroyWindow(hwnd);
    else
	_beginthread(do_update, 0, 0);
    while (GetMessage(&msg, NULL, 0, 0))
    {
	if (IsDialogMessage(hwnd, &msg))
	    continue;
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }

    return 0;
}