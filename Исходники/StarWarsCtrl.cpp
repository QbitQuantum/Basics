//##ModelId=43B25EC100EA
void CStarWarsCtrl::DoScrollText(CDC *pDC)
{
	int nPosX =0;
	int nPosY =0;

	CDC memDC;
	CBitmap memBitmap;
	CFont *oldFont;

	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, m_rectClient.Width(), m_rectClient.Height());
	memDC.SelectObject(&memBitmap);
	memDC.SetBkColor(RGB(0,0,0));
	memDC.SetTextColor(RGB(0,255,0));
    memDC.SetBkMode(TRANSPARENT);

	oldFont = memDC.SelectObject(&m_Font);

	// black
	memDC.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), NULL, 0, 0, BLACKNESS);
	
	// draw Credits on the hidden Picture
	for(int i=0; i < m_TextLines.GetSize(); i++)
	{
		// set position for this line
		CSize size = memDC.GetTextExtent(m_TextLines.GetAt(i));

		nPosY = m_nScrollPos + (i * size.cy);
		if (nPosY > 0)
		{
			nPosX = (m_rectClient.Width() / 2) - (size.cx / 2);

			if (nPosY > 255)
			{
				memDC.SetTextColor(RGB(255, 255, 255));
			}
			else
			{
				// set fade color
				memDC.SetTextColor(RGB(nPosY, nPosY, nPosY));
			}
			
			// print text
			memDC.TextOut(nPosX, nPosY, m_TextLines.GetAt(i));
		}
		else
		{
			// start all over ...
			if (i == (m_TextLines.GetSize()-1))
			{
				m_nScrollPos = m_rectClient.Height();
			}
		}
	}

	int nWidth = m_rectClient.Width();
	int nHeight = m_rectClient.Height();

	// shrink text from bottom to top to create Star Wars effect
	for (int y=0; y <nHeight; y++)
	{
		double nScale = (double)y/(double)nHeight;
		int nOffset = (int)(nWidth - nWidth*nScale)/2;
		m_MainDC.StretchBlt(nOffset, y, (int)(nWidth*nScale), 1, &memDC, 0, y, nWidth, 1, SRCPAINT);
	}

	// restore the font
	memDC.SelectObject(oldFont);

	// move text up one pixel
	m_nScrollPos = m_nScrollPos - m_nScrollSpeed;
}