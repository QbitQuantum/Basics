void InitDocWnd(HWND hParentWnd)
{
	HMENU hMenu;
	HICON hIcon;
	if (hDocWnd != NULL) {
		DestroyWindow(hDocWnd);
		hDocWnd = NULL;
	}
	DocWndInfoReset2(hDocWnd);
	INILoadDocWnd();
	switch(PlayerLanguage){
  	case LANGUAGE_ENGLISH:
		hDocWnd = CreateDialog
			(hInst,MAKEINTRESOURCE(IDD_DIALOG_DOC_EN),hParentWnd,DocWndProc);
		break;
 	default:
	case LANGUAGE_JAPANESE:
		hDocWnd = CreateDialog
			(hInst,MAKEINTRESOURCE(IDD_DIALOG_DOC),hParentWnd,DocWndProc);
	break;
	}
	hIcon = LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_TIMIDITY), IMAGE_ICON, 16, 16, 0);
	if (hIcon!=NULL) SendMessage(hDocWnd,WM_SETICON,FALSE,(LPARAM)hIcon);
	DocWndInfoReset2(hDocWnd);
	hMenu = GetSystemMenu(DocWndInfo.hwnd,FALSE);
	switch(PlayerLanguage){
	case LANGUAGE_JAPANESE:
		AppendMenu(hMenu,MF_SEPARATOR,0,0);
		AppendMenu(hMenu,MF_STRING,IDM_DOCWND_CHOOSEFONT,"フォントの選択");
		break;
 	default:
  	case LANGUAGE_ENGLISH:
		AppendMenu(hMenu,MF_SEPARATOR,0,0);
		AppendMenu(hMenu,MF_STRING,IDM_DOCWND_CHOOSEFONT,"Choose Font");
		break;
	}
	DocWndInfoReset2(hDocWnd);
	INILoadDocWnd();
	DocWndInfoApply();
	ShowWindow(hDocWnd,SW_HIDE);
	UpdateWindow(hDocWnd);
	EnableWindow(GetDlgItem(hDocWnd,IDC_BUTTON_PREV),FALSE);
	EnableWindow(GetDlgItem(hDocWnd,IDC_BUTTON_NEXT),FALSE);
}