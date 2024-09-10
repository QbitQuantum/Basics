BOOL CThetaGridAdjustmentSimpleOutputDlg::OnInitDialog() 
{
	int i;
	CString T;
	BOOL b;
	CWnd* pWnd;
	CDC* pDC;

	pWnd=this;
	pWnd->CenterWindow();
	if (m_nType==1) pWnd->SetWindowTextW(L"Simple Output - Event's Arguments"); //if dealing with the event's arguments
	else if (m_nType==2) pWnd->SetWindowTextW(L"Simple Output - Complement Clause"); //if dealing with the event's complement clause
	CDialog::OnInitDialog();
	m_bSubjectRaised=FALSE;
	m_strTargetFontName=m_pDoc->GetTargetLanguageFontName(); //used in ChangeFont
	if (HFONT(m_fontTarget)==NULL)        //first time this modeless dialog activated
	{
		//create the fonts that will be used in the combo boxes
		pWnd=&m_datatblInput;
		pDC=pWnd->GetDC();	                    //get a pointer to the device context
		T=m_pDoc->GetSourceLanguageFontName(4);
		b=m_fontArial.CreatePointFont(90,L"Arial",pDC);
		if (b==FALSE) AfxMessageBox(L"Unable to create Arial font.",MB_OK);
		i=m_pDoc->GetTargetLanguageFontSize();
		b=m_fontTarget.CreatePointFont(10*i,m_strTargetFontName,pDC);
		if (b==FALSE) AfxMessageBox(L"Unable to create Target font.",MB_OK);
	}
	SetupTable();
	if (m_nType==2)        //if specifying features for object complement clause
	{
		pWnd=GetDlgItem(IDC_BUTTONFEATURESET);
		pWnd->MoveWindow(12,68,75,22);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}