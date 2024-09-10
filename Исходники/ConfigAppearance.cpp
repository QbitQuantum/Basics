BOOL CConfigAppearance::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	const CSettings *pSettings = theApp.GetSettings();
	m_strFont = pSettings->Appearance.strFont;		// // //

	CDC *pDC = GetDC();
	if (pDC != NULL) {
		LOGFONTW LogFont = { };		// // //
		LogFont.lfCharSet = ANSI_CHARSET;
		EnumFontFamiliesExW(pDC->m_hDC, &LogFont, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)this, 0);
		ReleaseDC(pDC);
	}

	CComboBox *pFontSizeList = static_cast<CComboBox*>(GetDlgItem(IDC_FONT_SIZE));
	CComboBox *pItemsBox = static_cast<CComboBox*>(GetDlgItem(IDC_COL_ITEM));

	for (int i = 0; i < COLOR_ITEM_COUNT; ++i) {
		pItemsBox->AddString(conv::to_wide(COLOR_ITEMS[i]).data());
	}

	pItemsBox->SelectString(0, conv::to_wide(COLOR_ITEMS[0]).data());

	m_iSelectedItem = 0;

	m_iColors[COL_BACKGROUND]			= pSettings->Appearance.iColBackground;
	m_iColors[COL_BACKGROUND_HILITE]	= pSettings->Appearance.iColBackgroundHilite;
	m_iColors[COL_BACKGROUND_HILITE2]	= pSettings->Appearance.iColBackgroundHilite2;
	m_iColors[COL_PATTERN_TEXT]			= pSettings->Appearance.iColPatternText;
	m_iColors[COL_PATTERN_TEXT_HILITE]	= pSettings->Appearance.iColPatternTextHilite;
	m_iColors[COL_PATTERN_TEXT_HILITE2]	= pSettings->Appearance.iColPatternTextHilite2;
	m_iColors[COL_PATTERN_INSTRUMENT]	= pSettings->Appearance.iColPatternInstrument;
	m_iColors[COL_PATTERN_VOLUME]		= pSettings->Appearance.iColPatternVolume;
	m_iColors[COL_PATTERN_EFF_NUM]		= pSettings->Appearance.iColPatternEffect;
	m_iColors[COL_SELECTION]			= pSettings->Appearance.iColSelection;
	m_iColors[COL_CURSOR]				= pSettings->Appearance.iColCursor;
	m_iColors[COL_CURRENT_ROW_NORMAL]	= pSettings->Appearance.iColCurrentRowNormal;		// // //
	m_iColors[COL_CURRENT_ROW_EDIT]		= pSettings->Appearance.iColCurrentRowEdit;
	m_iColors[COL_CURRENT_ROW_PLAYING]	= pSettings->Appearance.iColCurrentRowPlaying;

	m_iFontSize	= pSettings->Appearance.iFontSize;		// // //

	m_bPatternColors = pSettings->Appearance.bPatternColor;		// // //
	m_bDisplayFlats = pSettings->Appearance.bDisplayFlats;		// // //

	pItemsBox = static_cast<CComboBox*>(GetDlgItem(IDC_SCHEME));

	for (auto *scheme : COLOR_SCHEMES)
		pItemsBox->AddString(scheme->NAME);

	for (int pt : FONT_SIZES)		// // //
		pFontSizeList->AddString(conv::to_wide(conv::from_int(pt)).data());
	pFontSizeList->SetWindowTextW(conv::to_wide(conv::from_int(m_iFontSize)).data());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}