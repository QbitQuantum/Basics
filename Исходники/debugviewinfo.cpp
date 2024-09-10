void debugview_info::draw_contents(HDC windc)
{
	debug_view_char const *viewdata = m_view->viewdata();
	debug_view_xy const visarea = m_view->visible_size();

	// get the client rect
	RECT client;
	GetClientRect(m_wnd, &client);

	// create a compatible DC and an offscreen bitmap
	HDC const dc = CreateCompatibleDC(windc);
	if (dc == nullptr)
		return;
	HBITMAP const bitmap = CreateCompatibleBitmap(windc, client.right, client.bottom);
	if (bitmap == nullptr)
	{
		DeleteDC(dc);
		return;
	}
	HGDIOBJ const oldbitmap = SelectObject(dc, bitmap);

	// set the font
	HGDIOBJ const oldfont = SelectObject(dc, metrics().debug_font());
	COLORREF const oldfgcolor = GetTextColor(dc);
	int const oldbkmode = GetBkMode(dc);
	SetBkMode(dc, TRANSPARENT);

	// iterate over rows and columns
	for (UINT32 row = 0; row < visarea.y; row++)
	{
		// loop twice; once to fill the background and once to draw the text
		for (int iter = 0; iter < 2; iter++)
		{
			COLORREF fgcolor;
			COLORREF bgcolor = RGB(0xff,0xff,0xff);
			HBRUSH bgbrush = nullptr;
			int last_attrib = -1;
			TCHAR buffer[256];
			int count = 0;
			RECT bounds;

			// initialize the text bounds
			bounds.left = bounds.right = 0;
			bounds.top = row * metrics().debug_font_height();
			bounds.bottom = bounds.top + metrics().debug_font_height();

			// start with a brush on iteration #0
			if (iter == 0)
				bgbrush = CreateSolidBrush(bgcolor);

			// iterate over columns
			for (UINT32 col = 0; col < visarea.x; col++)
			{
				// if the attribute changed, adjust the colors
				if (viewdata[col].attrib != last_attrib)
				{
					COLORREF oldbg = bgcolor;

					// reset to standard colors
					fgcolor = RGB(0x00,0x00,0x00);
					bgcolor = RGB(0xff,0xff,0xff);

					// pick new fg/bg colors
					if (viewdata[col].attrib & DCA_VISITED) bgcolor = RGB(0xc6, 0xe2, 0xff);
					if (viewdata[col].attrib & DCA_ANCILLARY) bgcolor = RGB(0xe0,0xe0,0xe0);
					if (viewdata[col].attrib & DCA_SELECTED) bgcolor = RGB(0xff,0x80,0x80);
					if (viewdata[col].attrib & DCA_CURRENT) bgcolor = RGB(0xff,0xff,0x00);
					if ((viewdata[col].attrib & DCA_SELECTED) && (viewdata[col].attrib & DCA_CURRENT)) bgcolor = RGB(0xff,0xc0,0x80);
					if (viewdata[col].attrib & DCA_CHANGED) fgcolor = RGB(0xff,0x00,0x00);
					if (viewdata[col].attrib & DCA_INVALID) fgcolor = RGB(0x00,0x00,0xff);
					if (viewdata[col].attrib & DCA_DISABLED) fgcolor = RGB((GetRValue(fgcolor) + GetRValue(bgcolor)) / 2, (GetGValue(fgcolor) + GetGValue(bgcolor)) / 2, (GetBValue(fgcolor) + GetBValue(bgcolor)) / 2);
					if (viewdata[col].attrib & DCA_COMMENT) fgcolor = RGB(0x00,0x80,0x00);

					// flush any pending drawing
					if (count > 0)
					{
						bounds.right = bounds.left + (count * metrics().debug_font_width());
						if (iter == 0)
							FillRect(dc, &bounds, bgbrush);
						else
							ExtTextOut(dc, bounds.left, bounds.top, 0, nullptr, buffer, count, nullptr);
						bounds.left = bounds.right;
						count = 0;
					}

					// set the new colors
					if (iter == 0 && oldbg != bgcolor)
					{
						DeleteObject(bgbrush);
						bgbrush = CreateSolidBrush(bgcolor);
					}
					else if (iter == 1)
						SetTextColor(dc, fgcolor);
					last_attrib = viewdata[col].attrib;
				}

				// add this character to the buffer
				buffer[count++] = viewdata[col].byte;
			}

			// flush any remaining stuff
			if (count > 0)
			{
				bounds.right = bounds.left + (count * metrics().debug_font_width());
				if (iter == 0)
					FillRect(dc, &bounds, bgbrush);
				else
					ExtTextOut(dc, bounds.left, bounds.top, 0, nullptr, buffer, count, nullptr);
			}

			// erase to the end of the line
			if (iter == 0)
			{
				bounds.left = bounds.right;
				bounds.right = client.right;
				FillRect(dc, &bounds, bgbrush);
				DeleteObject(bgbrush);
			}
		}

		// advance viewdata
		viewdata += visarea.x;
	}

	// erase anything beyond the bottom with white
	GetClientRect(m_wnd, &client);
	client.top = visarea.y * metrics().debug_font_height();
	FillRect(dc, &client, (HBRUSH)GetStockObject(WHITE_BRUSH));

	// reset the font
	SetBkMode(dc, oldbkmode);
	SetTextColor(dc, oldfgcolor);
	SelectObject(dc, oldfont);

	// blit the final results
	BitBlt(windc, 0, 0, client.right, client.bottom, dc, 0, 0, SRCCOPY);

	// undo the offscreen stuff
	SelectObject(dc, oldbitmap);
	DeleteObject(bitmap);
	DeleteDC(dc);
}