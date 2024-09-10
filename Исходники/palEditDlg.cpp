BOOL
palEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   InitCommonProps();	

	switch(m_lightingType) {
	case TS::Material::ShadingSmooth:
		m_lightingSmooth.SetCheck(1);
		break;

	case TS::Material::ShadingFlat:
		m_lightingFlat.SetCheck(1);
		break;

	case TS::Material::ShadingNone:
		m_lightingUnlit.SetCheck(1);
		break;
	}

	

	
	// Set up the selection box...
	//
	RECT listRect;
	int  nHeight, nWidth;

	m_palListBox.GetClientRect(&listRect);
	nHeight = listRect.bottom / 16;
	nWidth  = listRect.right / 16;

	m_palListBox.SetItemHeight(0, nHeight);
	m_palListBox.SetColumnWidth(nWidth);
		
	//get the system palette
	PALETTEENTRY pal[256];
	CWnd* pWnd = GetDlgItem( ID_PAL_LIST );
	CDC* pListDC = pWnd->GetDC();
	int err = GetSystemPaletteEntries( pListDC->GetSafeHdc(), 0, 256, pal );
	AssertFatal(err == 256, "Error retreiving palette!");

	for (int i = 0; i < 256; i++) {
		m_palListBox.AddString((LPCTSTR)i);
	}

	if (m_selectedColor >= 0 && m_selectedColor <= 255) {
		m_palListBox.SetCurSel(m_selectedColor);
	} else {
		m_palListBox.SetCurSel(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}