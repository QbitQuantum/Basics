BOOL CTagDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// if tagging line don't add items to combobox
	if (tagLine) {
		return TRUE;
	}
	// Add items from tag lists to the combobox depending on data type
	switch (dataType) {
	case 0 : 
		{
			for (int i=0; i<boolTags->GetSize(); i++) {
				m_Tag.AddString(boolTags->GetAt(i));
			}
			break;
		}
	case 1 :
		{
			for (int i=0; i<intTags->GetSize(); i++) {
				m_Tag.AddString(intTags->GetAt(i));
			}
			break;
		}
	case 2 :
		{
			for (int i=0; i<realTags->GetSize(); i++) {
				m_Tag.AddString(realTags->GetAt(i));
			}
			break;
		}
	case 3 :
		{
			for (int i=0; i<stringTags->GetSize(); i++) {
				m_Tag.AddString(stringTags->GetAt(i));
			}
			break;
		}
	case 4 :
		{
			for (int i=0; i<eventTags->GetSize(); i++) {
				m_Tag.AddString(eventTags->GetAt(i));
			}
			break;
		}
	}

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_TAG_COMBO);
	if(pCombo != NULL) {
		pCombo->SetFocus();
		return 0; //since we are explicity setting focus
	}		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}