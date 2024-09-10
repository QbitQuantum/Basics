BOOL CCardopenConsumeView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd * pWnd = GetFocus();
		if (pWnd)
		{
			if (pWnd->GetDlgCtrlID() == IDC_BUTTON_STARTTIME 
				||pWnd->GetDlgCtrlID() == IDC_BUTTON_ENDTIME
				||pWnd->GetDlgCtrlID() == IDC_BUTTON_QUERY)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
			{
				PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_QUERY, BN_CLICKED),(LPARAM)GetDlgItem(IDC_BUTTON_QUERY)->m_hWnd);
			}
		}
	}

	return CIBAFormView::PreTranslateMessage(pMsg);
}