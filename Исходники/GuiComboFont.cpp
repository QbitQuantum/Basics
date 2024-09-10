void CGuiComboFont::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc = lpDrawItemStruct->rcItem;
	int nNumItem = lpDrawItemStruct->itemID;
	CBrush bf;	
	if (nNumItem == -1)
		return;
	rc.bottom -= 2;
	CString szFontName;
	GetLBText(nNumItem, szFontName);
	DWORD dwData = GetItemData(nNumItem);
	
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		bf.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		bf.CreateSolidBrush(pDC->GetBkColor());
	}
	
	pDC->SetBkMode(TRANSPARENT);
	pDC->FillRect(&rc, &bf);
	
	CFont font;
	if (!font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		szFontName))			   // lpszFacename		                 
		return;		
	
	CSize sz;
	HFONT hFont = NULL;
	hFont = (HFONT)pDC->SelectObject(font);
	sz    = pDC->GetTextExtent(szFontName);
	
	if (GetItemData(lpDrawItemStruct->itemID) & TRUETYPE_FONTTYPE)
	{
		m_imgArrow.Draw(pDC, 11, CPoint(rc.left + 2, rc.top + 1), ILD_TRANSPARENT);
	}

	pDC->TextOut(rc.left + 13, rc.top, szFontName);
	pDC->SelectObject(hFont);
}