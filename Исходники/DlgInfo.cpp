void CDlgInfo::OnNMReleasedcaptureSliderGb(NMHDR *pNMHDR, LRESULT *pResult)
{
	int pos = m_GB.GetPos();
	float newVal = float(0.01f * pos);
	//0.5~0.95 only
	if(newVal < 0.5f)
	{
		newVal = 0.5f;
		m_GB.SetPos(newVal / 0.01f);
	}
	if(newVal > 0.95f)
	{
		newVal = 0.95f;
		m_GB.SetPos(newVal / 0.01f);
	}

	m_pView->SetGB(newVal);
	TCHAR tchBuffer[BUFFER]; 
	SetDlgItemText(IDC_STATIC_GB, _gcvt(newVal, 5, tchBuffer)); 
	*pResult = 0;
}