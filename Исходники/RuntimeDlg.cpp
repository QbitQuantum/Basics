void CRuntimeDlg::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);
	
	CWnd* pChild = GetWindow(GW_CHILD);
	
	if (pChild)
		pChild->SetFocus();
}