void CPreferencesPrint::OnFooterButton() 
{
	CMenu menu;
	CMenu* pPopup;
	RECT rc;
	int i = SendDlgItemMessage (IDC_PRNDLG_HEADERBTN, BM_GETSTATE, 0, 0);
	::GetWindowRect(::GetDlgItem(m_hWnd, (i & BST_FOCUS) ? IDC_PRNDLG_HEADERBTN : IDC_PRNDLG_FOOTERBTN), &rc);
	menu.LoadMenu(IDR_POPUPS);
	pPopup = menu.GetSubMenu(3);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rc.right, rc.top, this);
}