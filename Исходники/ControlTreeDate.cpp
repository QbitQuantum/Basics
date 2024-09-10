/////////////////////////////////////////////////////////////////////////////
// CControlTreeDate message handlers
// ---
void CControlTreeDate::OnKillFocus( CWnd* pNewWnd ) {
	CDateTimeCtrl::OnKillFocus(pNewWnd);
												
	if ( !pNewWnd || !IsChild(pNewWnd) ) {
		CMonthCalCtrl *pMonthCtrl = GetMonthCalCtrl();
		if ( !pMonthCtrl || pMonthCtrl->GetSafeHwnd() != pNewWnd->GetSafeHwnd() ) {
			CString str;
			GetWindowText( str );

			// Send Notification to parent of ListView ctrl
			TV_DISPINFO dispinfo;
			dispinfo.hdr.hwndFrom = GetParent()->GetSafeHwnd();
			dispinfo.hdr.idFrom = GetDlgCtrlID();
			dispinfo.hdr.code = TVN_ENDLABELEDIT;

			dispinfo.item.mask = TVIF_TEXT;
			dispinfo.item.hItem = m_hItem;
			dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
			dispinfo.item.cchTextMax = str.GetLength();

			GetParent()->GetParent()->SendMessage( WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo );

			PostMessage( WM_CLOSE );
		}
	}
}