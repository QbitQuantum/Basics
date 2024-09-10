long CHSDib::Draw(HDC pDC, long xoffset, long yoffset,BOOL bTracking /*= FALSE*/)
{
	if( (hDib) && (pDC) ) 
	{
		CRect rect(xoffset, yoffset, m_bi.biWidth, m_bi.biHeight);

		if( bTracking == 2 ) // focus
		{
			FillRect(pDC, &rect, (HBRUSH) (COLOR_INFOBK + 1));
		}
		else if( bTracking == 1) // over
		{
			FillRect(pDC, &rect, (HBRUSH) (COLOR_WINDOW + 1));
		}
		else
		{
			FillRect(pDC, &rect, (HBRUSH) (COLOR_BTNFACE + 1));
		}

		CBrush hBrush;
		hBrush.CreateSolidBrush(0);
		FrameRect(pDC, &rect, (HBRUSH) hBrush );
		hBrush.DeleteObject();
		//LPSTR lpDIB = (char*)hDib;	//set image to hdc...
		//SetStretchBltMode(pDC,MAXSTRETCHBLTMODE);//COLORONCOLOR);	
		//SetDIBitsToDevice(pDC, xoffset, yoffset,
		//	m_bi.biWidth, m_bi.biHeight, 0, 0, 0,
		//	m_bi.biHeight, GetBits(),
		//	(BITMAPINFO*)lpDIB, DIB_RGB_COLORS);

#if Support_CHSDib
		//palette must be correctly filled
		LPSTR lpDIB = (char*)hDib;	//set image to hdc...
		SetStretchBltMode(pDC,MAXSTRETCHBLTMODE);//COLORONCOLOR);	
		SetDIBitsToDevice(pDC, xoffset, yoffset,
			m_bi.biWidth, m_bi.biHeight, 0, 0, 0,
			m_bi.biHeight, GetBits(),
			(BITMAPINFO*)lpDIB, DIB_RGB_COLORS);
#endif
		return 1;
	} 
	return 0;
}