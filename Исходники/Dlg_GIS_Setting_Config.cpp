void CDlg_GIS_Setting_Config::OnBnClickedCheckAutoGenerateFromToNodes3()
{

	UpdateData(1);

	if(m_bManageLanes == false)
	{
		m_bRFields = false;
		CEdit* pEditR = (CEdit*)GetDlgItem(IDC_ReservedFields);

		pEditR->ShowWindow (0);
				
		OnBnClickedCheckRFields();


	}

	CEdit* pEdit21 = (CEdit*)GetDlgItem(IDC_STATIC21);
	CEdit* pEdit22 = (CEdit*)GetDlgItem(IDC_STATIC22);
	CEdit* pEdit23 = (CEdit*)GetDlgItem(IDC_STATIC23);

	pEdit21->ShowWindow (m_bManageLanes);
	pEdit22->ShowWindow (m_bManageLanes);
	pEdit23->ShowWindow (m_bManageLanes);

	m_NumberOfLanes.ShowWindow (m_bManageLanes);
	m_Capacity.ShowWindow (m_bManageLanes);
	m_SpeedLimit.ShowWindow (m_bManageLanes);
	m_Capacity.ShowWindow (m_bManageLanes);
	m_LaneVSLinkCapacity.ShowWindow (m_bManageLanes);
	m_OneWayLanes.ShowWindow (m_bManageLanes);


}