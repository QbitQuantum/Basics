void CMatrixStatic::OnPaint(HWND hWnd) 
{

COLORREF SEGM_COLORS[3] = {
	RGB(63, 181, 255),	// BLUE ON
	RGB(23, 64,  103),	// BLUE OFF
	RGB(0,  0,   0),	// BLACK
};
	RECT rc;
	CRect m_rect;
	GetClientRect(&m_rect);
	int x = 0, y = 0;
	int strlen = m_csStrText.GetLength();
	if (strlen == 0)
		return;
	CPaintDC dc(this); // device context for painting
	HBITMAP bmp;
	COLORMAP	ColorMap[4];;
	ColorMap[0].from = SEGM_COLORS[0]; 
	ColorMap[0].to  = m_crOnColor;
	ColorMap[1].from = SEGM_COLORS[1]; 
	ColorMap[1].to  = m_crOffColor;
	ColorMap[2].from = SEGM_COLORS[2]; 
	ColorMap[2].to  = m_crBackColor;
	//bmp = ::CreateMappedBitmap(AfxGetInstanceHandle(), m_iImagematrix, 0, ColorMap, 3); //@@code modify -->
	bmp = ::CreateMappedBitmap(GetThisModule(), m_iImagematrix, 0, ColorMap, 3);
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);	// Select the bitmap into the in-memory DC
	//CBitmap* pOldBitmap = dcMemory.SelectObject(CBitmap::FromHandle(bmp)); //@@code modify -->
	HBITMAP pOldBitmap = dcMemory.SelectObject(bmp);
	int charcount = 0;
	int linecount = 1;
	HBRUSH hbBkBrush = CreateSolidBrush(m_crBackColor);
	FillRect(dc.m_hDC, &m_rect, hbBkBrush);
	for (int ix = 0; ix < strlen; ix++)
	{
		GetCharBmpOffset(&rc, (char)m_csStrText[ix]);
		dc.BitBlt(x, y, (m_icharwidth + m_ixspacing), (m_icharheight+m_iyspacing), &dcMemory, rc.left, rc.top, SRCCOPY);
		x += m_icharwidth + m_ixspacing;
		charcount++;
		if ((charcount == m_iMaxXChars) && m_iMaxYChars == 1)
			break;
		else if ((charcount == m_iMaxXChars) && m_iMaxYChars > 1)
		{
			if (linecount == m_iMaxYChars)
				break;
			x = charcount = 0;
			y += m_icharheight + m_iyspacing;
			linecount++;
		}
	}
	dcMemory.SelectObject(pOldBitmap);
	dcMemory.DeleteDC();
	DeleteObject(bmp);
	DeleteObject(hbBkBrush);
}