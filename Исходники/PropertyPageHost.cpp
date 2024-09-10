// unfortunately there is a bug in MFC that can cause an infinite loop
// when the property page is hosting an OLE control so we fix
// it by providing a replacement to the buggy code
BOOL COccManager::IsDialogMessage(CWnd* pWndDlg, LPMSG lpMsg)
{
	CWnd* pWndFocus = CWnd::GetFocus();
//	HWND hWndFocus = pWndFocus->GetSafeHwnd();
//	HWND hWndDlg = pWndDlg->GetSafeHwnd();
	UINT uMsg = lpMsg->message;

	if (((uMsg >= WM_KEYFIRST) && (uMsg <= WM_KEYLAST)) ||
		((uMsg >= WM_MOUSEFIRST) && (uMsg <= WM_MOUSELAST)))
	{
		CWnd* pWndCtrl = pWndFocus;

		// Walk up the parent chain, until we find an OLE control.
		while ((pWndCtrl != NULL) && (pWndCtrl->m_pCtrlSite == NULL) &&
			(pWndCtrl->GetParent() != pWndDlg))
		{
			pWndCtrl = pWndCtrl->GetParent();
		}

		// let the control attempt to translate the message
		if (pWndCtrl != NULL && pWndCtrl->m_pCtrlSite != NULL &&
			pWndCtrl->m_pCtrlSite->m_pActiveObject != NULL &&
			pWndCtrl->m_pCtrlSite->m_pActiveObject->TranslateAccelerator(lpMsg) == S_OK)
		{
			return TRUE;
		}

		// handle CTRLINFO_EATS_RETURN and CTRLINFO_EATS_ESCAPE flags
		if ((uMsg == WM_KEYUP || uMsg == WM_KEYDOWN || uMsg == WM_CHAR) &&
			pWndCtrl != NULL && pWndCtrl->m_pCtrlSite != NULL &&
			((LOWORD(lpMsg->wParam) == VK_RETURN &&
			 (pWndCtrl->m_pCtrlSite->m_ctlInfo.dwFlags & CTRLINFO_EATS_RETURN)) ||
			(LOWORD(lpMsg->wParam) == VK_ESCAPE &&
			 (pWndCtrl->m_pCtrlSite->m_ctlInfo.dwFlags & CTRLINFO_EATS_ESCAPE))))
		{
			return FALSE;
		}
	}

	// else simple default
	// because this is where the MFC bug existed
	return ::IsDialogMessage(pWndDlg->GetSafeHwnd(), lpMsg);
}