BOOL CDlgLinkProperties::OnInitDialog()
{
	CDialog::OnInitDialog();
	std::map<int, DTALinkType>:: const_iterator itr;

	for(itr = m_pDoc->m_LinkTypeMap.begin(); itr != m_pDoc->m_LinkTypeMap.end(); itr++)
	{
	
		CString str;
		str.Format("%d,%s",itr->first,itr->second .link_type_name.c_str ());
		m_LinkTypeComboBox.AddString (str);

		if(LinkType == itr->first)
		{
			m_LinkTypeComboBox.SetCurSel (m_LinkTypeComboBox.GetCount ()-1);
		}
	}

		SetDlgItemTextA(IDC_STATIC_UNIT_SPEED_LIMIT,"distance unit/hour");
		SetDlgItemTextA(IDC_STATIC_UNIT_DENSITY,"(veh/distance/ln)");

	EnableDataBasedOnLinkType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}