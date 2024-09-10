void CDialogConf::OnInitMenuPopup(CMenuHandle menuPopup, UINT nIndex, BOOL bSysMenu)
{
	if (bSysMenu)
	{
		if (!IsMenuItemExist(menuPopup, IDM_ALWAYS_ON_TOP))
		{
			//menuPopup.InsertMenu(SC_MINIMIZE, MF_BYCOMMAND);
			menuPopup.InsertMenu(SC_MINIMIZE, MF_BYCOMMAND, IDM_ALWAYS_ON_TOP, L"Always on top");
			//menuPopup.InsertMenu(SC_MINIMIZE, MF_BYCOMMAND);
		}
		
		if (GetWindowLongPtr(GWL_EXSTYLE) & WS_EX_TOPMOST)
		{
			menuPopup.CheckMenuItem(IDM_ALWAYS_ON_TOP, MF_BYCOMMAND | MF_CHECKED);
		}
		else
		{
			menuPopup.CheckMenuItem(IDM_ALWAYS_ON_TOP, MF_BYCOMMAND | MF_UNCHECKED);
		}
	}
}