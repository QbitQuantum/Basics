INT_PTR CColorRuleDialog::OnInitDialog()
{
	if(m_bEdit)
	{
		SetDlgItemText(m_hDlg,IDC_EDIT_DESCRIPTION,m_pColorRule->strDescription.c_str());
		SetDlgItemText(m_hDlg,IDC_EDIT_FILENAMEPATTERN,m_pColorRule->strFilterPattern.c_str());

		m_cfCurrentColor = m_pColorRule->rgbColour;

		if(m_pColorRule->caseInsensitive)
			CheckDlgButton(m_hDlg,IDC_CHECK_CASE_INSENSITIVE,BST_CHECKED);

		if(m_pColorRule->dwFilterAttributes & FILE_ATTRIBUTE_COMPRESSED)
			CheckDlgButton(m_hDlg,IDC_CHECK_COMPRESSED,BST_CHECKED);

		if(m_pColorRule->dwFilterAttributes & FILE_ATTRIBUTE_ENCRYPTED)
			CheckDlgButton(m_hDlg,IDC_CHECK_ENCRYPTED,BST_CHECKED);

		if(m_pColorRule->dwFilterAttributes & FILE_ATTRIBUTE_ARCHIVE)
			CheckDlgButton(m_hDlg,IDC_CHECK_ARCHIVE,BST_CHECKED);

		if(m_pColorRule->dwFilterAttributes & FILE_ATTRIBUTE_HIDDEN)
			CheckDlgButton(m_hDlg,IDC_CHECK_HIDDEN,BST_CHECKED);

		if(m_pColorRule->dwFilterAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
			CheckDlgButton(m_hDlg,IDC_CHECK_INDEXED,BST_CHECKED);

		if(m_pColorRule->dwFilterAttributes & FILE_ATTRIBUTE_READONLY)
			CheckDlgButton(m_hDlg,IDC_CHECK_READONLY,BST_CHECKED);

		if(m_pColorRule->dwFilterAttributes & FILE_ATTRIBUTE_SYSTEM)
			CheckDlgButton(m_hDlg,IDC_CHECK_SYSTEM,BST_CHECKED);

		TCHAR szTemp[64];
		LoadString(GetInstance(),IDS_EDITCOLORRULE,
			szTemp,SIZEOF_ARRAY(szTemp));
		SetWindowText(m_hDlg,szTemp);
	}
	else
	{
		m_cfCurrentColor = m_pcrdps->m_cfInitialColor;
	}

	HWND hStaticColor = GetDlgItem(m_hDlg,IDC_STATIC_COLOR);
	SetWindowSubclass(hStaticColor,NColorRuleDialog::StaticColorProcStub,0,reinterpret_cast<DWORD_PTR>(this));

	SendMessage(GetDlgItem(m_hDlg,IDC_EDIT_DESCRIPTION),EM_SETSEL,0,-1);
	SetFocus(GetDlgItem(m_hDlg,IDC_EDIT_DESCRIPTION));

	m_pcrdps->RestoreDialogPosition(m_hDlg,false);

	return 0;
}