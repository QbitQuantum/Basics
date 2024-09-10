void CFileOptDlg::OnRclickListFileopt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu popMenu;
	popMenu.LoadMenu(IDR_POPMENU_FILE);
	CPoint point;
	GetCursorPos(&point);
	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	*pResult = 0;
}