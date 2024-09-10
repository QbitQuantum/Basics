void CDoubleBufferDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
#ifndef DOUBLE
		CPaintDC dc(this);
		int x, y;
		CRect rect;
		GetClientRect(&rect);

		CPen *oldPen;
		CPen BlackPen(PS_SOLID, 1, RGB(0,0,0));
		CPen GreenPen(PS_SOLID, 1, RGB(0,255,0));
		CPen BluePen(PS_SOLID, 5, RGB(0,0,255));
		oldPen = dc.SelectObject(&BlackPen);

		for (x = 0; x < rect.right; x += 10)
		{
			dc.MoveTo(x, 0);
			dc.LineTo(x, rect.bottom);
		}

		for (y = 0; y < rect.bottom; y += 10)
		{
			dc.MoveTo(0, y);
			dc.LineTo(rect.right, y);
		}

		dc.SelectObject(&GreenPen);

		dc.Ellipse(ex - r, ey - r, r * 2, r * 2);
		dc.SelectObject(&BluePen);
		dc.Ellipse(ex - r, ey - r, r * 2, r * 2);

		dc.SelectObject(oldPen);
#else
		CPaintDC paintdc(this);
		CDC dc;
		CBitmap dcBitmap, *pOldBitmap;
		CPen BlackPen(PS_SOLID, 1, RGB(0,0,0));
		CPen GreenPen(PS_SOLID, 1, RGB(0,255,0));
		CPen BluePen(PS_SOLID, 5, RGB(0,0,255));
		CPen *pOldPen;

		int x, y;
		CRect rect;
		GetClientRect(&rect);

		dc.CreateCompatibleDC(&paintdc);
		dcBitmap.CreateCompatibleBitmap(&paintdc, rect.Width(), rect.Height());
		pOldBitmap = dc.SelectObject(&dcBitmap);
		dc.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

		pOldPen = dc.SelectObject(&BlackPen);

		for (x = 0; x < rect.right; x += 10)
		{
			dc.MoveTo(x, 0);
			dc.LineTo(x, rect.bottom);
		}

		for (y = 0; y < rect.bottom; y += 10)
		{
			dc.MoveTo(0, y);
			dc.LineTo(rect.right, y);
		}

		dc.SelectObject(&GreenPen);

		dc.Ellipse(ex - r, ey - r, ex - r + r * 2, ey - r + r * 2);
		dc.SelectObject(&BluePen);
		dc.Ellipse(ex - r, ey - r, ex - r + r * 2, ey - r + r * 2);

		paintdc.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
		
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBitmap);
		
		ReleaseDC(&dc);
		DeleteDC(dc);
#endif
		CDialogEx::OnPaint();
	}
}