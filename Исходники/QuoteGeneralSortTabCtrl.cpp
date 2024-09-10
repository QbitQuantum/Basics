void QuoteTableCtrlGeneralSort::OnDraw(CDC* pDC)
{
	CHSGridCtrl::OnDraw(pDC);

	CRect rect, itemrect, rccvlient;
	GetClientRect(rccvlient);
	ClientToScreen(rccvlient);
	GetClientRect(rect);
	itemrect = rect;
	if (GetRowCount() <=0)
		return;

	int rowheight = GetRowHeight(0);
	itemrect.bottom = rowheight-1;
	
	COLORREF bkcolor = GetBkColor();
	COLORREF textcolor = RGB(155,155,155);
	if (m_iColorFontProt)
		textcolor = m_iColorFontProt->GetQuoteTabTextColor();
	CFont* pFont;
	CFont* pOldFont;
	BOOL bCreat = FALSE;
	if (m_iFont)
		pFont = (CFont*)m_iFont->GetQuoteColHeadFont();
	else
	{
		pFont = new CFont();
		VERIFY(pFont->CreateFont(16,0, 0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_SWISS, _T("宋体")));
		bCreat = TRUE;
	}

	pOldFont = pDC->SelectObject(pFont);

	
	pDC->SetBkColor( GetSysColor(COLOR_HIGHLIGHT) );
	pDC->SetBkColor(bkcolor);
	pDC->SetTextColor(textcolor);

	pDC->SetBkColor(bkcolor);
	pDC->DrawText(m_pTableFlag->strTitle, &itemrect, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);

	pDC->SelectObject(pOldFont);
	if (bCreat)
		pFont->DeleteObject();

	
	
	CPen hPen;
	hPen.CreatePen(PS_SOLID ,1,RGB(200,0,0));
	CPen* hOldPen = pDC->SelectObject(&hPen);

	pDC->MoveTo(CPoint(itemrect.left,itemrect.bottom));
	pDC->LineTo(CPoint(itemrect.right, itemrect.bottom));

	pDC->SelectObject(hOldPen);
	hPen.DeleteObject();

	
}