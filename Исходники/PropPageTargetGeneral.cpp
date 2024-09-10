BOOL CPropPageTargetGeneral::OnInitDialog() 
{
	CDialog::OnInitDialog();

    FillCombos();

    CheckCommChannels();

    // if properties dialog, disable name edit
    if(!m_bNewDlg)
    {
        CEdit*   pEdit = (CEdit*)GetDlgItem(IDC_PROPGEN_NAME);
        pEdit->EnableWindow(FALSE);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}