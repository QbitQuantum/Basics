void  CSkinWndHelper::DoNcPaint()
{
	CDC dc;
	HDC hdc = GetWindowDC(m_hWnd);
	dc.Attach(hdc);

	if (m_pBkImage==NULL)
	{
		return;
	}

	CDC MemDC;

	// 获取位置
	CRect rcWindow;
	GetWindowRect(m_hWnd,&rcWindow);
	rcWindow.OffsetRect( -rcWindow.left, -rcWindow.top);


	CRect rcClient;
	GetClientRect(m_hWnd,&rcClient);

	//剪除掉客户区
	rcClient.OffsetRect(m_nFrameWidth, m_nTitleHeight);
	dc.ExcludeClipRect(rcClient.left, rcClient.top,
		rcClient.right, rcClient.bottom);


	MemDC.CreateCompatibleDC(dc);


	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc,rcWindow.Width(),rcWindow.Height());
	MemDC.SelectBitmap(bmp);
	MemDC.SetBkMode(TRANSPARENT);

	Gdiplus::Graphics graphics(MemDC.m_hDC);
	RectF destRect;

	//绘制底部和边框
	destRect.X = 0;
	destRect.Y = rcWindow.Height() - m_nFrameWidth;
	destRect.Width = rcWindow.Width();
	destRect.Height = m_nFrameWidth;
	graphics.DrawImage(m_pBkImage,destRect,m_nTitleHeight,m_pBkImage->GetHeight()-m_nFrameWidth,m_nFrameWidth,m_nFrameWidth,UnitPixel);

	destRect.X = rcWindow.right-m_nTitleHeight;
	destRect.Y = rcWindow.bottom - m_nTitleHeight;
	destRect.Width = m_nTitleHeight;
	destRect.Height = m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,m_pBkImage->GetWidth()-m_nTitleHeight,m_pBkImage->GetHeight()-m_nTitleHeight,m_nTitleHeight,m_nTitleHeight,UnitPixel);

	destRect.X = 0;
	destRect.Y = rcWindow.Height() - m_nTitleHeight;
	destRect.Width = m_nTitleHeight;
	destRect.Height = m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,0,m_pBkImage->GetHeight()-m_nTitleHeight,m_nTitleHeight,m_nTitleHeight,UnitPixel);

	//左边框
	destRect.X = 0;
	destRect.Y = m_nTitleHeight;
	destRect.Width = m_nFrameWidth;
	destRect.Height = rcWindow.Height() - 2*m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,0,m_nTitleHeight,m_nFrameWidth,m_nFrameWidth,UnitPixel);


	//右边框
	destRect.X = rcWindow.Width() - m_nFrameWidth;
	destRect.Y = m_nTitleHeight;
	destRect.Width = m_nFrameWidth;
	destRect.Height = rcWindow.Height() - 2*m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,m_pBkImage->GetWidth()-m_nFrameWidth,m_nTitleHeight,m_nFrameWidth,m_nFrameWidth,UnitPixel);

	//绘制标题栏
	destRect.X = 0;
	destRect.Y = 0;
	destRect.Width = rcWindow.Width();
	destRect.Height = m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,50,0,5,m_nTitleHeight,UnitPixel);
	graphics.DrawImage(m_pBkImage,0,0,0,0,50,m_nTitleHeight,UnitPixel);
	graphics.DrawImage(m_pBkImage,rcWindow.Width() - 50,0,m_pBkImage->GetWidth()-50,0,50,m_nTitleHeight,UnitPixel);


	int xPos = 15;
	int yPos = 15;

	HICON hIcon = (HICON)::SendMessage(m_hWnd, WM_GETICON, ICON_SMALL, 0);
	if (hIcon)
	{
		DrawIconEx(MemDC,xPos, yPos-2,hIcon,GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, 0, DI_NORMAL);

		xPos += GetSystemMetrics(SM_CXSMICON);
		xPos += 5;
	}

	CString strText;
	int nLen = ::GetWindowTextLength(m_hWnd);
	::GetWindowText(m_hWnd, strText.GetBufferSetLength(nLen), nLen+1);
	strText.ReleaseBuffer();

	if (!strText.IsEmpty())
	{
		//绘制标题
		LOGFONT lfFont;
		memset(&lfFont, 0, sizeof(lfFont));
		lfFont.lfHeight = -12;
		lfFont.lfWeight |= FW_BOLD;
		lstrcpy(lfFont.lfFaceName, _T("宋体"));
		Gdiplus::Font font(dc.m_hDC, &lfFont);

		StringFormat stringFormat;
		stringFormat.SetFormatFlags( StringFormatFlagsNoWrap);
		stringFormat.SetAlignment(StringAlignmentNear);
		stringFormat.SetLineAlignment(StringAlignmentNear);
		CStringW strTitle(strText);
		SolidBrush brush((ARGB)Color::White);
		PointF point;

		point.X=(Gdiplus::REAL)xPos;
		point.Y=(Gdiplus::REAL)yPos;
		graphics.DrawString(strTitle, strTitle.GetLength(), &font, point,&stringFormat, &brush);

	}

	CRect rcPaint;
	dc.GetClipBox(&rcPaint);
	std::map<int,CDUIButton>::iterator iter;
	for (iter = m_TitleBtn.begin(); iter != m_TitleBtn.end(); iter++)
	{
		CDUIButton& dcControl = iter->second;
		CRect rcControl;
		dcControl.GetRect(&rcControl);

		// 判断当前按钮是否需要重绘
		if(!rcPaint.IsRectEmpty() && !CRect().IntersectRect(&rcControl, rcPaint))
		{
			continue;
		}

		dcControl.DrawButton(graphics);
	}



	dc.BitBlt(0,0,rcWindow.Width(),rcWindow.Height(),MemDC,0,0,SRCCOPY);

	dc.SelectClipRgn(NULL);

	dc.Detach();

	ReleaseDC(m_hWnd,hdc);


}