int runDialog(HINSTANCE hInst, int cmdShow, int dialogId, int iconId, int accelTableId, DLGPROC dialogProc, LPARAM lp)
{
	HWND   hDlg = NULL;
	HACCEL hAccel = NULL;
	MSG    msg = { 0 };
	BOOL   ret = FALSE;
	HICON  hIcon16 = NULL, hIcon32 = NULL;

	InitCommonControls();
	g_hSysFont = Font_cloneFromSystem(); // retrieve global system font
	hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(dialogId), 0, dialogProc, lp);

	if(iconId) { // put icon on dialog system menu, if any (probably yes)
		hIcon16 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(iconId), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		hIcon32 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(iconId), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon16);
		SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon32);
	}

	ShowWindow(hDlg, cmdShow);

	if(accelTableId) // load accelerators table, if any
		hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(accelTableId));
	
	while((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
		if(ret == -1) return -1; // failure
		if(!(hAccel && TranslateAccelerator(hDlg, hAccel, &msg)) && !IsDialogMessage(hDlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if(hIcon16) DestroyIcon(hIcon16); // release the dialog icons
	if(hIcon32) DestroyIcon(hIcon32);
	Font_free(g_hSysFont); // release global system font
	return (int)msg.wParam; // this can be the return value of the program
}