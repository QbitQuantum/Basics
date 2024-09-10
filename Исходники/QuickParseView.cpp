void CQuickParseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuickParseView)
	DDX_Check(pDX, IDC_CHECKTrace, m_bTrace);
	DDX_Text(pDX, IDC_EDITInput, m_sInput);
	DDX_Text(pDX, IDC_EDITAmpleOutput, m_sOutput);
	DDX_Text(pDX, IDC_EDITTraceMorphs, m_sTraceMorphs);
	DDX_Check(pDX, IDC_CHECKManualParse, m_bManualParse);
	//}}AFX_DATA_MAP

	if(!pDX->m_bSaveAndValidate)
	{
		CEdit* pE = (	CEdit*)GetDlgItem(IDC_EDITTraceMorphs);
		if(pE)
			pE->EnableWindow(m_bTrace);
#ifndef hab218
		CButton* pB = (CButton*)GetDlgItem(IDC_CHECKManualParse);
		if (pB)
			pB->EnableWindow(m_bTrace);
		CStatic* pS = (CStatic*)GetDlgItem(IDC_STATICManualParse);
		if (pS)
			pS->EnableWindow(m_bTrace);
#endif // hab218
	}
		// i removed the button because opening a window with this text
	// will take some more work

	if(!pDX->m_bSaveAndValidate && m_pAmpleProcess)
	{
		//CWnd* pButton = GetDlgItem(IDC_Errors);
		CWnd* pMessage = GetDlgItem(IDC_ErrorStatic);
		CWnd* pMessageNoTrace = GetDlgItem(IDC_ErrorStatic2);
		CWnd* pIcon = GetDlgItem(IDC_ErrorIcon);
		CWnd* pMessageRefreshed = GetDlgItem(IDC_RefreshNotice);


		// jdh 3/14/2000
		if(m_bDidRefresh)
			pMessageRefreshed->ModifyStyle(NULL, WS_VISIBLE);
		else
			pMessageRefreshed->ModifyStyle(WS_VISIBLE,NULL);
		pMessageRefreshed->Invalidate();


		if(/*pButton &&*/ pIcon && m_pAmpleProcess->getLastRunHadError())
		{
			//pButton->ModifyStyle(NULL, WS_VISIBLE);
			pMessage->ModifyStyle(NULL, WS_VISIBLE);
			pMessage->Invalidate();
			if(!m_bTrace)
			{
				pMessageNoTrace->ModifyStyle(NULL, WS_VISIBLE);
				pMessageNoTrace->Invalidate();
			}
			else // trace is on
			{
				pMessageNoTrace->ModifyStyle(WS_VISIBLE, NULL);
				pMessageNoTrace->Invalidate();
			}

			pIcon->ModifyStyle(NULL, WS_VISIBLE);
			pIcon->Invalidate();
		}
		else if(/*pButton &&*/ pIcon)
		{
			//pButton->ModifyStyle(WS_VISIBLE, NULL);
			pMessage->ModifyStyle(WS_VISIBLE, NULL);
			pMessage->Invalidate();
			pMessageNoTrace->ModifyStyle(WS_VISIBLE, NULL);
			pMessageNoTrace->Invalidate();
			pIcon->ModifyStyle(WS_VISIBLE, NULL);
			pIcon->Invalidate();
		}
		this->Invalidate();
	}
}