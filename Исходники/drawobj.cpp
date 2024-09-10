void CDrawText::OnOpen(CDrawView* pView)
{
	ASSERT_VALID(this);

	// get rect in device coord.
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc,NULL);
	CRect rect(m_position);
	dc.LPtoDP(rect);
	rect.NormalizeRect();

	// create device font
	LOGFONT lf = m_lf;
	lf.lfHeight = MulDiv(lf.lfHeight,GetDeviceCaps(dc.m_hDC, LOGPIXELSY),100);  //====
  	lf.lfWidth = 0;
	pView->m_peditfont = new CFont;
	pView->m_peditfont->CreateFontIndirect(&lf);			  // create font
	pView->m_peditbrush = new CBrush;
	pView->m_peditbrush->CreateSolidBrush(m_pDocument->GetPaperColor());

	// create edit window to edit text
	CEdit *pEdit = new CEdit;
	pView->m_pedit=pEdit;
	pView->m_ptext=this;

	pEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|
		AlignTable[m_align].editstyle, rect, pView, 1);
	pEdit->SetFont(pView->m_peditfont);
	pEdit->SetWindowText(m_text);
	pEdit->SetFocus();
	m_pDocument->SetModifiedFlag();
	
	// load open-state accelerator 
	pView->ReplaceAccelTable(IDR_SEPEDTTYPE_CNTR_IP);
}