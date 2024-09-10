void CJobControlDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLISTVIEW	lpnmlv = (LPNMLISTVIEW)pNMHDR;
	if (lpnmlv->iItem >= 0) {
		CMenu	menu;
		menu.LoadMenu(IDR_JOB_CONTROL_CTX);
		CMenu	*mp = menu.GetSubMenu(0);
		CToolDlg::UpdateMenu(this, &menu);
		CPoint	pt;
		GetCursorPos(&pt);
		UpdateMenu(this, mp);	// call menu's UI handlers
		mp->TrackPopupMenu(0, pt.x, pt.y, this);
	}
	*pResult = 0;
}