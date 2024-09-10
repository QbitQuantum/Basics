void CWindowWithShadow::CWndShadow::DoPaint( RECT* prcPaint )
{
	//COMMON_TRACE(L"Paint--------");
	if ((GetWindowLong(GetHWND(), GWL_EXSTYLE) & WS_EX_LAYERED) == 0)
		SetWindowLong(GetHWND(), GWL_EXSTYLE, GetWindowLong(GetHWND(), GWL_EXSTYLE) | WS_EX_LAYERED);

	if (prcPaint == NULL)
		GetWindowRect(GetHWND(), prcPaint);
	if (::IsRectEmpty(prcPaint))
		return;
	int iWidth = prcPaint->right - prcPaint->left;
	int iHeight = prcPaint->bottom - prcPaint->top;
	if (m_hmpOffscreen != NULL)
	{
		::SelectObject(m_hDcOffScreen, m_hbmpOffscreenOld);
		::DeleteObject(m_hmpOffscreen);
		::DeleteDC(m_hDcOffScreen);
	}
	if (m_hDcPaint ==  NULL)
		m_hDcPaint = GetDC(GetHWND());

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biHeight = iHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = iWidth * iHeight * (bmi.bmiHeader.biBitCount/8);
	m_hmpOffscreen = ::CreateDIBSection(m_hDcPaint, &bmi, DIB_RGB_COLORS, (LPVOID*) &m_pDibOffScreen, NULL, 0);

	m_hDcOffScreen = CreateCompatibleDC(m_hDcPaint);
	m_hbmpOffscreenOld = (HBITMAP)SelectObject(m_hDcOffScreen, m_hmpOffscreen);

	RECT rcClient;
	GetClientRect(GetHWND(), &rcClient);

	if (m_PaintManager.GetResourcePath().IsEmpty())
	{	// 允许更灵活的资源路径定义
		CDuiString strResourcePath=m_PaintManager.GetInstancePath();
		m_PaintManager.SetResourcePath(strResourcePath.GetData());
	}
	DuiLib::CRenderEngine::DrawImageString(m_hDcOffScreen, &m_PaintManager,  rcClient, *prcPaint, L"file='bk_shadow.png' corner='10,10,10,10'");
	//FillRect(m_hDcOffScreen, &rcClient, (HBRUSH)GetStockObject(BLACK_BRUSH));

	POINT ptDest = {prcPaint->left, prcPaint->top};
	::ClientToScreen(GetHWND(), &ptDest);
	POINT ptSrc = {0, 0};
	SIZE sz = {rcClient.right-rcClient.left, rcClient.bottom-rcClient.top};

	BLENDFUNCTION bfUpdate;
	bfUpdate.BlendOp = AC_SRC_OVER;
	bfUpdate.AlphaFormat = AC_SRC_ALPHA;
	bfUpdate.BlendFlags = 0;
	bfUpdate.SourceConstantAlpha = 255;
	BOOL bRet = UpdateLayeredWindow(GetHWND(), m_hDcPaint, NULL, &sz, m_hDcOffScreen, &ptSrc, 0, &bfUpdate,ULW_ALPHA);

// 	HDC hDCScreen = GetDC(NULL);
// 	BitBlt(hDCScreen, 100,100, 100, 100, m_hDcOffScreen, 0, 0, SRCCOPY);
// 	ReleaseDC(NULL, hDCScreen);
}