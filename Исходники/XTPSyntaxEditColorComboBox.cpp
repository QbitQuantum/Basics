void CXTPSyntaxEditColorComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC*  pDC       = CDC::FromHandle(lpDIS->hDC);
	UINT  itemState = lpDIS->itemState;
	UINT  itemID    = lpDIS->itemID;
	CRect rcItem    = lpDIS->rcItem;

	if (itemID == (UINT)-1)
	{
		return;
	}

	BOOL bDisabled = ((itemState & ODS_DISABLED) == ODS_DISABLED);
	BOOL bSelected = ((itemState & ODS_SELECTED) == ODS_SELECTED);
	BOOL bFocus    = ((itemState & ODS_FOCUS)    == ODS_FOCUS);

	// draw background.
	if (bDisabled)
	{
		pDC->SetTextColor(GetXtremeColor(COLOR_GRAYTEXT));
		pDC->SetBkColor(GetXtremeColor(COLOR_3DFACE));
		pDC->FillSolidRect(&rcItem, GetXtremeColor(COLOR_3DFACE));
	}
	else
	{
		if (bSelected)
		{
			pDC->SetTextColor(GetXtremeColor(COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor(GetXtremeColor(COLOR_WINDOW));
			pDC->FillSolidRect(&rcItem, GetXtremeColor(COLOR_HIGHLIGHT));
		}
		else
		{
			pDC->SetTextColor(GetXtremeColor(COLOR_WINDOWTEXT));
			pDC->SetBkColor(GetXtremeColor(COLOR_WINDOW));
			pDC->FillSolidRect(&rcItem, GetXtremeColor(COLOR_WINDOW));
		}

		// draw focus rectangle.
		if (bFocus)
		{
			pDC->DrawFocusRect(&rcItem);
		}
	}

	// determine the size of the color rectangle.
	CRect rColor(rcItem);
	rColor.DeflateRect(2,2);
	rColor.right = rColor.left + COLOR_ITEM_WIDTH;
	rColor.bottom = rColor.top + COLOR_ITEM_WIDTH;

	// draw color rectangle.
	pDC->FillSolidRect(rColor,
		bDisabled? GetXtremeColor(COLOR_3DFACE): (COLORREF)lpDIS->itemData);

	pDC->Draw3dRect(rColor,
		GetXtremeColor(bDisabled? COLOR_GRAYTEXT: COLOR_WINDOWTEXT),
		GetXtremeColor(bDisabled? COLOR_GRAYTEXT: COLOR_WINDOWTEXT));

	// determine the size of the text display.
	CRect rText(rColor);
	rText.top -= 2;
	rText.bottom = rText.top + (::GetSystemMetrics(SM_CYVTHUMB)-::GetSystemMetrics(SM_CYEDGE));
	rText.left = rText.right + 4;
	rText.right = rcItem.right;

	// draw text.
	CString csItemText;
	GetLBText(itemID, csItemText);
	if (!csItemText.IsEmpty())
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(csItemText, rText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
}