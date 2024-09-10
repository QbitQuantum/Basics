BOOL CMsgBoxDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT))
	{
		CWnd* pWnd = GetFocus(); //焦点何处

		if (pWnd != NULL)
		{
			if (pWnd->GetDlgCtrlID() == IDOK)
			{
				GetDlgItem(IDCANCEL)->SetFocus();

				return TRUE;
			}
			else if (pWnd->GetDlgCtrlID() == IDCANCEL)
			{
				GetDlgItem(IDOK)->SetFocus();

				return TRUE;
			}
			else if (pWnd->GetDlgCtrlID() == IDYES)
			{
				GetDlgItem(IDNO)->SetFocus();

				return TRUE;
			}
			else if (pWnd->GetDlgCtrlID() == IDNO)
			{
				GetDlgItem(IDYES)->SetFocus();

				return TRUE;
			}
		}
	}

	return CBCGPDialog::PreTranslateMessage(pMsg);
}