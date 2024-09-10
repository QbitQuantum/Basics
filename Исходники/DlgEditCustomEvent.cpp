BOOL DlgEditCustomEvent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	TString str;
	
// TODO: Add extra initialization here
	CComboBox * p;
	int i;

	p = (CComboBox *)GetDlgItem(IDC_COMBO1);
	for(i =0; i < 30; i++)
	{
		str.Format("%s Tithi (%s Paksa)", GCStrings::GetTithiName(i), GCStrings::GetPaksaName(i/15));
		p->AddString(str);
	}
	p->SetCurSel(this->m_nTithi);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);

	p = (CComboBox *)GetDlgItem(IDC_COMBO2);
	for(i = 0; i < 12; i++)
	{
		p->AddString(GCStrings::GetMasaName(i));
	}
	p->SetCurSel(this->m_nMasa);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);

	p = (CComboBox *)GetDlgItem(IDC_COMBO3);
	for(i = 0; i <= 6; i++)
	{
		p->AddString(GCStrings::GetEventClassText(i));
	}
	p->SetCurSel(this->m_nClass);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);
	else
		p->EnableWindow(GCDisplaySettings::getValue(44)==1);
	
	p = (CComboBox *)GetDlgItem(IDC_COMBO4);
	p->AddString("no fast");
	p->AddString(GCStrings::GetFastingName(0x201));
	p->AddString(GCStrings::GetFastingName(0x202));
	p->AddString(GCStrings::GetFastingName(0x203));
	p->AddString(GCStrings::GetFastingName(0x204));
	p->AddString(GCStrings::GetFastingName(0x205));
	p->SetCurSel(this->m_nFastType);
	if (m_nClass != 6)
		p->EnableWindow(FALSE);

	if (m_nClass != 6)
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}