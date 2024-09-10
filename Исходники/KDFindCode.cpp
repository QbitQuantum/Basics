void __stdcall IDAP_run(int arg)
{

	HWND hMainDlg = NULL;
	if(NULL == (hMainDlg=FindWindow("#32770", "Find Code")) )
	{
		EnumWindows(EnumWindowsProc,0);
		hMainDlg = CreateDialog(g_hInstance, (LPCTSTR)IDD_DIALOG_FINDCODE, NULL,(DLGPROC)Main_Proc);
		if(NULL == hMainDlg)
		{
			msg("hMainDlg NULL 0x%X\n",GetLastError());
		}
		else
		{
			ShowWindow(hMainDlg, SW_SHOWNA);
		}
	}
	else
	{
		POINT p;
		GetCursorPos(&p);
		RECT rect;
		GetWindowRect(hMainDlg,&rect);   //rect保存窗口大小
		MoveWindow(hMainDlg, p.x, p.y, rect.right - rect.left, rect.bottom - rect.top, TRUE);
		SwitchToThisWindow(hMainDlg, TRUE);
	}
	
	

}