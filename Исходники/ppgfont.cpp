void CFontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT( lpDIS->CtlType == ODT_COMBOBOX );

	// make sure this is a *real* item
	if (lpDIS->itemID == -1)
		return;

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	FONTITEM_PPG* pFI = (FONTITEM_PPG*)lpDIS->itemData;    // pointer to a FONTITEM storied in item data
	LOGFONT* pLF = &pFI->lf;
	COLORREF crBk, crText;
	TEXTMETRIC tm;
	int x, y;

	// Calculate the colors to use
	crBk = pDC->SetBkColor(
		GetSysColor(lpDIS->itemState & ODS_SELECTED ? COLOR_HIGHLIGHT : COLOR_WINDOW) );
	crText = pDC->SetTextColor(
		GetSysColor(lpDIS->itemState & ODS_SELECTED ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT) );

	// Calculate the position of the text
	pDC->GetTextMetrics( &tm );
	x = LOWORD(GetDialogBaseUnits()) / 4;
	y = (lpDIS->rcItem.bottom + lpDIS->rcItem.top - tm.tmHeight) / 2;

	// Draw the text
	pDC->ExtTextOut(lpDIS->rcItem.left + DX_BITMAP + 2 * x, y, ETO_CLIPPED | ETO_OPAQUE,
		&lpDIS->rcItem,(LPCTSTR) pLF->lfFaceName,
		lstrlen((LPCTSTR) pLF->lfFaceName), NULL );

	// Put the colors back as they were
	pDC->SetTextColor( crText );
	pDC->SetBkColor( crBk );

	// Draw the TrueType bitmap
	if (pFI->dwFontType & TRUETYPE_FONTTYPE)
	{
		int dy;
		dy = ((lpDIS->rcItem.bottom - lpDIS->rcItem.top) - DY_BITMAP) / 2;
		_AfxDrawMaskedBitmap(pDC, &m_bmpTrueType, &m_bmpMask,
			x, lpDIS->rcItem.top + dy, DX_BITMAP, DY_BITMAP);
	}

	// Draw the focus rect if needed
	if (lpDIS->itemState & ODS_FOCUS)
		pDC->DrawFocusRect( &lpDIS->rcItem );
}