BOOL CBackgroundUtil::TileBitmap(
	CDC* pDC, 
	CRect rc
) {
	CDC MemDC;

	// If there is a bitmap loaded
	if (m_BmpPattern.m_hObject != NULL)
	{
		MemDC.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = MemDC.SelectObject(&m_BmpPattern);

		// Clip the tiling to the requested rect.
		// Convert from screen coords to logical coords...
		CRgn rgn;
		CRect rectRgn = rc;
		pDC->DPtoLP( &rectRgn );
		rgn.CreateRectRgn(
			rectRgn.TopLeft().x, 
			rectRgn.TopLeft().y, 
			rectRgn.BottomRight().x, 
			rectRgn.BottomRight().y
		); 
		pDC->SelectClipRgn( &rgn ); 

		if ( m_BkgndStyle == BDBS_TILE )
		{
			// Tile the bitmap.
			// Note that it has to be offset as needed, but
			// we want to make sure we still tile the whole client area.

			// actual xoffset = -xoff + (xoff/xbmp)*xbmp
			int x = - m_nXOffset + ( m_nXOffset / m_nBmpWidth  ) * m_nBmpWidth ;
			int y = - m_nYOffset + ( m_nYOffset / m_nBmpHeight ) * m_nBmpHeight;

			while ( y < rc.Height() ) 
			{
				while( x < rc.Width() ) 
				{
					pDC->BitBlt(x, y, m_nBmpWidth, m_nBmpHeight, &MemDC, 0, 0, SRCCOPY);
					x += m_nBmpWidth;
				}
				x = - m_nXOffset + ( m_nXOffset / m_nBmpWidth  ) * m_nBmpWidth ;
				y += m_nBmpHeight;
			}
		
		} else if ( m_BkgndStyle == BDBS_CENTER )
		{
			pDC->BitBlt(
				m_nXOffset + ( rc.Width()  - m_nBmpWidth  ) / 2, 
				m_nYOffset + ( rc.Height() - m_nBmpHeight ) / 2, 
				m_nBmpWidth, 
				m_nBmpHeight, 
				&MemDC, 
				0, 
				0, 
				SRCCOPY
			);		
		}

		MemDC.SelectObject(pOldBitmap);

		pDC->SelectClipRgn( NULL ); 

		return TRUE;
	}

	return FALSE; // Normal behaviour
} // End of TileBitmap