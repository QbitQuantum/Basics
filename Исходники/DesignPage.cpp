BOOL CDesignPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	CopyMemory( &m_stLogFont, &m_pcProfileDatas->m_stLogFont, sizeof( LOGFONT));
	m_clrNormalFore = m_pcProfileDatas->m_clrForeColor;
	m_clrNormalBack = m_pcProfileDatas->m_clrBackColor;
	m_nIconIndex	= m_pcProfileDatas->m_nIconIndex;
	m_clrFore		= m_clrNormalFore;
	m_clrBack		= m_clrNormalBack;

	m_clrBeforeFore	= m_pcProfileDatas->m_clrBeforeFore;
	m_clrBeforeBack	= m_pcProfileDatas->m_clrBeforeBack;
	m_clrAfterFore	= m_pcProfileDatas->m_clrAfterFore;
	m_clrAfterBack	= m_pcProfileDatas->m_clrAfterBack;

	m_nGenerationCount = m_pcProfileDatas->m_nGenerationCount;
	
	m_blAutoIMEOpen	= m_pcProfileDatas->m_blAutoIMEOpen;

	m_cStrSaveFilePath = m_pcProfileDatas->m_cStrSaveFilePath;

	CDC*	pcDC;
	pcDC = GetDC();
	if( pcDC)
	{
		m_cBrhBack.CreateSolidBrush( pcDC->GetNearestColor( m_clrBack));
		ReleaseDC( pcDC);
	}
	if( m_pcFntEdit)
	{
		delete m_pcFntEdit;
		m_pcFntEdit = NULL;
	}
	m_pcFntEdit = new CFont;
	m_pcFntEdit->CreateFontIndirect( &m_stLogFont);
	m_cEdtSample.SetFont( m_pcFntEdit);
	m_cEdtSample.SetMargins( 0, 0);

	m_nDesignTypeOld = m_nDesignType;

	m_cEdtSaveFilePath.EnableWindow( m_blSpecSet);
	m_cBtnSaveFileSel.EnableWindow( m_blSpecSet);

	m_cSpnGenerationCount.SetRange( 0, 10);

	m_cEdtGenerationCount.EnableWindow( m_blSpecSet);
	m_cSpnGenerationCount.EnableWindow( m_blSpecSet);

	CSetRegApp*	pcSetRegApp = ( CSetRegApp*)AfxGetApp();
	ASSERT( pcSetRegApp);
	const CIconImgList* pcIconImgs = pcSetRegApp->GetIconList();
	pcDC = m_cBtnIconSel.GetDC();
	if( pcDC)
	{
		CDC	cMemDC;
		if( cMemDC.CreateCompatibleDC( pcDC))
		{
			m_cBmpIcon.CreateCompatibleBitmap( &cMemDC, _ICON_WIDTH, _ICON_HEIGHT);
			cMemDC.SelectObject( &m_cBmpIcon);
			pcIconImgs->Draw( m_nIconIndex, cMemDC.GetSafeHdc(), CRect( 0, 0, _ICON_WIDTH, _ICON_HEIGHT));

			cMemDC.DeleteDC();

			m_cBtnIconSel.SetBitmap( m_cBmpIcon);
		}
		m_cBtnIconSel.ReleaseDC( pcDC);
	}

	UpdateData( FALSE);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}