BOOL CVoiceSetup::OnInitDialog(void)
{
	
	CDialog::OnInitDialog();
	
	HRESULT                             hr = S_OK;

	/*hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
	
	if(SUCCEEDED(hr)){

		hr = cpEnum->GetCount(&ulCount);

	}

	while(SUCCEEDED(hr) && ulCount -- ){
    
		cpVoiceToken.Release();
		if(SUCCEEDED(hr))
			hr = cpEnum->Next( 1, &cpVoiceToken, NULL );
		if(SUCCEEDED(hr))
	        hr = cpVoice->SetVoice(cpVoiceToken);
	    if(SUCCEEDED(hr))
			hr = cpVoice->Speak( L"How are you?", SPF_DEFAULT, NULL);

		m_cbMaleVoice.AddString(
	}  */


	hr = SpInitTokenComboBox(GetDlgItem(IDC_MALE_VOICE)->m_hWnd, SPCAT_VOICES);
	if(FAILED(hr)){

		AfxMessageBox("Error enumerating voices", MB_ICONSTOP);
	}

	hr = SpInitTokenComboBox(GetDlgItem(IDC_FEMALE_VOICE)->m_hWnd, SPCAT_VOICES);
	if(FAILED(hr)){

		AfxMessageBox("Error enumerating voices", MB_ICONSTOP);
	}


	CFileFind finder;

	BOOL bFound = finder.FindFile(g_sSettings.GetWorkingDir() + "\\gfx\\char_*.bmp");
	CString strChar, strTmp;
	while(finder.FindNextFile()){

		strChar = finder.GetFileTitle();
		strChar = strChar.Mid(5);
		m_cbMaleChar.AddString(strChar);
		m_cbFemChar.AddString(strChar);
	}


	CIni ini;
	ini.SetIniFileName(g_sSettings.GetIniFile());

	int nCnt = ini.GetValue("Voice", "MaleCount", 0);
	for(int i = 0; i < nCnt; i++){

		strTmp.Format("Male_%d", i);
		m_lbMales.AddString(ini.GetValue("Voice", strTmp, ""));
	}

	nCnt = ini.GetValue("Voice", "FemaleCount", 0);
	for(int i = 0; i < nCnt; i++){

		strTmp.Format("Female_%d", i);
		m_lbFemales.AddString(ini.GetValue("Voice", strTmp, ""));
	}



	return TRUE;
}