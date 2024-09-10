BOOL CMarmaladeNonModalOptionsDlg::OnInitDialog()
{
	__super::OnInitDialog();

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetIcon(Icon16x16(IDI_MARMALADE), false);

	GetClientRect(m_rectClient);

	// Get the holder's rect and delete the frame placeholder.
	CWnd* pFrame = GetDlgItem(IDC_STATIC_FRAME);
	ASSERT(NULL != pFrame);
	pFrame->GetWindowRect(m_rectHolder);
	pFrame->DestroyWindow();
	ScreenToClient(m_rectHolder);

	if (NULL == m_pHolder)
		return FALSE;

	// Create the holder.
	m_pHolder->Create(_T(""), m_rectHolder, this);

	// Create section 1 and attach it to the holder.
	CRhRdkExpandingSection* pSection1 = new CMarmaladeOptionsSection1;
	pSection1->CreateAndAttachToHolder(m_pHolder);

	// Create section 2 and attach it to the holder.
	CRhRdkExpandingSection* pSection2 = new CMarmaladeOptionsSection2;
	pSection2->CreateAndAttachToHolder(m_pHolder);

	// Create section 3 and attach it to the holder.
	CRhRdkExpandingSection* pSection3 = new CMarmaladeOptionsSection1_Detailed;
	pSection3->CreateAndAttachToHolder(m_pHolder);

	// Create section 4 and attach it to the holder.
	CRhRdkExpandingSection* pSection4 = new CMarmaladeOptionsSection2_Detailed;
	pSection4->CreateAndAttachToHolder(m_pHolder);

	m_pHolder->SetExpertMode(false);

	const int iCheck = m_pHolder->ExpertMode();
	m_check_expert.SetCheck(iCheck);

	return FALSE;
}