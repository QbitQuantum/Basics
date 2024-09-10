BOOL CBoneAssignmentPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// set step and description text
	m_stepStatic.SetWindowText(m_strStep);
	CString str;
	str.LoadString(m_nDescriptionID);
	m_descriptionStatic.SetWindowText(str);

	// set the time values
	TSTR strValue;

	strValue.printf(_T("%d"), m_maxBoneCount);
	m_maxBoneCountEdit.SetWindowText(strValue);

	strValue.printf(_T("%f"), m_weightThreshold);
	m_weightThresholdEdit.SetWindowText(strValue);

	return TRUE;
}