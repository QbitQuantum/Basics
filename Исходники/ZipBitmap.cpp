void CZipBackGroundBitmap::CreateBackBitmap(CRect& Area, int uiBackGround, int Options, int TickWidth, int TickHeight)
{
	// Clear background
	hDC = ::CreateCompatibleDC(NULL);
	CreateBitmap(Area.Width(), Area.Height(), 1, ::GetDeviceCaps(hDC, BITSPIXEL), NULL);
	hbmold = (HBITMAP)::SelectObject(hDC, (HBITMAP)(m_hObject));

	HBRUSH hBR = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	::FillRect(hDC, Area, hBR);
	::DeleteObject(hBR);

	// Copy Background picture
	if (uiBackGround)
	{
		CZipBitmap Pic;
		Pic.LoadBitmap(uiBackGround);
		HDC hdcMem = ::CreateCompatibleDC(NULL);
		HBITMAP hbmold = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)(Pic.m_hObject));

		int Left, Top;
		Left = Top = 0;
		if (Options & BG_CENTER)
		{
			Left = (GetWidth() - Pic.GetWidth()) / 2;
			Top = (GetHeight() - Pic.GetHeight()) / 2;
		}
		else if (Options & BG_CENTER_ONTICK)
		{
			Left = (GetWidth() - Pic.GetWidth()) / 2;
			Top = (TickHeight - Pic.GetHeight()) / 2;
		}
		else if (Options & BG_CENTER_ONTICK_VERT)
		{
			Left = (TickWidth - Pic.GetWidth()) / 2;
			Top = (GetHeight() - Pic.GetHeight()) / 2;
		}
		if (Options & BG_STARTATICK)
		{
			Left = iMarginWidth - TickWidth / 2;
		}
		if (Options & BG_STARTATICK_VERT)
		{
			Top = iMarginWidth - TickHeight / 2;
		}

		// Blt the bits
		if (Options & BG_STRETCH_HOR)
		{
			int SpreadWidth = Area.Width();
			if (Options & BG_STARTATICK)
				SpreadWidth -= Left * 2;
			::StretchBlt(hDC, Left, Top, SpreadWidth, Pic.GetHeight(), hdcMem, 0, 0, Pic.GetWidth(), Pic.GetHeight(), SRCCOPY);
		}
		else if (Options & BG_STRETCH_VERT)
		{
			int SpreadHeight = Area.Height();
			if (Options & BG_STARTATICK_VERT)
				SpreadHeight -= Top * 2;
			::StretchBlt(hDC, Left, Top, Pic.GetWidth(), SpreadHeight, hdcMem, 0, 0, Pic.GetWidth(), Pic.GetHeight(), SRCCOPY);
		}
		else
			::BitBlt(hDC, Left, Top, Pic.GetWidth(), Pic.GetHeight(), hdcMem, 0, 0, SRCCOPY);

		::SelectObject(hdcMem, hbmold);
		::DeleteDC(hdcMem);
	}
}