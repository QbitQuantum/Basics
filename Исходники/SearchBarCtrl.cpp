void CSearchBarCtrl::OnPaint()
{
	CPaintDC dc(this);

	CRect rtTriangle;
	CRect rtBack;
	

	CClientRect	rtClient(this);
	CBufferDC	bufDC(dc.GetSafeHdc(), rtClient);
	rtTriangle.CopyRect(rtClient);

	SendMessage(WM_ERASEBKGND, (WPARAM) bufDC.GetSafeHdc(), 1);

	CSize	sizeIcon;
	CRect	rtIcon;
	CFaceManager::GetInstance()->GetImageSize(m_nCurrentIcon, sizeIcon);
	CenterRect(&rtIcon, rtClient, sizeIcon);

	rtIcon.left = rtClient.left + MARGIN_WIDTH;
	rtIcon.top = rtClient.top + MARGIN_WIDTH;
	rtIcon.right = rtIcon.left + sizeIcon.cx;

	rtBack.left = rtClient.left + 2;
	rtBack.top = rtClient.top + 2;
	rtBack.bottom = rtClient.bottom;
	rtBack.right = sizeIcon.cx - 8;


	if (m_bHover)
	{
		bufDC.FillSolidRect(rtBack, RGB(226,226,226));//RGB(238,236,221)
	}
	else
	{
		bufDC.FillSolidRect(rtBack, RGB(240,240,240));//RGB(238,236,221)
	}

	{
		CPenDC pen(bufDC.GetSafeHdc(), RGB(200,200,200));


		bufDC.MoveTo(rtBack.bottom + 6, rtBack.top - 1);
		bufDC.LineTo(rtBack.bottom + 6, rtBack.right - 5);

	}

	m_ImageList.Draw(&bufDC, m_nCurrentIcon, CPoint(rtIcon.left, rtIcon.top), ILD_NORMAL);

	rtTriangle.left = rtClient.left + MARGIN_WIDTH + 1;
	rtTriangle.bottom = rtClient.bottom - rtClient.Height()/2 + MARGIN_WIDTH;
	rtTriangle.right = rtTriangle.left + sizeIcon.cx;


	DrawTriangle(&bufDC, rtTriangle);

}