void CPropTreeList::OnPaint() 
{
	CPaintDC dc(this);
	CDC memdc;
	CBitmap* pOldBitmap;

	ASSERT(m_pProp!=NULL);

	m_pProp->ClearVisibleList();

	memdc.CreateCompatibleDC(&dc);
	pOldBitmap = memdc.SelectObject(&m_BackBuffer);

	CRect rc;
	GetClientRect(rc);

	// draw control background
	memdc.SelectObject(GetSysColorBrush(COLOR_BTNFACE));
	memdc.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

	// draw control inside fill color
	rc.DeflateRect(2,2);
	memdc.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), m_pProp->IsWindowEnabled() ? WHITENESS : PATCOPY);
	rc.InflateRect(2,2);

	// draw expand column
	memdc.SelectObject(GetSysColorBrush(COLOR_BTNFACE));
	memdc.PatBlt(0, 0, PROPTREEITEM_EXPANDCOLUMN, rc.Height(), PATCOPY);

	// draw edge
	memdc.DrawEdge(&rc, BDR_SUNKENOUTER, BF_RECT);

	CPropTreeItem* pItem;
	LONG nTotal = 0;

	ASSERT(m_pProp->GetRootItem()!=NULL);

	rc.DeflateRect(2,2);

	// create clip region
	HRGN hRgn = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	SelectClipRgn(memdc.m_hDC, hRgn);

	// draw all items
	for (pItem = m_pProp->GetRootItem()->GetChild(); pItem; pItem = pItem->GetSibling())
	{
		LONG nHeight = pItem->DrawItem(&memdc, rc, 0, nTotal);
		nTotal += nHeight;
	}

	// remove clip region
	SelectClipRgn(memdc.m_hDC, NULL);
	DeleteObject(hRgn);

	// copy back buffer to the display
	dc.GetClipBox(&rc);
	dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memdc, rc.left, rc.top, SRCCOPY);
	memdc.DeleteDC();
}