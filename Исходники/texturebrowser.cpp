//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
BOOL CTextureBrowser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cSizeList.SubclassDlgItem(IDC_TEXTURESIZE, this);
	m_cFilter.SubclassDlgItem(IDC_FILTER, this);
	m_cKeywords.SubclassDlgItem(IDC_KEYWORDS, this);
	m_cCurName.SubclassDlgItem(IDC_CURNAME, this);
	m_cCurDescription.SubclassDlgItem(IDC_CURDESCRIPTION, this);
	m_cUsed.SubclassDlgItem(IDC_USED, this);
   
	m_FilterOpaque.SubclassDlgItem(IDC_FILTER_OPAQUE, this);
	m_FilterTranslucent.SubclassDlgItem(IDC_FILTER_TRANSLUCENT, this);
	m_FilterSelfIllum.SubclassDlgItem(IDC_FILTER_SELFILLUM, this);
	m_FilterEnvMask.SubclassDlgItem(IDC_FILTER_ENVMASK, this);
	m_ShowErrors.SubclassDlgItem(IDC_SHOW_ERROR, this);

	m_FilterOpaque.SetCheck( true );
	m_FilterTranslucent.SetCheck( true );
	m_FilterSelfIllum.SetCheck( true );
	m_FilterEnvMask.SetCheck( true );
	m_ShowErrors.SetCheck( true );

	//
	// Create CTextureWindow that takes up area of dummy control.
	//
	RECT r;
	GetDlgItem(IDC_BROWSERDUMMY)->GetClientRect(&r);
	m_cTextureWindow.Create(this, r);

	// Show everything initially
	m_cTextureWindow.SetTypeFilter( ~0, true );

	//
	// Add latest history to the filter combo.
	//
	for (int i = 0; i < m_nFilterHistory; i++)
	{
		m_cFilter.AddString(m_FilterHistory[i]);
	}

	//
	// Set the name filter unless one was explicitly specified.
	//
	if (m_szNameFilter[0] == '\0')
	{
		//
		// No name filter specified. Use whatever is on top of the history.
		//
		if (m_cFilter.GetCount() > 0)
		{
			m_cFilter.GetLBText(0, m_szNameFilter);
			m_cFilter.SetCurSel(0);
		}
	}

	m_cFilter.SetWindowText(m_szNameFilter);
	m_cTextureWindow.SetNameFilter(m_szNameFilter);

	//
	// Done with the name filter; clear it for next time.
	//
	m_szNameFilter[0] = '\0';

	//
	// Add the global list of keywords to the keywords combo.
	//
	POSITION pos = g_Textures.KeywordsGetHeadPosition();
	while (pos != NULL)
	{
		char *pszKeyword = g_Textures.KeywordsGetNext(pos);
		m_cKeywords.AddString(pszKeyword);
	}

	//
	// Set the keyword filter.
	//
	m_cKeywords.SetWindowText(m_szLastKeywords);
	m_cTextureWindow.SetKeywords(m_szLastKeywords);

	m_cUsed.SetCheck(m_bUsed);

	CWinApp *pApp = AfxGetApp();
	CString str = pApp->GetProfileString(pszIniSection, "Position");
	if (!str.IsEmpty())
	{
		CRect r;
		sscanf(str, "%d %d %d %d", &r.left, &r.top, &r.right, &r.bottom);

		if (r.left < 0)
		{
			ShowWindow(SW_SHOWMAXIMIZED);
		}
		else
		{
			MoveWindow(r.left, r.top, r.right-r.left, r.bottom-r.top, FALSE);
		}
	}

	int iSize = pApp->GetProfileInt(pszIniSection, "ShowSize", 0);
	m_cSizeList.SetCurSel(iSize);
	OnSelendokTexturesize();

	if (szInitialTexture[0])
	{
		m_cTextureWindow.SelectTexture(szInitialTexture);
	}

	m_cTextureWindow.ShowWindow(SW_SHOW);

	SetTimer(1, 500, NULL);

	m_cFilter.SetFocus();

	return(FALSE);
}