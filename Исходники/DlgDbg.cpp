BOOL CDlgDbg::Create(HWND hWndParent, CMgrData *pMgrData)
{
	CWnd *pWnd;

	m_pMgrData	= pMgrData;
	m_pSock		= m_pMgrData->GetUraraSockTCP ();
	pWnd		= CWnd::FromHandle (hWndParent);

	CDialog::Create (IDD, pWnd);

	ShowWindow (SW_SHOW);
	pWnd->SetFocus ();

	return TRUE;
}