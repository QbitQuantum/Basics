void CWndPopup::DrawWindow()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CDC *pDC = GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap memBit;
	memBit.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());

	CBitmap *pOldBit = MemDC.SelectObject(&memBit);

	MemDC.SetBkMode(TRANSPARENT);
	if(m_pImage)
	{
		Graphics graphics(MemDC);
		DrawImageFrame(graphics, m_pImage, rcClient,0, 0, m_sizeBKImage.cx, m_sizeBKImage.cy, 32);
	}
	else
	{
		MemDC.FillSolidRect(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), RGB(0, 147, 209));
		MemDC.FillSolidRect(rcClient.left + 1, rcClient.top + 1, rcClient.Width() - 2, rcClient.Height() - 2, RGB(255, 255, 255));
	}

	CDC TempMemDC;
	TempMemDC.CreateCompatibleDC(&MemDC);
	TempMemDC.SetBkMode(TRANSPARENT);

	CBitmap TempMemBit;
	TempMemBit.CreateCompatibleBitmap(&MemDC, rcClient.Width(), rcClient.Height());

	CBitmap *pTempOldBit = TempMemDC.SelectObject(&TempMemBit);

	TempMemDC.FillSolidRect(0, 0, rcClient.Width(), rcClient.Height(), RGB(255, 0, 255));

	DrawWindow(TempMemDC, rcClient);

	DWORD dwSize = TempMemBit.GetBitmapBits(0,NULL);
	unsigned char *lpBuffer = new unsigned char[dwSize];
	TempMemBit.GetBitmapBits(dwSize,lpBuffer);
	for( int i = 0 ; i+3 < dwSize ; i+=4 )
	{
		if(lpBuffer[i] == 255 && lpBuffer[i + 1] == 0 && lpBuffer[i + 2] == 255)
		{
			lpBuffer[i] = 0;
			lpBuffer[i + 1] = 0;
			lpBuffer[i + 2] = 0;
		}
		else 			
		{
			if(lpBuffer[i] == 0 && lpBuffer[i + 1] == 0 && lpBuffer[i + 2] == 0) lpBuffer[i] = 1;
			lpBuffer[i+3] = 255;
		}
	}
	TempMemBit.SetBitmapBits(dwSize, lpBuffer);
	delete[] lpBuffer;

	BLENDFUNCTION blendTemp = {AC_SRC_OVER,0,255,AC_SRC_ALPHA};
	MemDC.AlphaBlend(0, 0, rcClient.Width(), rcClient.Height(), &TempMemDC, 0, 0, rcClient.Width(), rcClient.Height(), blendTemp);

	TempMemDC.SelectObject(pTempOldBit);
	TempMemBit.DeleteObject();
	TempMemDC.DeleteDC();

	DrawWindowEx(MemDC, rcClient);
 	DWORD dwSizeMen = memBit.GetBitmapBits(0,NULL);
 	unsigned char *lpBufferMen = new unsigned char[dwSize];
 	memBit.GetBitmapBits(dwSizeMen,lpBufferMen);
 	for( int i = 0 ; i+3 < dwSizeMen ; i+=4 )
 	{
 		if(lpBufferMen[i] == 0 && lpBufferMen[i + 1] == 0 && lpBufferMen[i + 2] == 0) lpBufferMen[i] = 1;
 	}
 	memBit.SetBitmapBits(dwSizeMen, lpBufferMen);
 	delete[] lpBufferMen;


	ClientToScreen(&rcClient);
	POINT pointDes;
	pointDes.x = rcClient.left;
	pointDes.y = rcClient.top;
	POINT pointSrc;
	pointSrc.x = 0;
	pointSrc.y = 0;
	SIZE sizeDes;
	sizeDes.cx = rcClient.Width();
	sizeDes.cy = rcClient.Height();

	BLENDFUNCTION blend;
	memset( &blend, 0, sizeof( blend) );
	blend.AlphaFormat = AC_SRC_ALPHA ;
	blend.SourceConstantAlpha = 255;

	HWND hWnd = GetSafeHwnd();
	SetWindowLong(hWnd,GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	UpdateLayeredWindow(pDC, &pointDes, &sizeDes, &MemDC, &pointSrc, 0, &blend,m_pImage ? ULW_ALPHA : ULW_COLORKEY);

	MemDC.SelectObject(pOldBit);
	memBit.DeleteObject();
	MemDC.DeleteDC();

	ReleaseDC(pDC);
}