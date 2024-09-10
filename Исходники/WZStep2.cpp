BOOL CWZStep2::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	//-- needn't the help button begin
	(pSheet->GetDlgItem(IDHELP))->ShowWindow(FALSE);
	//-- needn't the help button end

	// this is what I added.
	// m_SourceImage=g_ImageFileName;
	m_SourceImage=g_RestoreInfo.szImageFile;

	m_Comment = g_RestoreInfo.szImageComment;
	
	UpdateData(FALSE);

    //GetDlgItem(IDC_COMMENT)->SetWindowText("Comment");

	// GetDlgItem(IDC_SOURCE_IMAGE)->SetWindowText(g_ImageFileName);
    
	//-- this is what I added.
	//-- GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

	// MAIL_BACKUP is 1
    // Outlook Express Mail is a bit different, so we
	// give it a special type.

	if(
		(MAIL_BACKUP == g_RestoreInfo.wImageType) ||
		(OE_MAIL_BACKUP == g_RestoreInfo.wImageType ) ||
		(WIN_MAIL_BACKUP == g_RestoreInfo.wImageType )
	  )
	{
		// first make RestoreType to total restore
		// then disable the part restore choice
		m_RestoreType=0;
		UpdateData(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
	}

	return CPropertyPageEx::OnSetActive();
}