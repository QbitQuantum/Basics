BOOL CMorphAnimationTimePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// set step and description text
	m_stepStatic.SetWindowText(m_strStep);
	CString str;
	str.LoadString(m_nDescriptionID);
	m_descriptionStatic.SetWindowText(str);

	// set the time values
	TSTR strValue;

	strValue.printf(_T("%d"), m_startFrame);
	m_startFrameEdit.SetWindowText(strValue);

	strValue.printf(_T("%d"), m_endFrame);
	m_endFrameEdit.SetWindowText(strValue);

	strValue.printf(_T("%d"), m_displacement);
	m_displacementEdit.SetWindowText(strValue);

	strValue.printf(_T("%d"), m_fps);
	m_fpsEdit.SetWindowText(strValue);

	return TRUE;
}