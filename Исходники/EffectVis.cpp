void CEffectVis::ShowVisImage(CDC *pDC)
//-------------------------------------
{
	CDC memDC;
	CBitmap memBitmap;
	CBitmap* oldBitmap; // bitmap originally found in CMemDC

	// to avoid flicker, establish a memory dc, draw to it
	// and then BitBlt it to the destination "pDC"
	memDC.CreateCompatibleDC(pDC);
	if (!memDC)
		return;
	memBitmap.CreateCompatibleBitmap(pDC, m_rcDraw.Width(), m_rcDraw.Height()) ;
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap) ;

	// make sure we have the bitmaps
	if (!m_dcGrid.GetSafeHdc())
		return ;
	if (!m_dcNodes.GetSafeHdc())
		return ;
	if (!m_dcPlayPos.GetSafeHdc())
		return ;

	if (memDC.GetSafeHdc() != NULL)
	{
		// draw the grid
		memDC.BitBlt(0, 0, m_rcDraw.Width(), m_rcDraw.Height(), &m_dcGrid, 0, 0, SRCCOPY) ;

		// merge the nodes image with the grid
		memDC.TransparentBlt(0, 0, m_rcDraw.Width(), m_rcDraw.Height(), &m_dcNodes, 0, 0, m_rcDraw.Width(), m_rcDraw.Height(), 0x00000000) ;
		// further merge the playpos
		memDC.TransparentBlt(0, 0, m_rcDraw.Width(), m_rcDraw.Height(), &m_dcPlayPos, 0, 0, m_rcDraw.Width(), m_rcDraw.Height(), 0x00000000) ;

		// copy the resulting bitmap to the destination
		pDC->BitBlt(0, 0, m_rcDraw.Width(), m_rcDraw.Height(), &memDC, 0, 0, SRCCOPY) ;
	}

	memDC.SelectObject(oldBitmap);

}