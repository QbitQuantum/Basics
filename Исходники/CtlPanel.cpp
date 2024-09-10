//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
LRESULT CCtlPanel::OnDrawItem(UINT /*uMsg*/, WPARAM wParam,
							   LPARAM lParam, BOOL &bHandled)
{
	UINT idCtl = wParam;
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;

	if (idCtl == IDC_COLOR)
	{
		CAGDC dc(lpdis->hDC);
		HBRUSH hbr = (HBRUSH) GetStockObject(WHITE_BRUSH);
		FillRect(lpdis->hDC, &lpdis->rcItem, hbr);

		if ((int) lpdis->itemID != -1)
		{
			COLORREF clr = (COLORREF) ::SendMessage(lpdis->hwndItem,
			  CB_GETITEMDATA, lpdis->itemID, 0);

			RECT rect = lpdis->rcItem;
			InflateRect(&rect, -4, -2);
			hbr = CreateSolidBrush(clr | PALETTERGB_FLAG);
			FillRect(lpdis->hDC, &rect, hbr);
			DeleteObject(hbr);
			hbr = (HBRUSH) GetStockObject(BLACK_BRUSH);
			FrameRect(lpdis->hDC, &rect, hbr);
		}

		if (lpdis->itemState & ODS_FOCUS || lpdis->itemState & ODS_SELECTED)
		{
			hbr = (HBRUSH) GetStockObject(BLACK_BRUSH);
			FrameRect(lpdis->hDC, &lpdis->rcItem, hbr);
		}
	}
	else if (idCtl == IDC_FONT)
	{
		if ((int) lpdis->itemID != -1)
		{
			int nFont = ::SendMessage(lpdis->hwndItem, CB_GETITEMDATA, lpdis->itemID, 0);

			FONTARRAY &FontArray = GetFontArray();
			LOGFONT NewFont = FontArray[nFont].lf;
			NewFont.lfHeight = m_nFontHeight;
			NewFont.lfWidth = 0;
			if (NewFont.lfCharSet == SYMBOL_CHARSET)
			{
				lstrcpy(NewFont.lfFaceName, "Arial");
				NewFont.lfCharSet = ANSI_CHARSET;
				NewFont.lfPitchAndFamily = FF_SWISS;
			}

			SaveDC(lpdis->hDC);
			SetTextAlign(lpdis->hDC, TA_LEFT | TA_TOP | TA_NOUPDATECP);

			if (lpdis->itemState & ODS_SELECTED)
				SetTextColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
			else
				SetTextColor(lpdis->hDC, GetSysColor(COLOR_WINDOWTEXT));

			if (lpdis->itemState & ODS_SELECTED)
				SetBkColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHT));
			else
				SetBkColor(lpdis->hDC, GetSysColor(COLOR_WINDOW));

			HFONT hFont = CreateFontIndirect(&NewFont);
			HFONT hOldFont = (HFONT) SelectObject(lpdis->hDC, hFont);
			ExtTextOut(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top,
				ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem,
				FontArray[nFont].szFullName,
				lstrlen(FontArray[nFont].szFullName), NULL);
  
			if (lpdis->itemState & ODS_FOCUS)
				DrawFocusRect(lpdis->hDC, &lpdis->rcItem);

			SelectObject(lpdis->hDC, hOldFont);
			DeleteObject(hFont);
			RestoreDC(lpdis->hDC, -1);
		}
	}

	bHandled = TRUE;
	return (TRUE);
}