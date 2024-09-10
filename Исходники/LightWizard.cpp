BOOL CLightWizard::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (!LoadList())
	{
		CDialog::OnCancel();
		return FALSE;
	}
	for ( int i = 0; i < m_aLights.GetSize(); i++ )
	{
		CLightObj * pLight = (CLightObj *) m_aLights.GetAt(i);
		m_LightList.InsertString(i,pLight->m_csName);
		m_LightList.SetItemData(i, (DWORD_PTR)pLight);
	}

	m_Light1.SetArtType(8);
	m_Light2.SetArtType(8);
	m_Light3.SetArtType(8);

	wFlags = F_BG_GRASS;
	m_Light1.SetDrawFlags(wFlags);
	m_Light2.SetDrawFlags(wFlags);
	m_Light3.SetDrawFlags(wFlags);

	m_cscLightLevel.SetRange(0, 30);
	m_cscLightLevel.SetPos(21);
	CString csValue;
	csValue.Format("%02ld", m_cscLightLevel.GetPos());
	m_csLightValue.SetWindowText(csValue);
	m_csbScrollLight.EnableWindow(false);
	m_LightList.SetCurSel(0);
	OnLightChange();

	CRect rectFrame, rectDlg;
	CWnd* pMainWnd = AfxGetMainWnd();
	if(pMainWnd != NULL)
	{
		pMainWnd->GetClientRect(rectFrame);
		pMainWnd->ClientToScreen(rectFrame);
		GetWindowRect(rectDlg);
		int nXPos = rectFrame.left + (rectFrame.Width() / 2) - (rectDlg.Width() / 2);
		int nYPos = rectFrame.top + (rectFrame.Height() / 2) - (rectDlg.Height() / 2);
		::SetWindowPos(m_hWnd, HWND_TOP, nXPos, nYPos, rectDlg.Width(), rectDlg.Height(), SWP_NOCOPYBITS);
	}
	return TRUE;

}