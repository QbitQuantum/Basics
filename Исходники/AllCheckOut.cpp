BOOL CDlgAllCheckOut::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd * pWnd = GetFocus();
		
		if (pWnd != NULL)
		{
			if (pWnd->GetDlgCtrlID() == IDC_EDIT_FIND)
			{
				OnBnClickedButtonQuery();
				return TRUE;
			}
		}
	}

	//拦截焦点

	if (WM_CHAR == pMsg->message && pMsg->wParam != VK_RETURN)
	{
		CWnd* pWnd = GetFocus();
		
		if (pWnd != NULL && pWnd->GetDlgCtrlID() != IDC_EDIT_FIND)
		{
			GetDlgItem(IDC_EDIT_FIND)->SetFocus();
			GetDlgItem(IDC_EDIT_FIND)->PostMessage(WM_CHAR, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}
	}

	return CIBADialog::PreTranslateMessage(pMsg);
}