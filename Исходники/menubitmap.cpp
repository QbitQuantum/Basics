void
CNdasMenuBitmapHandler::
OnDrawStatusText(
	LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDCHandle dc = lpDrawItemStruct->hDC;
	CRect rect(&lpDrawItemStruct->rcItem);
	rect.bottom -= 2;

	COLORREF oldBkColor = dc.SetBkColor(RGB(255,255,225));

	CBrush brush = ::CreateSolidBrush(RGB(255,255,225));
	
	CPen pen = ::CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_3DDKSHADOW)); 

	HBRUSH hOldBrush = dc.SelectBrush(brush);
	HPEN hOldPen = dc.SelectPen(pen);

//	dc.Rectangle(rect);

	dc.RoundRect(rect,CPoint(rect.Height() /4, rect.Height() / 4));

	(void) dc.SelectPen(hOldPen);
	(void) dc.SelectBrush(hOldBrush);

	CRect rectText(rect);
	rectText.left += GetSystemMetrics(SM_CXMENUCHECK) + 2;

	CString strStatus;
	ATLVERIFY(strStatus.LoadString(static_cast<UINT>(lpDrawItemStruct->itemData)));

	CFontHandle curFont = dc.GetCurrentFont();
	LOGFONT logFont;
	curFont.GetLogFont(&logFont);
	logFont.lfWeight = FW_BOLD;
	CFont newFont = ::CreateFontIndirect(&logFont);
	CFontHandle oldFont = dc.SelectFont(newFont);

//	COLORREF oldTextColor = dc.SetTextColor(RGB(40,40,233));

	dc.DrawText(
		strStatus,
		strStatus.GetLength(),
		&rectText,
		DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_NOPREFIX | 
		DT_VCENTER);

	dc.SelectFont(oldFont);
//	dc.SetTextColor(oldTextColor);
	dc.SetBkColor(oldBkColor);
}