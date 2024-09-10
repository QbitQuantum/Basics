void CTDLFindResultsListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// we only need handle header items
	int nItem = lpDrawItemStruct->itemID;
	FTDRESULT* pRes = GetResult(nItem);

	if (pRes)
	{
		CEnListCtrl::DrawItem(lpDrawItemStruct);
		return;
	}

	// else
	CString sText = GetItemText(nItem, 0);

	if (!sText.IsEmpty())
	{
		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

		CRect rLabel, rItem;
		GetItemRect(nItem, rLabel, LVIR_LABEL);
		GetItemRect(nItem, rItem, LVIR_BOUNDS);

		rLabel.left -= 2;

		int nSave = pDC->SaveDC();

		pDC->SelectObject(&m_fontBold);
		pDC->SetTextColor(0);
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		pDC->SetBkMode(OPAQUE);
		pDC->DrawText(sText, rLabel, DT_TOP | DT_LEFT | DT_END_ELLIPSIS | DT_NOPREFIX);

		// draw a horizontal dividing line
		pDC->DrawText(sText, rLabel, DT_TOP | DT_LEFT | DT_END_ELLIPSIS | DT_NOPREFIX | DT_CALCRECT);
		pDC->FillSolidRect(rLabel.right + 6, rLabel.top + rLabel.Height() / 2, rItem.right - rLabel.right, 1,
			GetSysColor(COLOR_3DSHADOW));

		pDC->RestoreDC(nSave);
	}
}