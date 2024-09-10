void WinLuaOnStop()
{
	HWND hDlg = hLuaDlg;
	//LuaPerWindowInfo& info = LuaWindowInfo[hDlg];

	HWND prevWindow = GetActiveWindow();
	SetActiveWindow(hDlg); // bring to front among other script/secondary windows, since a stopped script will have some message for the user that would be easier to miss otherwise
	//if (prevWindow == AfxGetMainWnd()->GetSafeHwnd()) SetActiveWindow(prevWindow);

	//info.started = false;
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_LUABROWSE), true);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_LUASTOP), false);
	SetWindowText(GetDlgItem(hDlg, IDC_BUTTON_LUARUN), "Run");
	//      if(statusOK)
	//              Show_Genesis_Screen(MainWindow->getHWnd()); // otherwise we might never show the last thing the script draws
	//if(info.closeOnStop)
	//      PostMessage(hDlg, WM_CLOSE, 0, 0);
}