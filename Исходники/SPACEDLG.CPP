BOOL CCharacterSpacingDialog::OnInitDialog() 
{
	// Do default OnInitDialog.
	CPmwDialog::OnInitDialog();

	// Get the rect for our preview window.
	CWnd* pPreview = GetDlgItem(IDC_PREVIEW);
	if (pPreview != NULL)
	{
		pPreview->GetWindowRect(&m_crFullPreview);
		pPreview->ScreenToClient(&m_crFullPreview);

		m_crPreview = m_crFullPreview;
		m_crPreview.left++;
		m_crPreview.top++;
		m_crPreview.right--;
		m_crPreview.bottom--;
	}

	// Limit our text.
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_SPACING);
	if (pEdit != NULL)
	{
		pEdit->LimitText(7);
	}

	// Show the spacing in the edit.
	SetSpacing(m_lOriginalSpacing);

	// Check the radio button that corresponds to this spacing.
	UINT uID = IDC_CUSTOM;
	for (int i = 0; i < nStandardSpacings; i++)
	{
		if (StandardSpacing[i].m_lSpacing == m_lOriginalSpacing)
		{
			uID = StandardSpacing[i].m_uID;
			break;
		}
	}
	CheckDlgButton(uID, TRUE);

	return TRUE;
}