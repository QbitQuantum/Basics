void CMemoryHackerDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
CMenu menu;
menu.LoadMenu(IDR_PROCESS_MENU); // our context menu
CMenu* pPopup = menu.GetSubMenu(0);

RECT rect;
GetWindowRect(&rect);
CPoint mousepos;
GetCursorPos(&mousepos);
pPopup->TrackPopupMenu(NULL,mousepos.x,mousepos.y, this); 

// The menu is a temporary MFC object, no need to delete it.
	*pResult = 0;
}