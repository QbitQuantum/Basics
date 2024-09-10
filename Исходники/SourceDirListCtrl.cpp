void CSourceDirListCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu srcDirMenu;
	srcDirMenu.CreatePopupMenu();
	srcDirMenu.AppendMenu(MF_STRING, IDM_SOURCE_DIR_REMOVE,		_T("Remove"));
	srcDirMenu.AppendMenu(MF_STRING, IDM_SOURCE_DIR_REMOVE_ALL,	_T("Remove All"));
	srcDirMenu.AppendMenu(MF_SEPARATOR);
	srcDirMenu.AppendMenu(MF_STRING, IDM_SOURCE_DIR_SELECT_ALL,	_T("Select All\tCtrl+A"));
	srcDirMenu.AppendMenu(MF_SEPARATOR);
	srcDirMenu.AppendMenu(MF_STRING, IDM_SOURCE_DIR_CHECK,		_T("Check"));
	srcDirMenu.AppendMenu(MF_STRING, IDM_SOURCE_DIR_UNCHECK,	_T("Uncheck"));
	srcDirMenu.AppendMenu(MF_SEPARATOR);
	srcDirMenu.AppendMenu(MF_STRING, IDM_SOURCE_DIR_OPEN_DIR,	_T("Open Folder"));

	//Set menu enable status
	int nCount = GetSelectedCount();
	if(nCount <= 0)
	{
		srcDirMenu.EnableMenuItem(IDM_SOURCE_DIR_REMOVE, MF_BYCOMMAND | MF_GRAYED);
		srcDirMenu.EnableMenuItem(IDM_SOURCE_DIR_CHECK, MF_BYCOMMAND | MF_GRAYED);
		srcDirMenu.EnableMenuItem(IDM_SOURCE_DIR_UNCHECK, MF_BYCOMMAND | MF_GRAYED);
	}
	if(nCount != 1)
	{
		srcDirMenu.EnableMenuItem(IDM_SOURCE_DIR_OPEN_DIR, MF_BYCOMMAND | MF_GRAYED);
	}

	srcDirMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);	
}