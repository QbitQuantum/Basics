LRESULT CAddSpecFuncDlg::OnBnClickDestroy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CButton wndCheck = GetDlgItem(IDC_CHECK_DESTROY);
	CButton wndCheckAdd = GetDlgItem(IDC_CHECK_REMOVE_DESTROY);
	bool bChecked = (wndCheck.GetCheck() == BST_CHECKED);

	if (!bChecked && m_bEnableDestroy)
	{
		wndCheckAdd.SetCheck(BST_UNCHECKED);
		wndCheckAdd.EnableWindow(FALSE);
	}
	else
	{
		wndCheckAdd.EnableWindow();
	}
	return 0;
}