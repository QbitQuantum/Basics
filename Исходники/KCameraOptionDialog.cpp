BOOL KCameraOptionDialog::OnInitDialog()
{
	char szText[128];
	if (!m_pPlayer)
		return FALSE;
	if (m_pPlayer->IsFreeCamera())
		m_nFreeCamera = 1;
	else 
		m_nFreeCamera = 0;

	m_nCameraType = s_CameraTypeConvertTable[m_pPlayer->GetCameraType()];
	UpdateData(FALSE);

	_itoa(m_pPlayer->GetBindID(), szText, 10);
	m_editBindID.SetWindowTextA(szText);
	float fAAA = (m_pPlayer->GetAngle() * 180) / M_PI;
	gcvt(fAAA,5,szText);
	m_editAngle.SetWindowTextA(szText);	
	return TRUE;
}