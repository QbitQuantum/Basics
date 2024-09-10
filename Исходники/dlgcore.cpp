LRESULT CDialog::HandleInitDialog(WPARAM, LPARAM)
{
	PreInitDialog();

#ifndef _AFX_NO_OCC_SUPPORT
	// create OLE controls
	COccManager* pOccManager = afxOccManager;
	if ((pOccManager != NULL) && (m_pOccDialogInfo != NULL))
	{
		BOOL bDlgInit;
		if (m_lpDialogInit != NULL)
			bDlgInit = pOccManager->CreateDlgControls(this, m_lpDialogInit,
				m_pOccDialogInfo);
		else
			bDlgInit = pOccManager->CreateDlgControls(this, m_lpszTemplateName,
				m_pOccDialogInfo);

		if (!bDlgInit)
		{
			TRACE0("Warning: CreateDlgControls failed during dialog init.\n");
			EndDialog(-1);
			return FALSE;
		}
	}
#endif

	// Default will call the dialog proc, and thus OnInitDialog
	BOOL bResult = Default();

#ifndef _AFX_NO_OCC_SUPPORT
	if (bResult && (m_nFlags & WF_OLECTLCONTAINER))
	{
		CWnd* pWndNext = GetNextDlgTabItem(NULL);
		if (pWndNext != NULL)
		{
			pWndNext->SetFocus();   // UI Activate OLE control
			bResult = FALSE;
		}
	}
#endif

	return bResult;
}