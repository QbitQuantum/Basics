BOOL CDateDialog::OnInitDialog()
{
	CCSDialog::OnInitDialog();

	m_pListBox = &m_listBox; // set static member
	GetLocalTime(&m_time);
	m_id = GetUserDefaultLCID();

	EnumDateFormats(DateFmtEnumProc, m_id, DATE_SHORTDATE);
	EnumDateFormats(DateFmtEnumProc, m_id, DATE_LONGDATE);
	EnumTimeFormats(TimeFmtEnumProc, m_id, 0);

	m_pListBox = NULL;
	m_listBox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}