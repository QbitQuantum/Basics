void CToolTipCtrlX::CustomPaint(LPNMTTCUSTOMDRAW pNMCD)
{
	CWnd* pwnd = CWnd::FromHandle(pNMCD->nmcd.hdr.hwndFrom);
	CDC* pdc = CDC::FromHandle(pNMCD->nmcd.hdc);

	// Windows Vista (General)
	// -----------------------
	// *Need* to use (some aspects) of the 'TOOLTIP' theme to get typical Vista tooltips.
	//
	// Windows Vista *without* SP1
	// ---------------------------
	// The Vista 'TOOLTIP' theme offers a bold version of the standard tooltip font via 
	// the TTP_STANDARDTITLE part id. Furthermore TTP_STANDARDTITLE is the same font as
	// the standard tooltip font (TTP_STANDARD). So, the 'TOOLTIP' theme can get used
	// thoroughly.
	//
	// Windows Vista *with* SP1
	// ------------------------
	// The Vista SP1(!) 'TOOLTIP' theme does though *not* offer a bold font. Keep
	// in mind that TTP_STANDARDTITLE does not return a bold font. Keep also in mind
	// that TTP_STANDARDTITLE is even a *different* font than TTP_STANDARD!
	// Which means, that TTP_STANDARDTITLE should *not* be used within the same line
	// as TTP_STANDARD. It just looks weird. TTP_STANDARDTITLE could be used for a
	// single line (the title line), but it would though not give us a bold font.
	// So, actually we can use the Vista 'TOOLTIP' theme only for getting the proper
	// tooltip background.
	//
	// Windows XP
	// ----------
	// Can *not* use the 'TOOLTIP' theme at all because it would give us only a (non-bold)
	// black font on a white tooltip window background. Seems that the 'TOOLTIP' theme under 
	// WinXP is just using the default Window values (black+white) and does not
	// use any of the tooltip specific Window metrics...
	//
	bool bUseEmbeddedThemeFonts = false;
	HTHEME hTheme = NULL;
	if (theApp.IsVistaThemeActive()) {
		hTheme = OpenThemeData(*pwnd, L"TOOLTIP");
		// Using the theme's fonts works only under Vista without SP1. When SP1
		// is installed the fonts which are used for TTP_STANDARDTITLE and TTP_STANDARD
		// do no longer match (should not get displayed within the same text line).
		if (hTheme) bUseEmbeddedThemeFonts = true;
	}

	CString strText;
	pwnd->GetWindowText(strText);

	CRect rcWnd;
	pwnd->GetWindowRect(&rcWnd);

	CFont* pOldDCFont = NULL;
	if (hTheme == NULL || !bUseEmbeddedThemeFonts)
	{
		// If we have a theme, we try to query the correct fonts from it
		if (m_fontNormal.m_hObject == NULL && hTheme) {
			// Windows Vista Ultimate, 6.0.6001 SP1 Build 6001, English with German Language Pack
			// ----------------------------------------------------------------------------------
			// TTP_STANDARD, TTSS_NORMAL
			//  Height   -12
			//  Weight   400
			//  CharSet  1
			//  Quality  5
			//  FaceName "Segoe UI"
			//
			// TTP_STANDARDTITLE, TTSS_NORMAL
			//  Height   -12
			//  Weight   400
			//  CharSet  1
			//  Quality  5
			//  FaceName "Segoe UI Fett" (!!!) Note: "Fett" (that is German !?)
			//
			// That font name ("Segoe UI *Fett*") looks quite suspicious. I would not be surprised
			// if that eventually leads to a problem within the font mapper which may not be capable
			// of finding the (english) version of that font and thus falls back to the standard
			// system font. At least this would explain why the TTP_STANDARD and TTP_STANDARDTITLE
			// fonts are *different* on that particular Windows Vista system.
			LOGFONT lf = {0};
			if (GetThemeFont(hTheme, pdc->m_hDC, TTP_STANDARD, TTSS_NORMAL, TMT_FONT, &lf) == S_OK) {
				VERIFY( m_fontNormal.CreateFontIndirect(&lf) );

				if (m_bCol1Bold && m_fontBold.m_hObject == NULL) {
					memset(&lf, 0, sizeof(lf));
					if (GetThemeFont(hTheme, pdc->m_hDC, TTP_STANDARDTITLE, TTSS_NORMAL, TMT_FONT, &lf) == S_OK)
						VERIFY( m_fontBold.CreateFontIndirect(&lf) );
				}

				// Get the tooltip font color
				COLORREF crText;
				if (GetThemeColor(hTheme, TTP_STANDARD, TTSS_NORMAL, TMT_TEXTCOLOR, &crText) == S_OK)
					m_crTooltipTextColor = crText;
			}
		}

		// If needed, create the standard tooltip font which was queried from the system metrics
		if (m_fontNormal.m_hObject == NULL && m_lfNormal.lfHeight != 0)
			VERIFY( m_fontNormal.CreateFontIndirect(&m_lfNormal) );

		// Select the tooltip font
		if (m_fontNormal.m_hObject != NULL) {
			pOldDCFont = pdc->SelectObject(&m_fontNormal);

			// If needed, create the bold version of the tooltip font by deriving it from the standard font
			if (m_bCol1Bold && m_fontBold.m_hObject == NULL) {
				LOGFONT lf;
				m_fontNormal.GetLogFont(&lf);
				lf.lfWeight = FW_BOLD;
				VERIFY( m_fontBold.CreateFontIndirect(&lf) );
			}
		}

		// Set the font color (queried from system metrics or queried from theme)
		pdc->SetTextColor(m_crTooltipTextColor);
	}

	// Auto-format the text only if explicitly requested. Otherwise we would also format
	// single line tooltips for regular list items, and if those list items contain ':'
	// characters they would be shown partially in bold. For performance reasons, the
	// auto-format is to be requested by appending the TOOLTIP_AUTOFORMAT_SUFFIX_CH 
	// character. Appending, because we can remove that character efficiently without
	// re-allocating the entire string.
	bool bAutoFormatText = strText.GetLength() > 0 && strText[strText.GetLength() - 1] == TOOLTIP_AUTOFORMAT_SUFFIX_CH;
	if (bAutoFormatText)
		strText.Truncate(strText.GetLength() - 1); // truncate the TOOLTIP_AUTOFORMAT_SUFFIX_CH char by setting it to NUL
	bool bShowFileIcon = m_bShowFileIcon && bAutoFormatText;
	if (bShowFileIcon) {
		int iPosNL = strText.Find(_T('\n'));
		if (iPosNL > 0) {
			int iPosColon = strText.Find(_T(':'));
			if (iPosColon < iPosNL)
				bShowFileIcon = false; // 1st line does not contain a filename
		}
	}
	
	int iTextHeight = 0;
	int iMaxCol1Width = 0;
	int iMaxCol2Width = 0;
	int iMaxSingleLineWidth = 0;
	CSize sizText(0);
	int iPos = 0;
	int iCaptionHeight = 0;
	const int iCaptionEnd = bShowFileIcon ? max(strText.Find(_T("\n<br_head>\n")), 0) : 0; // special tooltip with file icon
	const int iLineHeightOff = 1;
	const int iIconMinYBorder = bShowFileIcon ? 3 : 0;
	const int iIconWidth = bShowFileIcon ? theApp.GetBigSytemIconSize().cx : 0;
	const int iIconHeight = bShowFileIcon ? theApp.GetBigSytemIconSize().cy : 0;
	const int iIconDrawingWidth = bShowFileIcon ? (iIconWidth + 9) : 0;
	while (iPos != -1)
	{
		CString strLine = GetNextString(strText, _T('\n'), iPos);
		int iColon = bAutoFormatText ? strLine.Find(_T(':')) : -1;
		if (iColon != -1) {
			CSize siz;
			if (hTheme && bUseEmbeddedThemeFonts) {
				CRect rcExtent;
				CRect rcBounding(0, 0, 32767, 32767);
				GetThemeTextExtent(hTheme, *pdc, m_bCol1Bold ? TTP_STANDARDTITLE : TTP_STANDARD, TTSS_NORMAL, strLine, iColon + 1, m_dwCol1DrawTextFlags, &rcBounding, &rcExtent);
				siz.cx = rcExtent.Width();
				siz.cy = rcExtent.Height();
			}
			else {
				CFont* pOldFont = m_bCol1Bold ? pdc->SelectObject(&m_fontBold) : NULL;
				siz = pdc->GetTextExtent(strLine, iColon + 1);
				if (pOldFont)
					pdc->SelectObject(pOldFont);
			}
			iMaxCol1Width = max<int>(iMaxCol1Width, siz.cx + ((bShowFileIcon && iPos <= iCaptionEnd + strLine.GetLength()) ? iIconDrawingWidth : 0));
			iTextHeight = siz.cy + iLineHeightOff; // update height with 'col1' string, because 'col2' string might be empty and therefore has no height
			if (iPos <= iCaptionEnd)
				iCaptionHeight += siz.cy + iLineHeightOff;
			else
				sizText.cy += siz.cy + iLineHeightOff;

			LPCTSTR pszCol2 = (LPCTSTR)strLine + iColon + 1;
			while (_istspace((_TUCHAR)*pszCol2))
				pszCol2++;
			if (*pszCol2 != _T('\0')) {
				if (hTheme && bUseEmbeddedThemeFonts) {
					CRect rcExtent;
					CRect rcBounding(0, 0, 32767, 32767);
					GetThemeTextExtent(hTheme, *pdc, TTP_STANDARD, TTSS_NORMAL, pszCol2, ((LPCTSTR)strLine + strLine.GetLength()) - pszCol2, m_dwCol2DrawTextFlags, &rcBounding, &rcExtent);
					siz.cx = rcExtent.Width();
					siz.cy = rcExtent.Height();
				}
				else {
					siz = pdc->GetTextExtent(pszCol2, ((LPCTSTR)strLine + strLine.GetLength()) - pszCol2);
				}
				iMaxCol2Width = max<int>(iMaxCol2Width, siz.cx);
			}
		}
		else if (bShowFileIcon && iPos <= iCaptionEnd && iPos == strLine.GetLength() + 1){
			// file name, printed bold on top without any tabbing or desc
			CSize siz;
			if (hTheme && bUseEmbeddedThemeFonts) {
				CRect rcExtent;
				CRect rcBounding(0, 0, 32767, 32767);
				GetThemeTextExtent(hTheme, *pdc, m_bCol1Bold ? TTP_STANDARDTITLE : TTP_STANDARD, TTSS_NORMAL, strLine, strLine.GetLength(), m_dwCol1DrawTextFlags, &rcBounding, &rcExtent);
				siz.cx = rcExtent.Width();
				siz.cy = rcExtent.Height();
			}
			else {
				CFont* pOldFont = m_bCol1Bold ? pdc->SelectObject(&m_fontBold) : NULL;
				siz = pdc->GetTextExtent(strLine);
				if (pOldFont)
					pdc->SelectObject(pOldFont);
			}
			iMaxSingleLineWidth = max<int>(iMaxSingleLineWidth, siz.cx + iIconDrawingWidth);
			iCaptionHeight += siz.cy + iLineHeightOff;
		}
		else if (!strLine.IsEmpty() && strLine.Compare(_T("<br>")) != 0 && strLine.Compare(_T("<br_head>")) != 0) {
			CSize siz;
			if (hTheme && bUseEmbeddedThemeFonts) {
				CRect rcExtent;
				CRect rcBounding(0, 0, 32767, 32767);
				GetThemeTextExtent(hTheme, *pdc, TTP_STANDARD, TTSS_NORMAL, strLine, strLine.GetLength(), m_dwCol2DrawTextFlags, &rcBounding, &rcExtent);
				siz.cx = rcExtent.Width();
				siz.cy = rcExtent.Height();
			}
			else {
				siz = pdc->GetTextExtent(strLine);
			}
			iMaxSingleLineWidth = max<int>(iMaxSingleLineWidth, siz.cx + ((bShowFileIcon && iPos <= iCaptionEnd) ? iIconDrawingWidth : 0));
			if (bShowFileIcon && iPos <= iCaptionEnd + strLine.GetLength())
				iCaptionHeight += siz.cy + iLineHeightOff;
			else
				sizText.cy += siz.cy + iLineHeightOff;
		}
		else{
			CSize siz;
			if (hTheme && bUseEmbeddedThemeFonts) {
				CRect rcExtent;
				CRect rcBounding(0, 0, 32767, 32767);
				GetThemeTextExtent(hTheme, *pdc, TTP_STANDARD, TTSS_NORMAL, _T(" "), 1, m_dwCol2DrawTextFlags, &rcBounding, &rcExtent);
				siz.cx = rcExtent.Width();
				siz.cy = rcExtent.Height();
			}
			else {
				// TODO: Would need to use 'GetTabbedTextExtent' here, but do we actually use 'tabbed' text here at all ??
				siz = pdc->GetTextExtent(_T(" "), 1);
			}
			sizText.cy += siz.cy + iLineHeightOff;
		}
	}
	if (bShowFileIcon && iCaptionEnd > 0)
		iCaptionHeight = max<int>(iCaptionHeight, theApp.GetBigSytemIconSize().cy + (2*iIconMinYBorder));
	sizText.cy += iCaptionHeight;
	if (hTheme && theApp.m_ullComCtrlVer >= MAKEDLLVERULL(6,16,0,0))
		sizText.cy += 2; // extra bottom margin for Vista/Theme

	iMaxCol1Width = min(m_iScreenWidth4, iMaxCol1Width);
	iMaxCol2Width = min(m_iScreenWidth4*2, iMaxCol2Width);

	const int iMiddleMargin = 6;
	iMaxSingleLineWidth = max(iMaxSingleLineWidth, iMaxCol1Width + iMiddleMargin + iMaxCol2Width);
	if (iMaxSingleLineWidth > m_iScreenWidth4*3)
		iMaxSingleLineWidth = m_iScreenWidth4*3;
	sizText.cx = iMaxSingleLineWidth;

	if (pNMCD->uDrawFlags & DT_CALCRECT)
	{
		pNMCD->nmcd.rc.left = rcWnd.left;
		pNMCD->nmcd.rc.top = rcWnd.top;
		pNMCD->nmcd.rc.right = rcWnd.left + sizText.cx;
		pNMCD->nmcd.rc.bottom = rcWnd.top + sizText.cy;
	}
	else
	{
		pwnd->ScreenToClient(&rcWnd);

		int iOldBkColor = -1;
		if (hTheme) {
			int iPartId = TTP_STANDARD;
			int iStateId = TTSS_NORMAL;
			if (IsThemeBackgroundPartiallyTransparent(hTheme, iPartId, iStateId))
				DrawThemeParentBackground(m_hWnd, pdc->m_hDC, &rcWnd);
			DrawThemeBackground(hTheme, pdc->m_hDC, iPartId, iStateId, &rcWnd, NULL);
		}
		else {
			::FillRect(*pdc, &rcWnd, GetSysColorBrush(COLOR_INFOBK));
			iOldBkColor = pdc->SetBkColor(m_crTooltipBkColor);
			// Vista: Need to draw the window border explicitly !?
			if (theApp.m_ullComCtrlVer >= MAKEDLLVERULL(6,16,0,0)) {
				CPen pen;
				pen.CreatePen(0, 1, m_crTooltipTextColor);
				CPen *pOP = pdc->SelectObject(&pen);
				pdc->MoveTo(rcWnd.left, rcWnd.top);
				pdc->LineTo(rcWnd.right - 1, rcWnd.top);
				pdc->LineTo(rcWnd.right - 1, rcWnd.bottom - 1);
				pdc->LineTo(rcWnd.left, rcWnd.bottom - 1);
				pdc->LineTo(rcWnd.left, rcWnd.top);
				pdc->SelectObject(pOP);
				pen.DeleteObject();
			}
		}

		int iOldBkMode = 0;
		if ((hTheme && !bUseEmbeddedThemeFonts) || (hTheme == NULL && iOldBkColor != -1))
			iOldBkMode = pdc->SetBkMode(TRANSPARENT);

		CPoint ptText(pNMCD->nmcd.rc.left, pNMCD->nmcd.rc.top);
		iPos = 0;
		while (iPos != -1)
		{
			CString strLine = GetNextString(strText, _T('\n'), iPos);
			int iColon = bAutoFormatText ? strLine.Find(_T(':')) : -1;
			CRect rcDT;
			if (!bShowFileIcon || (unsigned)iPos > (unsigned)iCaptionEnd + strLine.GetLength())
				rcDT.SetRect(ptText.x, ptText.y, ptText.x + iMaxCol1Width, ptText.y + iTextHeight);
			else
				rcDT.SetRect(ptText.x + iIconDrawingWidth, ptText.y, ptText.x + iMaxCol1Width, ptText.y + iTextHeight);
			if (iColon != -1) {
				// don't draw empty <col1> strings (they are still handy to use for skipping the <col1> space)
				if (iColon > 0) {
					if (hTheme && bUseEmbeddedThemeFonts)
						DrawThemeText(hTheme, pdc->m_hDC, m_bCol1Bold ? TTP_STANDARDTITLE : TTP_STANDARD, TTSS_NORMAL, strLine, iColon + 1, m_dwCol1DrawTextFlags, 0, &rcDT);
					else {
						CFont* pOldFont = m_bCol1Bold ? pdc->SelectObject(&m_fontBold) : NULL;
						pdc->DrawText(strLine, iColon + 1, &rcDT, m_dwCol1DrawTextFlags);
						if (pOldFont)
							pdc->SelectObject(pOldFont);
					}
				}

				LPCTSTR pszCol2 = (LPCTSTR)strLine + iColon + 1;
				while (_istspace((_TUCHAR)*pszCol2))
					pszCol2++;
				if (*pszCol2 != _T('\0')) {
					rcDT.left = ptText.x + iMaxCol1Width + iMiddleMargin;
					rcDT.right = rcDT.left + iMaxCol2Width;
					if (hTheme && bUseEmbeddedThemeFonts)
						DrawThemeText(hTheme, pdc->m_hDC, TTP_STANDARD, TTSS_NORMAL, pszCol2, ((LPCTSTR)strLine + strLine.GetLength()) - pszCol2, m_dwCol2DrawTextFlags, 0, &rcDT);
					else
						pdc->DrawText(pszCol2, ((LPCTSTR)strLine + strLine.GetLength()) - pszCol2, &rcDT, m_dwCol2DrawTextFlags);
				}

				ptText.y += iTextHeight;
			}
			else if (bShowFileIcon && iPos <= iCaptionEnd && iPos == strLine.GetLength() + 1){
				// first line on special fileicon tab - draw icon and bold filename
				if (hTheme && bUseEmbeddedThemeFonts)
					DrawThemeText(hTheme, pdc->m_hDC, m_bCol1Bold ? TTP_STANDARDTITLE : TTP_STANDARD, TTSS_NORMAL, strLine, strLine.GetLength(), m_dwCol1DrawTextFlags, 0, &CRect(ptText.x  + iIconDrawingWidth, ptText.y, ptText.x + iMaxSingleLineWidth, ptText.y + iTextHeight));
				else {
					CFont* pOldFont = m_bCol1Bold ? pdc->SelectObject(&m_fontBold) : NULL;
					pdc->DrawText(strLine, CRect(ptText.x  + iIconDrawingWidth, ptText.y, ptText.x + iMaxSingleLineWidth, ptText.y + iTextHeight), m_dwCol1DrawTextFlags);
					if (pOldFont)
						pdc->SelectObject(pOldFont);
				}

				ptText.y += iTextHeight;
				int iImage = (int) theApp.GetFileTypeSystemImageIdx(strLine, -1, true);
				if (theApp.GetBigSystemImageList() != NULL) {
					int iPosY = rcDT.top;
					if (iCaptionHeight > iIconHeight)
						iPosY += (iCaptionHeight - iIconHeight) / 2;
					::ImageList_Draw(theApp.GetBigSystemImageList(), iImage, pdc->GetSafeHdc(), ptText.x, iPosY, ILD_TRANSPARENT);
				}
			}
			else {
				bool bIsBrHeadLine = false;
				if (bAutoFormatText && (strLine.Compare(_T("<br>")) == 0 || (bIsBrHeadLine = strLine.Compare(_T("<br_head>")) == 0) == true)){
					CPen pen;
					pen.CreatePen(0, 1, m_crTooltipTextColor);
					CPen *pOP = pdc->SelectObject(&pen);
					if (bIsBrHeadLine)
						ptText.y = iCaptionHeight;
					pdc->MoveTo(ptText.x, ptText.y + ((iTextHeight - 2) / 2)); 
					pdc->LineTo(ptText.x + iMaxSingleLineWidth, ptText.y + ((iTextHeight - 2) / 2));
					ptText.y += iTextHeight;
					pdc->SelectObject(pOP);
					pen.DeleteObject();
				}
				else{
					if (hTheme && bUseEmbeddedThemeFonts) {
						CRect rcLine(ptText.x, ptText.y, 32767, 32767);
						DrawThemeText(hTheme, pdc->m_hDC, TTP_STANDARD, TTSS_NORMAL, strLine, strLine.GetLength(), DT_EXPANDTABS | m_dwCol2DrawTextFlags, 0, &rcLine);
						ptText.y += iTextHeight;
					}
					else {
						// Text is written in the currently selected font. If 'nTabPositions' is 0 and 'lpnTabStopPositions' is NULL,
						// tabs are expanded to eight times the average character width.
						CSize siz;
						if (strLine.IsEmpty()) // Win98: To draw an empty line we need to output at least a space.
							siz = pdc->TabbedTextOut(ptText.x, ptText.y, _T(" "), 1, NULL, 0);
						else
							siz = pdc->TabbedTextOut(ptText.x, ptText.y, strLine, strLine.GetLength(), NULL, 0);
						ptText.y += siz.cy + iLineHeightOff;
					}
				}
			}
		}
		if (iOldBkColor != -1)
			pdc->SetBkColor(iOldBkColor);
		if (hTheme && !bUseEmbeddedThemeFonts)
			pdc->SetBkMode(iOldBkMode);
	}
	if (pOldDCFont)
		pdc->SelectObject(pOldDCFont);
	if (hTheme)
		CloseThemeData(hTheme);
}