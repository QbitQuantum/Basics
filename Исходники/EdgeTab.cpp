BOOL CEdgeTab::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton* pButton = (CButton*)GetDlgItem(IDC_NETWORK_EDGE_CHECK);
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_WEIGHT_EDIT);
	pButton->EnableWindow(m_bEmptyE);
	pCombo->EnableWindow(m_bEmptyE);
	pCombo->SetCurSel(m_lpControlStruct->edgeType);
	if (m_lpControlStruct->edgeType == None) {
		pEdit->EnableWindow(FALSE);
		pButton->EnableWindow(FALSE);	
	}
	else{
		pEdit->EnableWindow(TRUE);
		pEdit->SetWindowText(m_lpControlStruct->defaultWeightOfEdge);
	}
	GetDlgItem(IDC_CAPACITY_EDIT)->EnableWindow(pButton->GetCheck() == 1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}