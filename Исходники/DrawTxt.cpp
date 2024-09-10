HRESULT CDrawTxt::DoDraw(HDC hdcDest)
{
	USES_CONVERSION;

	// 如果字体宽度小于1，无法绘制
	if (m_dFontWidth > 0 && ROUND(m_dFontWidth) == 0)
		return S_OK;

	//设置背景模式
	int iBkMode = m_bsBackStyle == BackStyleTransparent ? TRANSPARENT : OPAQUE;
	int iOldBkMode = SetBkMode(hdcDest, iBkMode);
//	UINT uOldTextAlignMode = SetTextAlign(hdcDest, m_nTextAlign);
	COLORREF colFore;
	OleTranslateColor(m_clrForeColor, NULL, &colFore);
	COLORREF colOldTextColor = SetTextColor(hdcDest, colFore);

	COLORREF colBack;
	OleTranslateColor(m_clrBackColor, NULL, &colBack);
	COLORREF clrOldBackColor = SetBkColor(hdcDest, colBack);

	HFONT hFont = CreateTextFont(ROUND(m_dFontHeight), ROUND(m_dFontWidth));
	HFONT hOldFont = (HFONT)SelectObject(hdcDest, hFont);

	LPTSTR szCaption = W2T(m_bstrCaption);
	int cbCaption = lstrlen(szCaption);
	RECT rcCaption;
	RECTFToRECT(&m_rcPosition, &rcCaption);
	UINT uFormat = DT_NOPREFIX/* | DT_EXTERNALLEADING*/;
	// 考虑到斜体时可能文本超过外围矩形
	if (m_bAutoSize)
		uFormat |= DT_NOCLIP;
	else if (m_bWordWrap)
		uFormat |= DT_WORDBREAK;
	if (m_nTextAlign == TextAlignCenter)
		uFormat |= DT_CENTER;
	else if (m_nTextAlign == TextAlignRight)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;
	DrawText(hdcDest, szCaption, cbCaption, &rcCaption, uFormat);

	SelectObject(hdcDest, hOldFont);
	DeleteObject(hFont);

	SetBkMode(hdcDest, iOldBkMode);
//	SetTextAlign(hdcDest, uOldTextAlignMode);
	SetTextColor(hdcDest, colOldTextColor);
	SetBkColor(hdcDest, clrOldBackColor);

	return S_OK;

}