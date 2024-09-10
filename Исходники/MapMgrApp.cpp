BOOL CMapMgrApp::FirstInstance()
{
	CString	strCaption;
	strCaption.LoadString(AFX_IDS_APP_TITLE);
	CWnd *pWndFirst = CWnd::FindWindow(NULL,strCaption);
	if( pWndFirst )
	{
		CWnd *pWndPopup = pWndFirst->GetLastActivePopup();
		pWndFirst->BringWindowToTop();
		if(pWndFirst->IsIconic())
			pWndFirst->ShowWindow(SW_SHOWNORMAL);
		if(pWndFirst != pWndPopup)
			pWndPopup->BringWindowToTop();
		return FALSE;
	}
	return TRUE;
}