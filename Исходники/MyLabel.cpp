void CMyLabel::OnPaint() {
	CPaintDC dc(this); // device context for painting

	DWORD dwFlags = DT_LEFT | DT_WORDBREAK;

	CRect rc;
	GetClientRect(rc);
	CString strText;
	GetWindowText(strText);
	CBitmap bmp;
	
	CDC* pDCMem;
	CBitmap*	pOldBitmap = NULL;

	pDCMem = new CDC;
	pDCMem->CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
	pOldBitmap = pDCMem->SelectObject(&bmp);
	
	UINT nMode = pDCMem->SetBkMode(TRANSPARENT);

	COLORREF crText;
	if (IsWindowEnabled()) {
		crText = pDCMem->SetTextColor(m_textColor);
	} else {
		crText = pDCMem->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	}

	CFont *pOldFont = pDCMem->SelectObject(&m_font);

	CBrush br;			
	br.Attach(m_brush);			
	pDCMem->FillRect(rc,&br);

	br.Detach();		

	pDCMem->DrawText(strText,rc,dwFlags);
		
	// Restore DC's State
	pDCMem->SetBkMode(nMode);
	pDCMem->SelectObject(pOldFont);
	pDCMem->SetTextColor(crText);
	
	dc.BitBlt(0,0,rc.Width(),rc.Height(),pDCMem,0,0,SRCCOPY);
	// continue DC restore 
	pDCMem->SelectObject ( pOldBitmap ) ;
	delete pDCMem;	
}