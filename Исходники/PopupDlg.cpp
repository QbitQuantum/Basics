BOOL CPopupDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	
	AnimateWindow(200, AW_VER_POSITIVE | AW_HIDE);	
	numOfDlg--;


	//전체 종료일 때는 postmessage 보내면 안됨
	if(!m_bFlagAllDestroy)
		GetParent()->PostMessage(WM_CLOSEPOPDLG, (WPARAM)this, 0);
	
	return CDialogEx::DestroyWindow();
}