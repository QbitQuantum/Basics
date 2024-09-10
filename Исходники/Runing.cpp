void CDuiAnimateImage::DrawControl(CDC &dc, CRect rcUpdate)
{
	int nWidth = m_rc.Width();
	int nHeight = m_rc.Height();

	if(!m_bUpdate)
	{
		UpdateMemDC(dc, nWidth * m_nMaxIndex, nHeight);

		Graphics graphics(m_memDC);
		
		CPoint point = GetOriginPoint(nWidth, nHeight, m_sizeImage.cx, m_sizeImage.cy,
						GetGDIAlignment(m_uAlignment), GetGDIVAlignment(m_uVAlignment));

		for(int i = 0; i < m_nMaxIndex; i++)
		{
			m_memDC.BitBlt(i * nWidth, 0, nWidth, nHeight, &dc, m_rc.left ,m_rc.top, SRCCOPY);

			graphics.DrawImage(m_pImage, Rect(point.x , point.y,  m_sizeImage.cx, m_sizeImage.cy),
				i * m_sizeImage.cx, 0, m_sizeImage.cx, m_sizeImage.cy, UnitPixel);

			point.x += nWidth;
		}
	}

	dc.BitBlt(m_rc.left,m_rc.top, m_rc.Width(), m_rc.Height(), &m_memDC, m_nIndex * nWidth, 0, SRCCOPY);
}