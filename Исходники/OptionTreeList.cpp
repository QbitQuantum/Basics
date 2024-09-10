void COptionTreeList::OnPaint() 
{
	// Make sure valid
	if (m_otOption == NULL)
	{
		return;
	}
	
	// Declare variables
	CPaintDC dc(this);
	CDC* pDCMem = new CDC;
	CBitmap bpMem;
	CBitmap *bmOld;
	COptionTreeItem* otiItem;
	CRect rcClient;
	HGDIOBJ hOldBrush;
	long lTotal, lHeight;
	HRGN hRgn;

	// Get client rectangle
	GetClientRect(rcClient);

	// Clear visible list
	m_otOption->ClearVisibleList();

	// Clear all label rectangle
	m_otOption->ClearAllLabelRect();

	// Create DC
	pDCMem->CreateCompatibleDC(&dc);

	// Create bitmap
	bpMem.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());

	// Select bitmap
	bmOld = pDCMem->SelectObject(&bpMem);

	// Draw control background
	hOldBrush = pDCMem->SelectObject(GetSysColorBrush(COLOR_BTNFACE));
	pDCMem->PatBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), PATCOPY);

	// Draw control inside fill color
	rcClient.DeflateRect(2, 2);
	if (m_otOption->IsWindowEnabled() == TRUE)
	{
		pDCMem->SelectObject(GetSysColorBrush(COLOR_WINDOW));
	}
	else
	{
		pDCMem->SelectObject(GetSysColorBrush(COLOR_3DFACE));
	}
	pDCMem->PatBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), PATCOPY);
	rcClient.InflateRect(2, 2);

	// Draw expand column	
	if (m_otOption->GetShadeExpandColumn() == TRUE || m_otOption->IsWindowEnabled() == FALSE)
	{
		pDCMem->SelectObject(GetSysColorBrush(COLOR_BTNFACE));
	}
	else
	{
		pDCMem->SelectObject(GetSysColorBrush(COLOR_WINDOW));
	}
	pDCMem->PatBlt(0, 0, OT_EXPANDCOLUMN, rcClient.Height(), PATCOPY);

	// Create clip region
	hRgn = CreateRectRgn(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
	SelectClipRgn(pDCMem->m_hDC, hRgn);

	// Draw all items
	lTotal = 0;
	for (otiItem = m_otOption->GetRootItem()->GetChild(); otiItem != NULL; otiItem = otiItem->GetSibling())
	{
		lHeight = otiItem->DrawItem(pDCMem, rcClient, 0, lTotal);
		lTotal += lHeight;
	}

	// Remove clip region
	SelectClipRgn(pDCMem->GetSafeHdc(), NULL);
	DeleteObject(hRgn);

	// Draw vertical sep
	_DrawDarkVLine(pDCMem->GetSafeHdc(), OT_EXPANDCOLUMN, 0, rcClient.bottom);

	// Draw edge
	pDCMem->DrawEdge(&rcClient, BDR_SUNKENOUTER, BF_RECT);

	// Draw draw column
	if (m_bColDrag == TRUE)
	{
		_DrawXorBar(pDCMem->GetSafeHdc(), m_lColumn - OT_COLRNG / 2, 0, 4, rcClient.bottom);
	}

	// Copy back buffer to the display
	dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pDCMem, 0, 0, SRCCOPY);
	
	// Select old objects
	pDCMem->SelectObject(hOldBrush);
	pDCMem->SelectObject(bmOld);
	
	// Delete objects
	if (pDCMem->GetSafeHdc() != NULL)
	{
		pDCMem->DeleteDC();
	}
	delete pDCMem;
	if (bpMem.GetSafeHandle() != NULL)
	{
		bpMem.DeleteObject();
	}

}