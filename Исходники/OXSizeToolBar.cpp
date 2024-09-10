// tool tip notification handler for tool bar
afx_msg void COXSizeToolBar::OnTBNToolTip(UINT /* uID */, NMHDR* pNMHDR, LRESULT* /* pResult */)
{
	TOOLTIPTEXT* pTip = (TOOLTIPTEXT*)pNMHDR;
	pTip->hinst = NULL;
	pTip->lpszText = NULL;
	UINT ButtonId = PtrToUint(pTip->hdr.idFrom);	

	CString strText;
	if (strText.LoadString(ButtonId))
	{
		LPCTSTR pTipText = _tcschr(strText, _T('\n'));   // tool tip is after "\n" in the string
		if (pTipText != NULL)
		{	
			UTBStr::tcscpy(pTip->szText, 80, pTipText + 1);
			pTip->lpszText = pTip->szText;

			// try to ensure tool tip control and ensure it is top most in the Z-order
			CToolTipCtrl* pToolTipCtrl = m_ToolCtrl.GetToolTips();
			pToolTipCtrl->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

		}	
		// Set the text in the main window. Doesn't appear to be an easy way to check if
		// we're not over any particular bit of the tool tip.
		AfxGetMainWnd()->SendMessage(WM_SETMESSAGESTRING, ButtonId);
		return; 
	}	

	TRACE1("COXSizeToolBar:No Tooltip prompt for ID=%d\n", ButtonId);
	return;	
}