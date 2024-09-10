/*-----------------------------------------------------------------------------*/
BOOL OpenToolBox(HWND hWnd) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	// Make sure the window isn't already open
	if (!GetWindow(ghWndToolBox,GW_HWNDFIRST)) {
		ghWndToolBox = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DLG_TOOLBOX), ghWndCanvas, (DLGPROC)ToolBoxDlg);
		ShowWindow(ghWndToolBox, SW_SHOW);

		CheckMenuItem(hMenu, ID_FORMAT_TOOLBOX, MF_CHECKED);

		// Make sure the correct radio button is checked
		if (GetMenuState(hMenu, ID_TOOLS_LINE, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_LINE), TRUE);
		}
		else if (GetMenuState(hMenu, ID_TOOLS_RECTANGLE, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_RECTANGLE), TRUE);
		}
		else if (GetMenuState(hMenu, ID_TOOLS_POLYGON, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_POLYGON), TRUE);
		}
		else if (GetMenuState(hMenu, ID_TOOLS_SELECT, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_SELECT), TRUE);
		}
	}
	else {
		// Close the window if it was already open
		DestroyWindow(ghWndToolBox);

		CheckMenuItem(hMenu, ID_FORMAT_TOOLBOX, MF_UNCHECKED);
	}



	return TRUE;
}