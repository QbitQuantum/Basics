void CReflectSettingDlg::OnBnClickedOk()
{
	CString szTemp;
	m_edtStartAlpha.GetWindowTextW(szTemp);
	m_fStartAlpha = _wtof(szTemp);

	if(m_fStartAlpha < 0.0f || m_fStartAlpha > 1.0f)
	{
		MessageBox(_T("Starting transparency is lesser than 0.0 or greater than 1.0"), _T("Error"), MB_OK);
		return;
	}

	m_edtEndAlpha.GetWindowTextW(szTemp);
	m_fEndAlpha = _wtof(szTemp);

	if(m_fEndAlpha < 0.0f || m_fEndAlpha > 1.0f)
	{
		MessageBox(_T("Ending transparency is lesser than 0.0 or greater than 1.0"), _T("Error"), MB_OK);
		return;
	}

	m_edtShown.GetWindowTextW(szTemp);
	m_fShown = _wtof(szTemp);

	if(m_fShown < 0.0f || m_fShown > 1.0f)
	{
		MessageBox(_T("Image shown is lesser than 0.0 or greater than 1.0"), _T("Error"), MB_OK);
		return;
	}

	m_edtGap.GetWindowTextW(szTemp);
	m_nGap = _wtoi(szTemp);

	CDialog::OnOK();
}