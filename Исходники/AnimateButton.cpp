void CAnimateButton::PrepareBitmap(HBITMAP hBitmap)
{
	int nStates = 4;

	//取得图像所处区域及计算各状态按钮窗口区域
	m_arBmpRgn.SetSize(nStates);
	m_arBmpRgn.SetSize(nStates);

	CRect rcTmp;
	for(int i = 0; i < nStates; i ++)
	{
		m_arBmpRgn[i] = BitmapToRegion(hBitmap, nStates, i);
	}

	CBitmap* pBmpWhole = CBitmap::FromHandle(hBitmap);
	BITMAP bmp;
	pBmpWhole->GetBitmap(&bmp);

	m_aniBtnWidth = bmp.bmWidth / nStates;
	m_aniBtnHeight = bmp.bmHeight;

	m_pMemDC = new CDC;
	CDC* pDC = GetDC();
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pMemDC->SelectObject(pBmpWhole);
	ReleaseDC(pDC);

 	CRgn RgnWnd;
 	RgnWnd.CreateRectRgn(0, 0, m_aniBtnWidth, m_aniBtnHeight);
 	SetWindowRgn(HRGN(RgnWnd), FALSE);
	//调整大小(这样在DrawItem里面才可能限定画的范围)
	SetWindowPos(NULL, 0, 0, m_aniBtnWidth, m_aniBtnHeight, SWP_NOMOVE);
}