LRESULT CResendDlg::OnListRClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
	CPoint pt;
    GetCursorPos(&pt);
    CMenu menu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_POPUPMENU));  
    CMenu submenu = menu.GetSubMenu(5);

    strconv_t strconv;
    CString sSelectAll = Utility::GetINIString(g_CrashInfo.m_sLangFileName, _T("ResendDlg"), _T("SelectAll"));
    CString sDeselectAll = Utility::GetINIString(g_CrashInfo.m_sLangFileName, _T("ResendDlg"), _T("DeselectAll"));
	CString sDeleteSelected = Utility::GetINIString(g_CrashInfo.m_sLangFileName, _T("ResendDlg"), _T("DeleteSelected"));
	CString sDeleteAll = Utility::GetINIString(g_CrashInfo.m_sLangFileName, _T("ResendDlg"), _T("DeleteAll"));

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING;

    mii.dwTypeData = sSelectAll.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_SELECTALL, FALSE, &mii);

    mii.dwTypeData = sDeselectAll.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_DESELECTALL, FALSE, &mii);

	mii.dwTypeData = sDeleteSelected.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_DELETESELECTED, FALSE, &mii);

	mii.dwTypeData = sDeleteAll.GetBuffer(0);  
    submenu.SetMenuItemInfo(ID_MENU6_DELETEALL, FALSE, &mii);

	// Get count of checked list items
	int nItems = 0;
	int nChecked = 0;
	int i;
    for(i=0; i<m_listReports.GetItemCount(); i++)
    {
		nItems++;

		// If list item checked
		if(m_listReports.GetCheckState(i))
			nChecked++;
	}
	
	submenu.EnableMenuItem(ID_MENU6_SELECTALL, nItems>0?MF_ENABLED:MF_DISABLED);
	submenu.EnableMenuItem(ID_MENU6_DESELECTALL, nItems>0?MF_ENABLED:MF_DISABLED);	
	submenu.EnableMenuItem(ID_MENU6_DELETESELECTED, nChecked>0?MF_ENABLED:MF_DISABLED);
	submenu.EnableMenuItem(ID_MENU6_DELETEALL, nItems>0?MF_ENABLED:MF_DISABLED);

	submenu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);
    return 0;

	return 0;
}