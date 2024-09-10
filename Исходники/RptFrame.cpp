int CRptFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if( !m_Acct_DlgBar.Create( this, IDD_ACCT_DLGBAR, CBRS_TOP, 1)  ) {
		TRACE("CRptFrame: Failed to create dialog bar\n");
		return -1;
	}

	CWnd* pAcct = m_Acct_DlgBar.GetDlgItem( IDC_ACCT );
	pAcct->SetFocus( );
	CWinApp* pApp = AfxGetApp( );
	//CFrameWnd* pMainFrame = (CFrameWnd*) (AfxGetApp()->m_pMainWnd);
	//CJevDoc* pDoc = (CJevDoc*) pMainFrame->GetActiveDocument();
	//ASSERT_VALID(pDoc);
	CJevApp* pJevApp =  ((CJevApp*) AfxGetApp());
	CJevDoc* pDoc = pJevApp -> m_pActiveJevDoc;
	int ar = pDoc->njeGetActiveRecord();
	CJournalEntry* pJE = pDoc->m_JEArray.GetAtJe( ar );
	m_sAcct = pJE->GetCrAcct();
	m_Acct_DlgBar.SetDlgItemText( IDC_ACCT, m_sAcct);



	//GotoDlgCtrl( pAcct );
	return 0;
}