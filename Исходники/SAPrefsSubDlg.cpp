BOOL CSAPrefsSubDlg::PreTranslateMessage(MSG* pMsg) 
{
	// Don't let CDialog process the Escape key.
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	}
	
	// Don't let CDialog process the Return key, if a multi-line edit has focus
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		// Special case: if control with focus is an edit control with
		// ES_WANTRETURN style, let it handle the Return key.
		
		TCHAR szClass[10];
		CWnd* pWndFocus = GetFocus();
		if (((pWndFocus = GetFocus()) != NULL) &&
			IsChild(pWndFocus) &&
			(pWndFocus->GetStyle() & ES_WANTRETURN) &&
			GetClassName(pWndFocus->m_hWnd, szClass, 10) &&
			(lstrcmpi(szClass, _T("EDIT")) == 0))
		{
			pWndFocus->SendMessage(WM_CHAR, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}
		
		return FALSE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}