void CNifConvertDlg::OnContextMenu(CWnd *pWnd, CPoint point)
{
	CMenu*	pPopUp(NULL);
	CMenu	menuBar;

	menuBar.LoadMenu(IDR_MENU_POPUP);

	pPopUp = menuBar.GetSubMenu(0);
	pPopUp->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}