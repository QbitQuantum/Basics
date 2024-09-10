BOOL CJobsConfigure::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTokenString tokstr;
	CString token, str;
	BOOL bInShow;
	int i;

	tokstr.Create(m_ColNames);
	tokstr.PrepareParse( );
	token=tokstr.GetToken();  
	while(!token.IsEmpty())
	{
		m_ListShow.AddString(token);
		token=tokstr.GetToken();
	}
	tokstr.Reset();

	tokstr.Create(m_SpecNames);
	tokstr.PrepareParse( );
	token=tokstr.GetToken();  
	while(!token.IsEmpty())
	{
		for (bInShow = FALSE, i = -1; ++i < m_ListShow.GetCount(); )
		{
			m_ListShow.GetText(i, str);
			if (str == token)
			{
				bInShow = TRUE;
				break;
			}
		}
		if (!bInShow)
			m_ListOther.AddString(token);
		token=tokstr.GetToken();
	}
	m_ListOther.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}