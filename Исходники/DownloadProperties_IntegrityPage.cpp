BOOL CDownloadProperties_IntegrityPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	fsDownload_Properties dp;
	fsDownload_Properties *dp0 = m_pvDlds->at (0)->pMgr->GetDownloadMgr ()->GetDP ();

	if (DP_EQ (bCheckIntegrityWhenDone, FALSE))
		CheckDlgButton (IDC_PERFORMCHECKWHENDONE, dp0->bCheckIntegrityWhenDone ? BST_CHECKED : BST_UNCHECKED);
	else
		CheckDlgButton (IDC_PERFORMCHECKWHENDONE, BST_INDETERMINATE);

	m_wndICFR.AddString (LS (L_ASK));
	m_wndICFR.AddString (LS (L_RESTART));
	m_wndICFR.AddString (LS (L_DONOTHING));
	if (DP_EQ (enICFR, FALSE))
		m_wndICFR.SetCurSel (dp0->enICFR);

	LPCTSTR ppszAlgs [] = {
		_T("MD5"), _T("SHA-1"), _T("SHA-2 256"), _T("SHA-2 384"), _T("SHA-2 512"),
		_T("CRC 32")
	};

	DWORD adwAlgs [] = {
		HA_MD5, HA_SHA1, HA_SHA2, 
		MAKELONG (HA_SHA2, HSHA2S_384), MAKELONG (HA_SHA2, HSHA2S_512), 
		HA_CRC32,
	};

	DWORD dwAlg = (DWORD)-1;
	if (m_pvDlds->size () == 1)
		dwAlg = dp0->dwIntegrityCheckAlgorithm;

	for (int i = 0; i < sizeof (ppszAlgs) / sizeof (LPCSTR); i++)
	{
		m_wndAlgorithm.AddString (ppszAlgs [i]);
		m_wndAlgorithm.SetItemData (i, adwAlgs [i]);
		if (dwAlg == adwAlgs [i])
			m_wndAlgorithm.SetCurSel (i);
	}

	if (m_pvDlds->size () == 1)
	{
		SetDlgItemText (IDC_CHECKSUM, dp0->pszCheckSum);		
	}
	else
	{
		UINT anIds [] = {
			IDC__CHECKSUMOFTHISFILE, IDC_CHECKSUM, 
			IDC__ALGORITHM, IDC_ALGORITHM
		};

		for (int i = 0; i < sizeof (anIds) / sizeof (UINT); i++)
			GetDlgItem (anIds [i])->ShowWindow (SW_HIDE);
	}

	ApplyLanguage ();

	UpdateEnabled ();
	
	return TRUE;  
	              
}